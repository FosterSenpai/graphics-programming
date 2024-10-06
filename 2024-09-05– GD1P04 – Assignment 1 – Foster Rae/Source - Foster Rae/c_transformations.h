// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_transformations.h
// Description : Handles the transformations of objects.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

/**
 * @class c_transformations
 * @brief Handles the transformations of objects.
 */
class c_transformations
{
public:

	// == Constructors / Destructors ==
	/**
	 * @brief Constructs the object with the given parameters.
	 *
	 * @param position The position of the object.
	 * @param rotation_angle The rotation angle of the object.
	 * @param scale_factor The scale factor of the object.
	 * @note the model matrix is initialized to the identity matrix.
	 */
	c_transformations(const glm::vec3& position, float rotation_angle, const glm::vec3& scale_factor);

	// == Public Methods ==
	/**
	 * @brief Updates the model matrix of the object.
	 */
	void update();
	/**
	 * @brief Returns the model matrix of the object.
	 *
	 * @return The model matrix. (glm::mat4)
	 */
	glm::mat4 get_model_matrix() const;

private:

	// == Members ==
    glm::vec3 position_;
    float rotation_angle_;
    glm::vec3 scale_factor_;
    glm::mat4 model_matrix_;
};
