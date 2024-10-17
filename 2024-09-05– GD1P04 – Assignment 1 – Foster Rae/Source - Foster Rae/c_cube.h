// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_cube.h
// Description : Class that defines a cube object.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once

#include <ext/matrix_transform.hpp>

#include "Dependencies/GLM/glm.hpp"
#include "c_mesh.h"

class c_cube {
public:
    // == Constructors and Destructors ==
    /**
     * @brief Construct a new c_cube object.
     * @param textures A vector of textures to apply to the cube.
     * @param pos The position of the cube in the world relative to the origin.
     * @param rot The rotation of the cube in degrees.
     * @param scl The scale of the cube.
     */
    c_cube(const std::vector<s_texture>& textures, glm::vec3 pos, float rot, glm::vec3 scl);

    // == Public Methods ==
    /**
	 * @brief Draws the cube.
	 * @param shader_program The shader program to use.
	 */
    void draw(GLuint shader_program);

    // == Public Members ==

	// == Transformation Methods ==
	void set_position(glm::vec3 pos) { position = pos; }
	void set_rotation(float rot) { rotation = rot; }
	void set_scale(glm::vec3 scl) { scale = scl; }
	glm::vec3 get_position() const { return position; }
	float get_rotation() const { return rotation; }
	glm::vec3 get_scale() const { return scale; }

	void update_model_matrix();

private:
    // == Private Members ==
    c_mesh mesh_; // The mesh of the cube. Holds the vertices, indices, and textures.

	// Transformation variables.
	glm::vec3 position;
    float rotation;
    glm::vec3 scale;
    glm::mat4 model_matrix = glm::mat4(1.0f);
};