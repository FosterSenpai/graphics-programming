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
 *			Make sure it contains the vao, vbo, EBO, and the draw function.
 */


#include <stb_image.h>
#include "c_graphics_utils.h"
#include <gtc/type_ptr.hpp>
#include "c_structs.h"
#include "c_camera.h"

// == Global Variables ==
GLFWwindow* window;
GLfloat current_time;
GLfloat previous_time = 0.0f;
GLfloat delta_time;
GLuint shader_program;
c_camera camera;
GLuint vao, vbo, ebo;

// Define the mouse callback function.
void mouse_callback(GLFWwindow* glfw_window, double x_pos, double y_pos)
{
    camera.mouse_input(window, x_pos, y_pos);
}

// ==== CREATE SHAPES HERE ====

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
/**
 * @brief Handles input processing.
 */
void process_input(void* glfw_window);

int main()
{
	// Initialize GLFW.
	c_graphics_utils::initialize_glfw();

	// Create a window.
	window = c_graphics_utils::create_window(camera.get_window_width(), camera.get_window_height(), "OpenGL Pipeline");
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
    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set to general blend.
	// Flip the images vertically.
	stbi_set_flip_vertically_on_load(true);
    // Hide & capture the cursor.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse callback function.
    glfwSetCursorPosCallback(window, mouse_callback); // Add this line
    // Create the shader program.
	shader_program = c_shader_loader::create_program("test.vert", "test.frag");

	// === LOAD TEXTURES HERE ===

    // Prepare the window.
    glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
    glViewport(0, 0, camera.get_window_width(), camera.get_window_height()); // Maps the range of the window size to NDC space.
}
void update()
{
	// Update Time.
	current_time = static_cast<GLfloat>(glfwGetTime());
	delta_time = current_time - previous_time;
	previous_time = current_time;
	// Process Input.
	process_input(window);
	camera.process_input(window, delta_time);
	// Update the camera.
	camera.update(delta_time);
	// Poll for and process events.
	glfwPollEvents();
}
void render()
{
	// Clear the colour buffer and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Send the current time to the shader.
    glUniform1f(glGetUniformLocation(shader_program, "time"), current_time);

	// == START OF RENDERING PIPELINE ==

	// ==== DRAW CALLS HERE ====

	// Use the shader program.
	glUseProgram(shader_program);

    // pass transformation matrices to the shader
    c_shader_loader::setMat4(shader_program,"projection", camera.get_projection_matrix());
    c_shader_loader::setMat4(shader_program,"view", camera.get_view_matrix());

	// Bind the vao before drawing.
	glBindVertexArray(vao);

	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the vao.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}

void process_input(void* glfw_window)
{
	// Close the window if the escape key is pressed.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
