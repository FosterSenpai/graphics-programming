﻿// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_camera.h
// Description : Class to handle the camera movement and view + projection matrices.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include <glfw3.h>
#include <ext/matrix_float4x4.hpp>
#include <ext/matrix_transform.hpp>

class c_camera
{
public:

	// == Constructors and Destructors ==
	c_camera(); // Constructor starts the camera at the origin.
	~c_camera() = default;

	// == Public Methods ==
	/**
	 * @brief Updates the camera position and view matrix based on the delta time.
	 * @param delta_time The time between frames. (float)
	 */
	void update(float delta_time);
	void process_input(GLFWwindow* window, float delta_time);
	void mouse_input(GLFWwindow* window, double x_pos, double y_pos);
	void switch_camera_mode(); // Use to swap modes on input.


	// == Accessors & Mutators ==
	void set_position(glm::vec3 position) { position_ = position; }
	void set_look_dir(glm::vec3 look_dir) { look_dir_ = look_dir; }
	void set_up_dir(glm::vec3 up_dir) { up_dir_ = up_dir; }
	void set_target_position(glm::vec3 target_position) { target_position_ = target_position; }
	void set_projection_matrix(const glm::mat4& projection_matrix) { projection_matrix_ = projection_matrix; }
	void set_view_matrix(const glm::mat4& view_matrix) { view_matrix_ = view_matrix; }
	void set_camera_speed(float camera_speed) { camera_speed_ = camera_speed; }
	void set_sensitivity(float sensitivity) { sensitivity_ = sensitivity; }
	void set_window_size(int width, int height) { window_width_ = width; window_height_ = height; }
	void set_view_distance(float view_distance) { view_distance_ = view_distance; }

	glm::vec3 get_position() const { return position_; }
	glm::vec3 get_look_dir() const { return look_dir_; }
	glm::vec3 get_up_dir() const { return up_dir_; }
	glm::vec3 get_target_position() const { return target_position_; }
	glm::mat4 get_view_matrix() const { return view_matrix_; }
	glm::mat4 get_projection_matrix() const { return projection_matrix_; }
	float get_camera_speed() const { return camera_speed_; }
	int get_window_width() const { return window_width_; }
	int get_window_height() const { return window_height_; }

	// == Public Members ==
	float current_time = 0.0f; // The current time of the camera.

private:

	// == Private Members ==
	glm::vec3 position_;           // Position of the camera.
	glm::vec3 previous_position_;
	glm::vec3 look_dir_;           // Direction the camera is looking.
	glm::vec3 up_dir_;             // Up direction of the camera.
	glm::vec3 target_position_;    // Position of the target camera.
	bool is_target_camera_;        // Flag to change the view matrix from FPS to target camera.
	float last_tab_time_;          // Time since the last tab press.
	float camera_speed_ = 2.5f;    // Speed the camera moves at.

	// Mouse input variables.
	double last_x_ = 400.0f;       // x position of the mouse, initialized to the center of the screen.
    double last_y_ = 300.0f;       // y position of the mouse, initialized to the center of the screen.
    float yaw_ = -90.0f;           // Yaw is initialized to -90.0 degrees to look along the z-axis
    float pitch_ = 0.0f;
    float sensitivity_ = 0.1f;     // Mouse sensitivity
	bool first_mouse_ = true;      // Flag to check if the mouse has moved.

	int window_width_ = 800;       // Window width and height for calculating the center.
	int window_height_ = 800;
	float view_distance_ = 100.0f; // Distance the camera can see.

	// Matrices
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;

};
