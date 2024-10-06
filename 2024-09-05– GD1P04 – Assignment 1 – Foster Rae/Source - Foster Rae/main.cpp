/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : main.cpp
Description : Entrance point for the OpenGL pipeline.
Author : Foster Rae
Mail : Foster.Rae@mds.ac.nz
************************************************************************/
#include <stb_image.h>

#include "c_graphics_utils.h"
#include "c_transformations.h"
#include <gtc/type_ptr.hpp>

// == Global Variables ==
int window_width = 800;
int window_height = 800;
GLFWwindow* window;
GLfloat current_time;

// == Objects ==
GLuint quad_program, quad_vao, quad_vbo, quad_ebo, texture_id1, texture_id2;

// == Transformations ==
// Quad 1, Scale by 0.5 and translate to the left.
c_transformations quad1_transformations(glm::vec3(-0.5f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f));
// Quad 2, Scale by 0.5 and translate to the right.
c_transformations quad2_transformations(glm::vec3(0.5f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f));

// == Function Prototypes ==
void initial_setup();
void update();
void render();

int main()
{
	// Initialize GLFW.
	c_graphics_utils::initialize_glfw();
	// Create a window.
	window = c_graphics_utils::create_window(window_width, window_height, "OpenGL Pipeline");
	if (!window)
		{
			return -1; // Return an error code.
		}
	// Initialize GLEW.
	c_graphics_utils::initialize_glew();
	// Set up the pipeline.
	initial_setup();

	// Main loop.
	while (glfwWindowShouldClose(window) == false) // While the window is open.
	{
		update(); // Update all objects and run the processes.
		render(); // Render the objects.
	}

	// Clean up.
	glfwTerminate();
	return 0;
}

void initial_setup()
{
	// Set Global Blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set to general blend.
	// Flip the images vertically.
	stbi_set_flip_vertically_on_load(true);
	// Initialize the quads.
	quad_program = c_graphics_utils::initialize_quads(quad_vao, quad_vbo, quad_ebo, texture_id1, texture_id2);

	// Prepare the window.
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}
void update()
{
	quad1_transformations.update();
	quad2_transformations.update();

	// Poll for and process events.
	glfwPollEvents();

	// Update Variables.
	current_time = static_cast<float>(glfwGetTime());
}
void render()
{
	// Clear the colour buffer and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// == START OF RENDERING PIPELINE ==


	// Use the Quad program.
	glUseProgram(quad_program);
	glBindVertexArray(quad_vao); // Bind the VAO.
	// Quad Program Uniforms.
	GLint model_matrix_location = glGetUniformLocation(quad_program, "model_matrix"); // Get the location of the model matrix.

	// == Textures ==
	// Texture 1.
	glActiveTexture(GL_TEXTURE0); // Activate the texture unit.
	glBindTexture(GL_TEXTURE_2D, texture_id1); // Bind the texture.
	glUniform1i(glGetUniformLocation(quad_program, "texture_0"), 0); // Set the texture unit to the uniform.
	// Set the texture wrapping parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Texture 2.
	glActiveTexture(GL_TEXTURE1); // Activate the texture unit.
	glBindTexture(GL_TEXTURE_2D, texture_id2); // Bind the texture.
	glUniform1i(glGetUniformLocation(quad_program, "texture_1"), 1); // Set the texture unit to the uniform.
	// Set the texture wrapping parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// == Quads ==
	// Quad 1.
	// Pass the model matrix to the shader and draw the quad.
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(quad1_transformations.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	// Quad 2.
	// Pass the model matrix to the shader and draw the quad.
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(quad2_transformations.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}
