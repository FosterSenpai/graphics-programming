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
	 * @param pos The position of the triangle. (glm::vec3)
	 * @param rot_angle The rotation angle of the triangle. (float)
	 * @param scl_factor The scale factor of the triangle. (glm::vec3)
	 */
    c_triangle(const glm::vec3& pos, float rot_angle, const glm::vec3& scl_factor)
        : c_shape(pos, rot_angle, scl_factor) {}

	void init() override;
	void draw(GLuint shader_program) override;
};