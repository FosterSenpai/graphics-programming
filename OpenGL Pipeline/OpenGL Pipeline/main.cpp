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
#include <iostream>
#include <vector>
#include "c_shader_loader.h"

// Global Variables
GLFWwindow* window = nullptr; // Pointer to the GLFW window.
GLuint program_fixed_tri; // First Fixed Triangle.

// Dynamic Data Globals
GLuint program_position_only;
GLuint vbo_tri;

struct s_vertex
{
	float x, y, z;
};

// Function Prototypes
void initial_setup();
void update();
void render();

// === Main Function ===
int main()
{
	// === Initialise GLFW ===
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	window = glfwCreateWindow(800, 800, "Graphics Framework", nullptr, nullptr);
	// Create a GLFW controlled window with the specified dimensions and title.
	if (window == nullptr) // Check if the window was created successfully, if not terminate the program.
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Make the window the current context.


	// === Initialise GLEW ===
	/*
	This function must be called after the initialization of the GLFW window and before any OpenGL functions are called.
	This populates all the gl-prefixed functions with the correct calls based on the current pc hardware and drivers.
	*/
	if (glewInit() != GLEW_OK) // Check if GLEW was initialised successfully, if not terminate the program.
	{
		std::cout << "Failed to initialise GLEW" << '\n';
		system("pause");

		glfwTerminate();
		return -1;
	}

	// === Set up the initial elements of the program ===
	initial_setup();

	// === Main Loop ===
	while (glfwWindowShouldClose(window) == false) // While window is open, keep running the program.
	{
		update(); // Update all objects and run the processes.
		render(); // Render the objects.
	}

	// === Terminate the program ===
	glfwTerminate(); // Terminate the GLFW window.
	return 0; // Return 0 to the operating system to indicate the program has run successfully.
}

// Function Definitions
/**
 * @brief
 *     Handles the initial setup of the program.
 *
 *  @details
 *     This function is called once at the start of the program and is used to set up the initial state of the program.
 *     This includes setting up the window, creating the program object, loading the shaders, and creating the VBO.
 */
void initial_setup()
{
	program_fixed_tri = c_shader_loader::create_program("Resources/Shaders/FixedTriangle.vert",
	                                                    "Resources/Shaders/FixedColor.frag");
	// Create the program object and load the shaders.

	program_position_only = c_shader_loader::create_program("Resources/Shaders/PositionOnly.vert",
	                                                        "Resources/Shaders/FixedColor.frag");

	// Generate the VBO for a Triangle
	// todo: Still need to implement dynamic data triangle, running off static data file right now.
	std::vector<s_vertex> verticesTri;
	verticesTri.push_back({0.0f, 0.0f, 0.0f});
	verticesTri.push_back({-0.5f, 0.8f, 0.0f});
	verticesTri.push_back({0.5f, 0.8f, 0.0f});

	glGenBuffers(1, &vbo_tri);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tri);
	/*
	 * GlBufferData
	 * Second argument wants the size of the data in Bytes but vector.size() is an int
	 * I multiplied the vector.size() by the byte size of the first vertex, so the warning is fixed, dont worry about it.
	 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri[0]) * verticesTri.size(), verticesTri.data(), GL_STATIC_DRAW);


	/**
	 *glClearColor
	 *This function only needs to be called once at the start of the program.
	 *but can be called multiple times to change the clear colour.
	 */
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the colour after clearing color buffers to a light grey.

	glViewport(0, 0, 800, 800);
	// Maps the range of the window size to NDC space. This is the area that will be rendered to the screen. -1 to 1 on all axes.
}

/**
 * @brief Update
 * @details This function is called once per frame and is used to update the state of the program.
 */
void update()
{
	glfwPollEvents(); // Poll for any events that have occurred.
	// Needs to be called once per frame to update the state of the program and register any input/changes.
}

/**
 * @brief Render
 * @details Renders all the objects in the scene.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Clear the colour and depth buffers. Start of the rendering pipeline.

	glUseProgram(program_fixed_tri); // Use the program object that was created and loaded with the shaders.
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// Draw the triangle. 3 vertices, 1 triangle. Draw calls must be between glClear and glfwSwapBuffers.

	glPolygonMode(GL_FRONT, GL_FILL); // Draw the triangle in fill mode.
	// if click on window, change color of triangle
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT, GL_LINE); // Draw the triangle in wireframe mode.
	}

	// Put all rendering code here.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
};
