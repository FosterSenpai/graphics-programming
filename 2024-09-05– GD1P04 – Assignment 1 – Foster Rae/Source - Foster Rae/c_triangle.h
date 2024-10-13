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
	void init() override;
	void draw() override;
};