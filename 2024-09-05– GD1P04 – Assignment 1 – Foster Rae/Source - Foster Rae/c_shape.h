﻿// /***********************************************************************
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
#include "gtc/type_ptr.hpp"
#include <string>

class c_shape
{
public:
	// == Public Methods ==
	/**
	 * @brief Initializes the shapes necessary data.
	 */
	virtual void init() = 0;
	/**
	 * @brief Draws the shape.
	 * @param shader_program A reference to the shader program.
	 */
	virtual void draw(GLuint shader_program) = 0;
	/**
	 * @brief Adds a texture to the shapes texture vector.
	 * @param texture_path The path to the texture.
	 */
	virtual void add_texture(const char* texture_path);
	virtual ~c_shape();

	// == Transformation Methods ==
	void set_position(glm::vec3 pos) { position = pos; }
	void set_rotation(float rot) { rotation = rot; }
	void set_scale(glm::vec3 scl) { scale = scl; }
	glm::vec3 get_position() const { return position; }
	float get_rotation() const { return rotation; }
	glm::vec3 get_scale() const { return scale; }
	/**
	 * @brief Update the model matrix of the shape.
	 */
	void update_model_matrix();

	bool is_animated = false;
protected:
	/**
	 * @brief Constructs a Shape and sets the transforms.
	 * @note The model matrix is initialized to an identity matrix.
	 *
	 * @param position The position of the shape. (glm::vec3)
	 * @param rotation The rotation of the shape. (float)
	 * @param scale The scale of the shape. (glm::vec3)
	 *  @param is_animated Whether the shape is animated or not. (bool)
	 */
    c_shape(const glm::vec3& position, float rotation, const glm::vec3& scale, bool is_animated)
        : position(position), rotation(rotation), scale(scale), model_matrix(1.0f), is_animated(is_animated) {}

	// Transformation variables.
	glm::vec3 position;
    float rotation;
    glm::vec3 scale;
    glm::mat4 model_matrix;

	GLuint vao_ = 0, vbo_ = 0, ebo_ = 0;
	std::vector<GLfloat> vertices_; //Vector for vertex data.
	std::vector<GLuint> indices_;   //Vector for indices.
	std::vector<GLuint> textures_;  //Vector for textures.
};
