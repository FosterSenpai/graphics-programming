// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_structs.h
// Description : Contains common types used by the c_mesh class.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once

#include <glm.hpp>
#include <string>

/**
 * @brief Vertex struct to hold the vertex data.
 * @param position The position of the vertex.
 * @param normal The normal of the vertex.
 * @param tex_coords The texture coordinates of the vertex.
 *
 * @note Stored in memory as:\n
 * [ position.x, position.y, position.z, normal.x, normal.y, normal.z, tex_coords.x, tex_coords.y ]
 */
struct s_vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

/**
 * @brief Texture struct to hold the texture id and type.
 * @param id The texture id.
 * @param type The texture type. (diffuse, specular, etc.)
 */
struct s_texture {
    unsigned int id;
    std::string type;
};