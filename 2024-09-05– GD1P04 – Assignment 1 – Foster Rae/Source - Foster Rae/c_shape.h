// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_shape.h
// Description : Base class to be derived from for shapes.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include <glew.h>
#include <vector>
#include "c_transformations.h"
#include "gtc/type_ptr.hpp"

class c_shape
{
public:
	virtual void init() = 0;
	/**
	 * @brief Draws the shape.
	 * @param shader_program A reference to the shader program.
	 */
	virtual void draw(GLuint shader_program) = 0;
	virtual void add_texture(const char* texture_path);
	virtual ~c_shape() = default;
protected:
	/**
	 * @brief Constructs a Shape and sets the transforms.
	 *
	 * @param position The position of the quad. (glm::vec3)
	 * @param rotation_angle The rotation angle of the quad. (float)
	 * @param scale_factor The scale factor of the quad. (glm::vec3)
	 */
    c_shape(const glm::vec3& position, float rotation_angle, const glm::vec3& scale_factor)
    : transformations_(position, rotation_angle, scale_factor) {}

	GLuint vao_ = 0, vbo_ = 0, ebo_ = 0;
	std::vector<GLfloat> vertices_; //Vector for vertex data.
	std::vector<GLuint> indices_;   //Vector for indices.
	std::vector<GLuint> textures_;  //Vector for textures.
	c_transformations transformations_; // Object holding all transforms of the shape.
};
