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
#include "c_mesh.h"

class c_cube {
public:
    // == Constructors and Destructors ==
    c_cube(const std::vector<s_texture>& textures);

    // == Public Methods ==
    /**
	 * @brief Draws the cube.
	 * @param shader_program The shader program to use.
	 */
    void draw(GLuint shader_program);

private:
    // == Private Members ==
    c_mesh mesh_; // The mesh of the cube. Holds the vertices, indices, and textures.
};