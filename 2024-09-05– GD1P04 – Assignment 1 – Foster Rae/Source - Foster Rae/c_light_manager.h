// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_light_manager.h
// Description : A class to manage the lights in the scene.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <glew.h>
#include <glm.hpp>
#include <vector>
#include "c_cube.h"

// === LIGHT STRUCTS ===
/**
 * @brief Struct to hold the point light data.
 * @param position The position of the light. (vec3)
 * @param color The color of the light. (vec3)
 * @param constant The constant attenuation value. (float)
 * @param linear The linear attenuation value. (float)
 * @param quadratic The quadratic attenuation value. (float)
 */
struct s_point_light {
	glm::vec3 position;
	glm::vec3 color;
	// Attenuation values.
	float constant;
	float linear;
	float quadratic;
};

/**
 * @brief Struct to hold the directional light data.
 * @param direction The direction of the light. (vec3)
 * @param color The color of the light. (vec3)
 */
struct s_directional_light {
	glm::vec3 direction;
	glm::vec3 color;
};

/**
 * @brief Struct to hold the spotlight data.
 * @param position The position of the light. (vec3)
 * @param direction The direction of the light. (vec3)
 * @param cut_off The cut off value. (float)
 * @param outer_cut_off The outer cut off value. (float)
 * @param color The color of the light. (vec3)
 * @param constant The constant attenuation value. (float)
 * @param linear The linear attenuation value. (float)
 * @param quadratic The quadratic attenuation value. (float)
 */
struct s_spotlight {
	glm::vec3 position;
	glm::vec3 direction;
	// Cut off values.
	float cut_off;
	float outer_cut_off;

	glm::vec3 color; // Color of the light.
	// Attenuation values.
	float constant;
	float linear;
	float quadratic;
};

class c_light_manager {
public:
	c_light_manager();
	/**
	 * @brief Add a point light to the scene.
	 * @param light The point light to add.
	 */
	void add_point_light(const s_point_light& light);
	/**
	 * @brief Set the directional light in the scene.
	 * @param light The directional light to set.
	 */
	void set_directional_light(const s_directional_light& light);
	/**
	 * @brief Set the spotlight in the scene.
	 * @param light The spotlight to set.
	 */
	void set_spotlight(const s_spotlight& light);
	/**
	 * @brief Toggle the point lights in the scene.
	 * @param state The state to toggle the lights to.
	 */
	void toggle_point_lights(bool state);
	/**
	 * @brief Toggle the directional light in the scene.
	 * @param state The state to toggle the light to.
	 */
	void toggle_directional_light(bool state);
	/**
	 * @brief Toggle the spotlight in the scene.
	 * @param state The state to toggle the light to.
	 */
	void toggle_spotlight(bool state);
	/**
	 * @brief Update the lights in the shader.
	 * @param shader_program The shader program to update the lights in.
	 * @param camera_position The position of the camera, to calculate specular highlights.
	 */
	void update_lights_in_shader(unsigned int shader_program, const glm::vec3& camera_position);
	/**
	 * @brief Update the spotlight with camera position and direction.
	 * @param position The position of the camera.
	 * @param direction The direction the camera is looking.
	 */
	void update_spotlight(const glm::vec3& position, const glm::vec3& direction);
	/**
	 * @brief Get the point lights in the scene.
	 * @return A vector of point lights.
	 */
	const std::vector<s_point_light>& get_point_lights() const { return point_lights_; }
	/**
	 * @brief Update the point light cubes to match the point light positions and colors.
	 */
	void update_point_light_cubes();
	/**
	 * @brief Draw the point light cubes.
	 * @param shader_program The shader program to draw the cubes with.
	 */
	void draw_point_light_cubes(GLuint shader_program);

private:

	std::vector<s_point_light> point_lights_; // Vector of point lights in the scene.
	std::vector<c_cube> point_light_cubes_;   // Vector of cubes representing the point lights.
	s_directional_light dir_light_;
	s_spotlight spot_light_;
	// Light toggles.
	bool point_lights_on_;
	bool dir_light_on_;
	bool spot_light_on_;
};
