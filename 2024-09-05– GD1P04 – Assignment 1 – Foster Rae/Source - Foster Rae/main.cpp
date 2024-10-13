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
#include <gtc/type_ptr.hpp>
#include "c_quad.h"
#include "c_triangle.h"

// == Global Variables ==
int window_width = 800;
int window_height = 800;
GLFWwindow* window;
GLfloat current_time;
GLuint shader_program;

// ==== CREATE SHAPES HERE ====
c_quad quad1(glm::vec3(-0.5f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f));
c_quad quad2(glm::vec3(0.5f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f));
c_triangle triangle(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f));

// == Function Prototypes ==
/**
 * @brief Sets up the pipeline, Handles things that only need to be done once.
 */
void initial_setup();
/**
 * @brief Handles updating objects, variables and processing/calculation functions.
 */
void update();
/**
 * @brief Handles drawing objects and sending information to the shaders.
 */
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

	// Create the shader program.
	shader_program = c_shader_loader::create_program("vertex_shader.vert", "fragment_shader.frag");

	// ==== INIT OBJECTS HERE ====
	quad1.init();
	quad2.init();
	triangle.init();

	// ==== ADD TEXTURES HERE ====
	quad1.add_texture("Resources/Textures/Run (1).PNG");
	quad2.add_texture("Resources/Textures/Run (2).PNG");
	triangle.add_texture("Resources/Textures/Run (3).PNG");

	// Prepare the window.
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}
void update()
{
	// ==== APPLY TRANSFORMS HERE ====
	quad1.update_model_matrix();
	quad2.update_model_matrix();
	triangle.update_model_matrix();

	// Poll for and process events.
	glfwPollEvents();
}
void render()
{
	// Clear the colour buffer and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use the shader program.
	glUseProgram(shader_program);
	// == START OF RENDERING PIPELINE ==

	// ==== DRAW CALLS HERE ====
	quad1.draw(shader_program);
    quad2.draw(shader_program);
    triangle.draw(shader_program);

	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}
