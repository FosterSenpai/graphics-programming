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

class c_shape
{
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void add_texture(const char* texture_path);
	virtual ~c_shape() = default;
protected:
	GLuint vao_ = 0, vbo_ = 0, ebo_ = 0;
	std::vector<GLfloat> vertices_; //Vector for vertex data.
	std::vector<GLuint> indices_;   //Vector for indices.
	std::vector<GLuint> textures_;  //Vector for textures.
};
