#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "c_cube.h"
#include "c_shader_loader.h"

c_cube::c_cube(const std::vector<s_texture>& textures, glm::vec3 pos, float rot, glm::vec3 scl)
    : mesh_(c_mesh(
        {
			// Front face
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			// Back face
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
			{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			// Right face
			{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			// Left face
			{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        	{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        	{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			// Top face
			{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			// Bottom face
			{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}
        },
        {
			 0,  1,  3, // Front face
			 1,  2,  3,
			 4,  5,  7, // Back face
			 5,  6,  7,
			 8,  9, 11, // Right face
			 9, 10, 11,
			12, 13, 15, // Left face
			13, 14, 15,
			16, 17, 19, // Top face
			17, 18, 19,
			20, 21, 23, // Bottom face
			21, 22, 23
        },
        textures)), position_(pos), rotation_(rot), scale_(scl)
{} // This looks super weird, but it works. It's a member initializer list.

void c_cube::draw(GLuint shader_program) {
	// Send the model matrix to the shader.
	update_model_matrix();
	c_shader_loader::set_mat_4(shader_program, "transform", model_matrix_);
	// Draw the cube.
    mesh_.draw(shader_program);
}

void c_cube::update_model_matrix()
{
	// Update the model matrix.
	model_matrix_ = glm::mat4(1.0f);
    model_matrix_ = glm::translate(model_matrix_, position_);
    model_matrix_ = glm::rotate(model_matrix_, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
    model_matrix_ = glm::scale(model_matrix_, scale_);
}

void c_cube::move(const c_camera& camera, const glm::vec3& direction)
{
    if (is_active_cube_)
    {
        glm::vec3 scaled_direction = direction * speed_; // Scale the direction by the speed factor

        if (camera.get_is_target_camera() || camera.is_manual_camera())
        {
            // Move along the orbital camera's view matrix.
            glm::vec3 right = glm::normalize(glm::cross(camera.get_look_dir(), camera.get_up_dir()));
            glm::vec3 forward = glm::normalize(glm::cross(camera.get_up_dir(), right));
            position_ += scaled_direction.x * right + scaled_direction.y * camera.get_up_dir() + scaled_direction.z * forward;
        }
        else
        {
            // Move along the free camera's view matrix.
            glm::vec3 right = glm::normalize(glm::cross(camera.get_look_dir(), camera.get_up_dir()));
            position_ += scaled_direction.x * right + scaled_direction.y * camera.get_up_dir() + scaled_direction.z * camera.get_look_dir();
        }
    }
}
