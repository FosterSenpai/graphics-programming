// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_triangle.h
// Description : Class for a triangle shape.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include "c_shape.h"

class c_triangle : public c_shape
{
public:
	/**
	 * @brief Constructs a triangle and sets the transforms.
	 *
	 * @param position The position of the triangle. (glm::vec3)
	 * @param rotation_angle The rotation angle of the triangle. (float)
	 * @param scale_factor The scale factor of the triangle. (glm::vec3)
	 */
	c_triangle(const glm::vec3& position, float rotation_angle, const glm::vec3& scale_factor)
        : c_shape(position, rotation_angle, scale_factor) {}

	void init() override;
	void draw(GLuint shader_program) override;
};