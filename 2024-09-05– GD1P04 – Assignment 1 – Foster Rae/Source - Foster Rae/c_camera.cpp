#include "c_camera.h"

#include <ext/matrix_clip_space.hpp>


c_camera::c_camera()
{
	// Set default values.
	position_ = glm::vec3(0.0f, 0.0f, 3.0f); // Camera starts at 3 units back.
	previous_position_ = position_;
	look_dir_ = glm::vec3(
		(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_))),
		(sin(glm::radians(pitch_))),
		(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))));
	up_dir_ = glm::vec3(0.0f, 1.0f, 0.0f);
	target_position_ = glm::vec3(0.0f, 0.0f, 0.0f); // Target camera is pointing at origin.
    is_target_camera_ = false; // Default to FPS camera.
	last_tab_time_ = 0.0f;

    // Set default matrices.
	projection_matrix_ = glm::mat4(1.0f);
    view_matrix_ = glm::mat4(1.0f);
}

void c_camera::update(float delta_time)
{
	// Check if the camera is in target mode.
	if (is_target_camera_)
	{
		// Calculate the view matrix for target camera.
		view_matrix_ = glm::lookAt(position_, target_position_, up_dir_);
	}
	else
	{
		// Calculate the view matrix for FPS camera.
		view_matrix_ = glm::lookAt(position_, position_ + look_dir_, up_dir_);
	}

	// Perspective Projection Matrix.
    projection_matrix_ = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width_)/static_cast<float>(window_height_), 0.1f, view_distance_);
	//Todo: Orthographic Projection Matrix for UI elements.

	// Update the current time.
	current_time += delta_time;
}

void c_camera::process_input(GLFWwindow* window, float delta_time)
{
	// Camera Movement Controls/
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Move forward.
	{
		position_ += get_camera_speed() * delta_time * look_dir_;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Move backward.
	{
		position_ -= get_camera_speed() * delta_time * look_dir_;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Move left.
	{
		position_ -= glm::normalize(glm::cross(look_dir_, up_dir_)) * get_camera_speed() * delta_time;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Move right.
	{
		position_ += glm::normalize(glm::cross(look_dir_, up_dir_)) * get_camera_speed() * delta_time;
	}
	// If space is pressed, move up.
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position_ += up_dir_ * get_camera_speed() * delta_time;
	}
	// If left control is pressed, move down.
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position_ -= up_dir_ * get_camera_speed() * delta_time;
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
        if (current_time - last_tab_time_ > 0.5f) // Check if 0.5 seconds have passed
        {

            switch_camera_mode();
            last_tab_time_ = current_time; // Update last_tab_time
        }
	}
}

void c_camera::mouse_input(GLFWwindow* window, double x_pos, double y_pos)
{
	if (is_target_camera_) // Don't allow mouse input in target mode.
	{
		return;
	}

	if (first_mouse_)
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

	// Clamp pitch.
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
	if (is_target_camera_)
    {
        // Switch to FPS camera and restore the previous position
        position_ = previous_position_;
        is_target_camera_ = false;

		// Reset mouse state
        first_mouse_ = true;
    }
    else
    {
        // Save the current position and switch to target camera
        previous_position_ = position_;
        is_target_camera_ = true;
    }
}
