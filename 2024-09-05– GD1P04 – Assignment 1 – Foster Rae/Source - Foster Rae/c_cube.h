// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_cube.h
// Description : Class that defines a cube object.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <ext/matrix_transform.hpp>
#include "c_camera.h"
#include "Dependencies/GLM/glm.hpp"
#include "c_mesh.h"

class c_cube {
public:

    // == Constructors and Destructors ==
    /**
     * @brief Construct a new c_cube object.
     * @param textures A vector of textures to apply to the cube.
     * @param pos The position of the cube in the world relative to the origin.
     * @param rot The rotation of the cube in degrees.
     * @param scl The scale of the cube.
     */
    c_cube(const std::vector<s_texture>& textures, glm::vec3 pos, float rot, glm::vec3 scl);

    // == Public Methods ==
    /**
	 * @brief Draws the cube.
	 * @param shader_program The shader program to use.
	 *  @param active_texture_index The index of the texture to use.
	 */
    void draw(GLuint shader_program, int active_texture_index);
    /**
     * @brief Updates the model matrix of the cube ready to be sent to the shader.
     * @note Call in the main update loop. 
     */
    void update_model_matrix();
    /**
	 * @brief Moves the cube in the direction relative to the camera.
	 * @param camera The camera object to get the direction from.
	 * @param direction The direction to move the cube.
	 */
    void move(const c_camera& camera, const glm::vec3& direction);

	// == Transformation Methods ==
	void set_position(glm::vec3 pos) { position_ = pos; }
	void set_rotation(float rot) { rotation_ = rot; }
	void set_scale(glm::vec3 scl) { scale_ = scl; }
    void set_active_cube(bool active) { is_active_cube_ = active; } // Set the cube to be controlled by the user.
    void set_speed(float speed) { speed_ = speed; }                 // Set the movement speed of the cube.
	glm::vec3 get_position() const { return position_; }
	float get_rotation() const { return rotation_; }
	glm::vec3 get_scale() const { return scale_; }
	bool get_active_cube() const { return is_active_cube_; }
    std::vector<s_texture> get_textures() const { return mesh_.textures; }


private:
    // == Private Members ==
    c_mesh mesh_; // The mesh of the cube. Holds the vertices, indices, and textures.

	// Transformation variables.
	glm::vec3 position_;
    float rotation_;
    glm::vec3 scale_;
    glm::mat4 model_matrix_ = glm::mat4(1.0f);
    bool is_active_cube_ = false;
    float speed_ = 0.1f;
};
