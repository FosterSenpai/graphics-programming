// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_mesh.h
// Description : Class to handle the mesh data and rendering.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include <vector>
#include <glew.h>
#include <glm.hpp>
#include "c_structs.h"

class c_mesh
{
public:

	// == Constructors and Destructors ==
	c_mesh() = default; // Default constructor
    c_mesh(const std::vector<s_vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<s_texture>& textures);

	// == Public Methods ==
	/**
	 * @brief Draws the mesh.
	 * @note Textures must be names as: texture_diffuseN, texture_specularN or nothing will be loaded.
	 *
	 * @param program_id The shader program to use.
	 */
	void draw(GLuint program_id, int active_texture_index);

	// == Public Members ==
	GLuint vao;
	// Mesh data
    std::vector<s_vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<s_texture> textures;

private:

	// == Private Methods ==
	/**
	 * @brief Sets up the mesh data.
	 * @note This is called in the constructor.
	 */
	void setup_mesh();
	
	// == Private Members ==
	// VBO, VAO, EBO
	GLuint vbo_, ebo_;

};
