#include "c_camera.h"
#include <ext/matrix_clip_space.hpp> // glm::perspective

c_camera::c_camera()
{
	position_ = glm::vec3(0.0f, -2.0f, 10.0f); // Camera starts at 10 units back.
	previous_position_ = position_;
	previous_free_position_ = position_;
	look_dir_ = glm::vec3(
		(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_))),
		(sin(glm::radians(pitch_))),
		(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))));
	right_vector_ = glm::normalize(glm::cross(look_dir_, up_dir_));
	up_dir_ = glm::vec3(0.0f, 1.0f, 0.0f); // Set to world up.
	target_position_ = glm::vec3(0.0f, -2.0f, -3.0f); // Target camera is pointing at origin.
	last_tab_time_ = 0.0f;
	orbit_radius_ = 10.0f;
	orbit_angle_ = 0.0f;
	orbit_height = orbit_radius_ * 0.5f;
	is_target_camera_ = true;

	// Set default matrices.
	projection_matrix_ = glm::mat4(1.0f);
	view_matrix_ = glm::mat4(1.0f);
}

void c_camera::update(GLFWwindow* window, float delta_time)
{
	// Process camera input.
	process_input(window, delta_time);

	// Check if the camera is in orbit mode.
	if (is_target_camera_ || is_manual_camera_)
	{
		// Convert polar coordinates to Cartesian coordinates.
		position_.x = target_position_.x + orbit_radius_ * cos(glm::radians(orbit_angle_));
		position_.z = target_position_.z + orbit_radius_ * sin(glm::radians(orbit_angle_));
		position_.y = target_position_.y + orbit_height; // Maintain a constant height.
		orbit_height = orbit_radius_ * 0.5f; // Keep the camera at a fixed height.

		// Update the look direction for movement in orbit mode.
		look_dir_ = glm::normalize(target_position_ - position_);

		// Calculate the view matrix for the orbital camera.
		view_matrix_ = glm::lookAt(position_, target_position_, up_dir_);
	}
	else
	{
		// Calculate the view matrix for FPS camera.
		view_matrix_ = glm::lookAt(position_, position_ + look_dir_, up_dir_);
	}

	// Update right vector.
	right_vector_ = glm::normalize(glm::cross(look_dir_, up_dir_));

	// Update the perspective matrix.
	projection_matrix_ = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width_) / static_cast<float>(window_height_), 0.1f, view_distance_);

	// Update the current time.
	current_time += delta_time;
}

void c_camera::process_input(GLFWwindow* window, float delta_time)
{
	glm::vec3 direction(0.0f); // Direction vector for movement.
	float orbit_multiplier = 10.0f;  // Orbit speed multiplier.

	if (is_target_camera_) // Automatic Orbit.
	{
		orbit_angle_ += get_camera_speed() * delta_time * orbit_multiplier;
	}
	else if (is_manual_camera_) // Manual Orbit.
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // Move left.
		{
			orbit_angle_ += get_camera_speed() * delta_time * orbit_multiplier;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // Move right.
		{
			orbit_angle_ -= get_camera_speed() * delta_time * orbit_multiplier;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // Move closer.
		{
			orbit_radius_ -= get_camera_speed() * delta_time * orbit_multiplier / 5; // Was a bit too fast so divide by 5.
			if (orbit_radius_ < 1.0f) // Prevent the camera from getting too close.
			{
				orbit_radius_ = 1.0f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // Move further.
		{
			orbit_radius_ += get_camera_speed() * delta_time * orbit_multiplier / 5;
		}
	}
	else // Free Camera Movement Controls
	{
		// Force the camera to update, first mouse flag not working here.
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);
		mouse_input(window, x_pos, y_pos);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // Move forward.
		{
			direction += look_dir_;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // Move backward.
		{
			direction -= look_dir_;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // Move left.
		{
			direction -= glm::normalize(glm::cross(look_dir_, up_dir_));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // Move right.
		{
			direction += glm::normalize(glm::cross(look_dir_, up_dir_));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // Move up.
		{
			direction += up_dir_;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) // Move down.
		{
			direction -= up_dir_;
		}

		// Normalize the direction vector to handle diagonal movement.
		if (glm::length(direction) > 0.0f)
		{
			direction = glm::normalize(direction);
		}

		// Apply the movement.
		position_ += get_camera_speed() * delta_time * direction;
	}

	// If left shift is pressed, speed up the camera.
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		set_camera_speed(5.0f);
	}
	else
	{
		set_camera_speed(2.5f);
	}

	// If tab is pressed, switch camera mode.
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (current_time - last_tab_time_ > 0.5f) // Check if 0.5 seconds have passed.
		{
			switch_camera_mode();
			last_tab_time_ = current_time; // Update last_tab_time.
		}
	}
}

void c_camera::mouse_input(GLFWwindow* window, double x_pos, double y_pos)
{
	if (is_target_camera_) // Don't allow mouse input in target mode.
	{
		return;
	}

	// Use first mouse flag to prevent a jump in the camera when the mouse is first moved.
	if (first_mouse_) // Update last x and y.
	{
		last_x_ = x_pos;
		last_y_ = y_pos;
		first_mouse_ = false;
	}

	// Offset since last frame.
	float x_offset = static_cast<float>(x_pos - last_x_);
	float y_offset = static_cast<float>(last_y_ - y_pos);
	last_x_ = x_pos;
	last_y_ = y_pos;

	// Sensitivity.
	x_offset *= sensitivity_;
	y_offset *= sensitivity_;

	// Update yaw and pitch.
	yaw_ += x_offset;
	pitch_ += y_offset;

	// Clamp pitch. (no glm in this file)
	if (pitch_ > 89.0f)
	{
		pitch_ = 89.0f;
	}
	if (pitch_ < -89.0f)
	{
		pitch_ = -89.0f;
	}

	// Update look direction.
	look_dir_ = glm::normalize(glm::vec3(
		(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_))),
		(sin(glm::radians(pitch_))),
		(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)))));
}

void c_camera::switch_camera_mode()
{
	// Auto orbit -> Manual orbit -> FPS -> Auto orbit.
	if (is_target_camera_) // Switch to manual orbit.
	{
		position_ = previous_position_; // Continue from the auto orbit position.
		is_target_camera_ = false;
		is_manual_camera_ = true;       // Switch to manual orbit.
	}
	else if (is_manual_camera_) // Switch to FPS.
	{
		previous_position_ = position_;      // Save old manual orbit pos.
		position_ = previous_free_position_; // Restore old free cam pos.
		is_manual_camera_ = false;           // Switch to FPS.
	}
	else // Switch to auto orbit.
	{
		previous_free_position_ = position_; // Save old free cam pos for changing back.
		is_target_camera_ = true;            // Switch to auto orbit.
	}
}