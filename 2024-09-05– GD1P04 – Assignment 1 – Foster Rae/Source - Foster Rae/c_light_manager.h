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
#include <glm.hpp>
#include <vector>

// === LIGHT STRUCTS ===
struct s_point_light {
    glm::vec3 position;
    glm::vec3 color;
    // Attenuation values.
    float constant;
    float linear;
    float quadratic;
};

struct s_directional_light {
    glm::vec3 direction;
    glm::vec3 color;
};

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
     */
    void update_lights_in_shader(unsigned int shader_program);

private:

    std::vector<s_point_light> point_lights_; // Vector of point lights in the scene.
    s_directional_light dir_light_;
    s_spotlight spot_light_;
    // Light toggles.
    bool point_lights_on_;
    bool dir_light_on_;
    bool spot_light_on_;
};
