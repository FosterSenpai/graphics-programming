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
/**
 * TODO: Exercise
 * Create and show a 3D Cube object using perspective projection.
 *
 * Create a camera class which holds the view and projection matrices.
 *     Change to Orthographic projection to see the difference. (Remember that orthographic projection needs to be scaled up)
 *
 *	Create a mesh class and spawn multiple cubes on the screen at once.
 *		Mesh class can be like a blueprint/template with instructions on how to render a certain structure (object).
 *			Make sure it contains the VAO, VBO, EBO, and the draw function.
 */


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
c_quad background_quad(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(2.0f), false);
c_quad quad1(glm::vec3(-0.55f, -0.18f, 0.0f), 0.0f, glm::vec3(1.0f), false);
c_quad quad2(glm::vec3(0.55f, -0.18f, 0.0f), 0.0f, glm::vec3(1.0f), false);
c_quad coin(glm::vec3(0.8f, 0.8f, 0.0f), 0.0f, glm::vec3(0.2f), true);

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
	background_quad.init();
	quad1.init();
	quad2.init();
	coin.init();

	// ==== ADD TEXTURES HERE ====
	background_quad.add_texture("Resources/Textures/s2U4Qp6.PNG");
	quad1.add_texture("Resources/Textures/left_hand.PNG");
	quad2.add_texture("Resources/Textures/right_hand.PNG");
	coin.add_texture("Resources/Textures/coin/tile000.PNG");
	coin.add_texture("Resources/Textures/coin/tile001.PNG");
	coin.add_texture("Resources/Textures/coin/tile002.PNG");
	coin.add_texture("Resources/Textures/coin/tile003.PNG");
	coin.add_texture("Resources/Textures/coin/tile004.PNG");
	coin.add_texture("Resources/Textures/coin/tile005.PNG");
	coin.add_texture("Resources/Textures/coin/tile006.PNG");
	coin.add_texture("Resources/Textures/coin/tile007.PNG");
	coin.add_texture("Resources/Textures/coin/tile008.PNG");
	coin.add_texture("Resources/Textures/coin/tile009.PNG");
	coin.add_texture("Resources/Textures/coin/tile010.PNG");
	coin.add_texture("Resources/Textures/coin/tile011.PNG");
	coin.add_texture("Resources/Textures/coin/tile012.PNG");
	coin.add_texture("Resources/Textures/coin/tile013.PNG");
	coin.add_texture("Resources/Textures/coin/tile014.PNG");


	// Prepare the window.
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}
void update()
{
	// Get the current time.
	current_time = glfwGetTime();

	// ==== APPLY TRANSFORMS HERE ====
	background_quad.update_model_matrix();
	quad1.update_model_matrix();
	quad2.update_model_matrix();
	coin.update_model_matrix();

	// Poll for and process events.
	glfwPollEvents();
}
void render()
{
	// Clear the colour buffer and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use the shader program.
	glUseProgram(shader_program);
	// Send the current time to the shader.
    glUniform1f(glGetUniformLocation(shader_program, "time"), current_time);
	// == START OF RENDERING PIPELINE ==

	// ==== SEND UNIFORMS HERE ====
	// ==== DRAW CALLS HERE ====
	background_quad.draw(shader_program);
	quad1.draw(shader_program);
    quad2.draw(shader_program);
	coin.draw(shader_program);

	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}
