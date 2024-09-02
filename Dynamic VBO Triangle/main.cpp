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
#include "c_shader_loader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// ======================================================================
// Globals
// ======================================================================

// ** Window Variables **
GLFWwindow* window = nullptr;    // Pointer to the GLFW window.
int window_height = 800;
int window_width = 800;

// ** Vertex data **
GLfloat vertices_quad[] = {
//Index      // Position			// Color
	/* 0*/	-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f, // Top - Left
	/* 1*/	0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f, // Top - Right
	/* 2*/	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, // Bottom - Right
	/* 3*/	-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f // Bottom - Left
};

// Array of indices for the quad.
GLuint indices_quad[] = {
	0, 1, 2, // First triangle (Top Left, Top Right, Bottom Right)
	0, 2, 3  // Second triangle (Top Left, Bottom Right, Bottom Left)
	// Triangles connected from top left to bottom right.
};

// ** Object IDs **
GLuint program_color_fade;       // Program object for the color fade shader.
GLuint program_world_space;      // Program object for the world space shader.
GLuint vbo_quad;				 // Vertex buffer object for the quad.
GLuint vao_quad;				 // Vertex array object for the quad.
GLuint ebo_quad;				 // Element buffer object for the quad.

// ** Matrices **
// ** Translation **

glm::vec3 quad_position = glm::vec3(0.5f, 0.5f, 0.0f);    // Move the quad to the right and up.
glm::mat4 translation_matrix;	                                 // Translation matrix.

// ** Utility Variables **
GLfloat current_time;            // Current time in seconds.

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
	// Initialise GLFW
	glfwInit(); // Must be called before any other GLFW functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);


	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(window_width, window_height, "Graphics Framework", nullptr, nullptr); // Create a window.
	if (window == nullptr) 	   		   // Check if the window was created successfully, if not terminate the program.
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);    // Make the window the current context.


	// Initialise GLEW
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

	// Set up the initial state of the program
	initial_setup();


	// ** Main Loop **
	while (glfwWindowShouldClose(window) == false)    // While window is open, keep running the program.
	{
		update();    // Update all objects and run the processes.
		render();    // Render the objects.
	}

	// ** End of main loop. Terminate the program **
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
	// Load shaders, Create program object

	program_world_space = c_shader_loader::create_program("Resources/Shaders/PositionOnly.vert",
	                                                      "Resources/Shaders/FadeColor.frag");

	// Generate the vertex array object
	glGenVertexArrays(1, &vao_quad);    // Generate a vertex array object name.
	glBindVertexArray(vao_quad);          // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.

	// Generate the element buffer object
	glGenBuffers(1, &ebo_quad);    																	           // Generate a buffer object name. This will be used to store the vertex data.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);    									           // Bind the VBO to the GL_ARRAY_BUFFER target slot.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);    // Creates and initializes a buffer object's data store.

	// Generate the vertex buffer object
	glGenBuffers(1, &vbo_quad);    																	     // Generate a buffer object name. This will be used to store the vertex data.
	glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);    												 // Bind the VBO to the GL_ARRAY_BUFFER target slot.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);    // Creates and initializes a buffer object's data store.

	// Set the vertex attributes
	/**
	 * NOTE TO SELF:
	 *
	 * glVertexAttribPointer
	 *
	 * This needs to be called after creating the VBO and VAO.
	 * When this is called its binding the VBO to the VAO.
	 * After this when we use the VAO it will use the VBO that is bound to it.
	 *
	 *    @param 1: Index of the vertex attribute that is to be modified.
	 *	  @param 2: Number of components per generic vertex attribute. 3 for x, y, z.
	 *	  @param 3: Data type of each component in the array. GL_FLOAT for x, y, z.
	 *    @param 4: Whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
	 *	  @param 5: Stride. Byte offset between consecutive generic vertex attributes. 6 * sizeof(GLfloat) for the three floats used for x, y, z in each vertex, and the three floats used for r, g, b in each vertex.
	 *	  @param 6: Offset. Offset from the beginning of each vertex. 0/nullptr as the data is at the start of the array. casting to void pointer is just an untyped pointer, dont need to know the type.
	 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr)); // Position attribute
	glEnableVertexAttribArray(0);    // Enable the vertex attribute array, you can have multiple vertex attributes and disable/enable them as needed.

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);    // Enable the color attribute array.


	// Prepare the window for rendering
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
	// ** Calculate Matrices **
	translation_matrix = glm::translate(glm::mat4(1.0f), quad_position);    // Create the translation matrix. Identity matrix, translate by quad_position.

	// ** Update the state of the program **
	glfwPollEvents();    // Poll for events. This will update the state of the program and respond to any user input.
	current_time = static_cast<float>(glfwGetTime());    // Get the current time.
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

	// ** Start of the rendering pipeline **

	glUseProgram(program_world_space);

	// Bind the VAO and draw the quad
	glBindVertexArray(vao_quad);         													  // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.

	// ** Set the uniform variables **

	// ** Time **
	GLint current_time_loc = glGetUniformLocation(program_world_space, "current_time");   // Get the location of the uniform variable in the shader.
	glUniform1f(current_time_loc, current_time);	                                          // Set the value of the uniform variable.
	// ** Translation **
	GLint translation_matrix_location = glGetUniformLocation(program_world_space, "translation_matrix");             // Get the location of the uniform variable in the shader.
	glUniformMatrix4fv(translation_matrix_location, 1, GL_FALSE, glm::value_ptr(translation_matrix));    // Set the value of the uniform variable.


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);          // Draw the elements using the indices in the element buffer object. each index is a vertex.


	// ** End of the rendering pipeline **

	glBindVertexArray(0);  // Unbind the VAO.
	glUseProgram(0);     // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window);    // Swap the front and back buffers. End of the rendering pipeline.
};
