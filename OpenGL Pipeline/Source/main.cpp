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
// ======================================================================
// Includes
// ======================================================================

#include <iostream>
#include <vector>
#include "c_shader_loader.h"

// ======================================================================
// Globals
// ======================================================================

GLFWwindow* window = nullptr;    // Pointer to the GLFW window.
GLuint program_fixed_tri; 		 // First Fixed Triangle.

int window_height = 800;
int window_width = 800;

// Dynamic Data Globals
GLuint program_position_only;
GLuint vbo_tri;

// ======================================================================
// Data Structures
// ======================================================================

struct s_vertex
{
	float x, y, z;
};

// ======================================================================
// Function Declarations
// ======================================================================

void initial_setup();
void update();
void render();

// ======================================================================
// Main Function
// ======================================================================

int main()
{
	// ***************
	// Initialise GLFW
	// ***************

	/*
	 * This function must be called before any other GLFW functions are called.
	 * It initializes the GLFW library,to version 4.6, and sets the OpenGL profile to be compatible.
	 */
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	/*
	 * Create a GLFW controlled window with a 800x800 resolution and a title of "Graphics Framework".
	 */
	window = glfwCreateWindow(window_width, window_height, "Graphics Framework", nullptr, nullptr);

	if (window == nullptr) 	   		   // Check if the window was created successfully, if not terminate the program.
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);    // Make the window the current context.

	// ***************
	// Initialise GLEW
	// ***************

	/*
	* This function must be called after the initialization of the GLFW window and before any OpenGL functions are called.
	* This populates all the OpenGL function pointers with the correct functions that are supported by the graphics card.
	*/
	if (glewInit() != GLEW_OK) 	       // Check if GLEW was initialised successfully, if not terminate the program.
	{
		std::cout << "Failed to initialise GLEW" << '\n';
		std::cin.get();

		glfwTerminate();
		return -1;
	}

	// **************************************
	// Setup the initial state of the program
	// **************************************

	initial_setup();

	// *********
	// Main Loop
	// *********

	while (glfwWindowShouldClose(window) == false)    // While window is open, keep running the program.
	{
		update();    // Update all objects and run the processes.
		render();    // Render the objects.
	}

	// *********************
	// Terminate the program
	// *********************

	glfwTerminate();    // Terminate the GLFW window.
	return 0;
}

// ======================================================================
// Function Definitions
// ======================================================================

/**
 * @brief
 *      Handles the initial setup of the program.
 *
 *  @details
 *      This function is called once at the start of the program and is used to set up the initial state of the program.
 *      This includes setting up the window, creating the program object, loading the shaders, and creating the VBO.
 */
void initial_setup()
{
	// ***********************************
	// Load shaders, Create program object
	// ***********************************

	program_fixed_tri = c_shader_loader::create_program("Resources/Shaders/FixedTriangle.vert",
	                                                    "Resources/Shaders/FixedColor.frag");

	// Generate the VBO for a Triangle
	// todo: Still need to implement dynamic data triangle, running off static data file right now.
	//program_position_only = c_shader_loader::create_program("Resources/Shaders/PositionOnly.vert",
	//                                                        "Resources/Shaders/FixedColor.frag");
	//std::vector<s_vertex> verticesTri;
	//verticesTri.push_back({0.0f, 0.0f, 0.0f});
	//verticesTri.push_back({-0.5f, 0.8f, 0.0f});
	//verticesTri.push_back({0.5f, 0.8f, 0.0f});

	// ******************
	// Create VBO buffers
	// ******************

	glGenBuffers(1, &vbo_tri);    						// Generate a buffer object name.
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tri);    // Bind the buffer object to the context.

	/*
	 * GlBufferData
	 * Second argument wants the size of the data in Bytes but vector.size() is an int
	 * I multiplied the vector.size() by the byte size of the first vertex, so the warning is fixed, dont worry about it.
	 */
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri[0]) * verticesTri.size(), verticesTri.data(), GL_STATIC_DRAW);

	// ********************************
	// Prepare the window for rendering
	// ********************************

	glClearColor(0.56f, 0.57f, 0.60f, 1.0f);    // Set the color of the window when the buffer is cleared. Grey.
	glViewport(0, 0, window_width, window_height);             // Maps the range of the window size to NDC space. This is the area that will be rendered to the screen. -1 to 1 on all axes.
}
/**
 * @brief
 *      Update
 *
 * @details
 *       This function is called once per frame and is used to update the state of the program.
 */
void update()
{
	glfwPollEvents();    // Poll for events. This will update the state of the program and respond to any user input. 
}
/**
 * @brief
 *       Render the scene
 * @details
 * 		Renders all the objects in the scene, this is called once per frame with the update function.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear the colour and depth buffers.
	// ********************************
	// Start of the rendering pipeline.
	// ********************************

	// --------------------------------
	// Program 1: Fixed Triangle: Start
	// --------------------------------
	glUseProgram(program_fixed_tri);                     	    // Use the program object that was created and loaded with the shaders.
	glDrawArrays(GL_TRIANGLES, 0, 3);           // Draw the triangle.
	glPolygonMode(GL_FRONT, GL_FILL);                 // Draw the triangle in fill mode.

	// If the left mouse button is pressed, draw the triangle in wireframe mode.
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	// ------------------------------
	// Program 1: Fixed Triangle: End
	// ------------------------------

	// *****************************
	// End of the rendering pipeline
	// *****************************
	glUseProgram(0);     // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window);    // Swap the front and back buffers. End of the rendering pipeline.
};
