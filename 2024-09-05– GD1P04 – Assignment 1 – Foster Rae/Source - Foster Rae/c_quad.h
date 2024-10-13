// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_quad.h
// Description : Class for a quad shape.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include "c_shape.h"

class c_quad : public c_shape
{
public:
	void init() override;
	void draw() override;
};
