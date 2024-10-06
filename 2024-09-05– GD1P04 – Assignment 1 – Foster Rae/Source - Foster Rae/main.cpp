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
#include "c_graphics_utils.h"
#include "c_transformations.h"
#include <gtc/type_ptr.hpp>

// == Global Variables ==
int window_width = 800;
int window_height = 800;
GLFWwindow* window;
GLfloat current_time;

// == TODO: Objects ==
// TODO: Transformations.

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
	// TODO: Set up objects.

	// Prepare the window.
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}
void update()
{
	//TODO: Update objects.

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

	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}
