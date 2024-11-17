// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_sky_box.h
// Description : Skybox class to render a skybox around the scene.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include <vector>
#include <string>
#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLEW/glew.h"

class c_skybox {
public:
    /**
	 * @brief Constructor for the Skybox class.
	 * @param faces A vector of file paths to the skybox textures.
	 */
    c_skybox(const std::vector<std::string>& faces);
    /**
     * @brief Draws the skybox.
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    void setup_skybox();
    void load_cubemap(const std::vector<std::string>& faces);

    GLuint skybox_vao_, skybox_vbo_;
    GLuint cubemap_texture_;
    GLuint shader_program_;
};
