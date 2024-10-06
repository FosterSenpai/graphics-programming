#include "c_transformations.h"

// == Constructors / Destructors ==
c_transformations::c_transformations(const glm::vec3& position, float rotation_angle, const glm::vec3& scale_factor)
    : position_(position), rotation_angle_(rotation_angle), scale_factor_(scale_factor), model_matrix_(1.0f) {}

// == Public Methods ==
void c_transformations::update()
{
    // Create the transformation matrices.
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_angle_), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale_factor_);
    // Update the model matrix.
    model_matrix_ = translation_matrix * rotation_matrix * scale_matrix;
    
}
glm::mat4 c_transformations::get_model_matrix() const
{
    return model_matrix_;
}
