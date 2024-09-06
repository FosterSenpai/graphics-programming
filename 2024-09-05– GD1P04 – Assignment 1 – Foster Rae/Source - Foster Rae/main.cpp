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
#include "c_shader_loader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"
// ***** Globals *****

// ** Window Variables **
GLFWwindow* window = nullptr;
int window_height = 800;
int window_width = 800;

// ** Object IDs **
GLuint program_hexagon;          // Program object for the quad shader.
GLuint program_texture;          // Program object for the texture shader.
GLuint vbo_quad;				 // Vertex buffer object for the quad.
GLuint vao_quad;				 // Vertex array object for the quad.
GLuint ebo_quad;				 // Element buffer object for the quad.
GLuint vbo_hexagon;				 // Vertex buffer object for the hexagon.
GLuint vao_hexagon;				 // Vertex array object for the hexagon.
GLuint ebo_hexagon;				 // Element buffer object for the hexagon.

// ** Texture IDs **
GLuint texture_alien; // Texture ID for the first texture.

// ***** Quad Matrices *****
// * Translation *
glm::vec3 quad_position1 = glm::vec3(-0.35f, -0.5f, 0.0f); // Move the quad to the bottom left.
glm::vec3 quad_position2 = glm::vec3(0.4f, -0.5f, 0.0f);  // Move the quad to the bottom right.
glm::mat4 translation_matrix; // Translation matrix.

// * Rotation *
float quad_rotation_angle1 = 0;   // No rotation.
float quad_rotation_angle2 = 0;   // No rotation.
glm::mat4 rotation_matrix;        // Rotation matrix.

// * Scaling *
glm::vec3 quad_scale1 = glm::vec3(0.5f, 0.5f, 1.0f);   // Scale the quad down to half its size.
glm::vec3 quad_scale2 = glm::vec3(0.5f, 0.5f, 1.0f);
glm::mat4 scale_matrix;                                       // Scale matrix.

// ** Model Matrices **
glm::mat4 model_matrix1; // Model matrix for the first quad.
glm::mat4 model_matrix2; // Model matrix for the second quad.

// ***** Hexagon Matrices *****
// * Translation *
glm::vec3 hexagon_position1 = glm::vec3(-0.35f, 0.5f, 0.0f);    // Move the hexagon to the top left.
glm::vec3 hexagon_position2 = glm::vec3(0.45f, 0.5f, 0.0f);     // Move the hexagon to the top right.
glm::mat4 hexagon_translation_matrix;                                 // Translation matrix.

// * Rotation *
float hexagon_rotation_angle1 = 0;
float hexagon_rotation_angle2 = 0;   // No rotation, will be updated in the shader.
glm::mat4 hexagon_rotation_matrix;   // Rotation matrix.

// * Scaling *
glm::vec3 hexagon_scale1 = glm::vec3(0.5f, 0.5f, 1.0f);   // Scale the hexagon down to half its size.
glm::vec3 hexagon_scale2 = glm::vec3(0.3f, 0.3f, 1.0f);   // Scale the hexagon down to 30% of its size.
glm::mat4 hexagon_scale_matrix;                                       // Scale matrix.

// ** Model Matrices **
glm::mat4 hexagon_model_matrix1; // Model matrix for the first hexagon.
glm::mat4 hexagon_model_matrix2; // Model matrix for the second hexagon.

// ** Color array **
glm::vec3 colors[] = {
    glm::vec3(1.0f, 0.0f, 0.0f), // Red
    glm::vec3(0.0f, 1.0f, 0.0f), // Green
    glm::vec3(0.0f, 0.0f, 1.0f), // Blue
    glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
    glm::vec3(1.0f, 0.0f, 1.0f), // Magenta
    glm::vec3(0.0f, 0.0f, 0.0f)  // Black
};

// ** Utility Variables **
GLfloat current_time; // Current time in seconds.

// ***** Function Declarations *****

/**
 * @brief
 *      Handles the initial setup of the program.
 *
 *  @details
 *      This function is called once at the start of the program and is used to set up the initial state of the program.
 *      This includes setting up the window, creating the program object, loading the shaders, and creating the VBO.
 */
void initial_setup();
/**
 * @brief
 *      Initialize Hexagons
 *
 * @details
 *      This function initializes the hexagon data and objects.
 *
 * @return
 *      Returns the program ID.
 */
GLuint initialize_hexagons();
/**
 * @brief
 *      Initialize Quads
 *
 * @details
 *      This function initializes the quad data and objects.
 *
 * @return
 *      Returns the program ID.
 */
GLuint initialize_quads();
/**
 * @brief
 *      Update
 *
 * @details
 *       This function is called once per frame and is used to update the state of the program.
 */
void update();
/**
 * @brief
 *       Render the scene
 * @details
 * 		Renders all the objects in the scene, this is called once per frame with the update function.
 */
void render();
/**
 * @brief
 *      Initialize GLFW
 *
 * @details
 *      This function initializes GLFW and sets the window hints.
 */
void initialize_glfw();
/**
 * @brief
 *      Initialize GLEW
 *
 * @details
 *      This function initializes GLEW and checks if it was successful.
 *
 * @return
 *      Returns an error code if GLEW failed to initialize.
 */
int initialize_glew();


// ***** Main Function *****

int main()
{
	// *** Initialise GLFW ***
	initialize_glfw();

	//  *** Create a window context ***
	window = glfwCreateWindow(window_width, window_height, "Graphics Framework", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

    // *** Initialise GLEW ***
    if (initialize_glew() == -1)
    {
        return -1; // Return an error code if GLEW initialization failed. (I feel like I might be making this check twice)
    }

	// *** Initial Setup ***
	initial_setup();

	// *** Main Loop ***
	while (glfwWindowShouldClose(window) == false)    // While window is open, keep running the program.
	{
		update(); // Update all objects and run the processes.
		render(); // Render the objects.
	}

	// *** End of main loop. Terminate the program ***
	glfwTerminate();
	return 0;
}


// ***** Function Definitions *****

void initial_setup()
{
	// ** Create Program, Load Shaders, Set up data **
	program_texture = initialize_quads();
	program_hexagon = initialize_hexagons();
	// ** Prepare the window **
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}

GLuint initialize_hexagons()
{
	GLuint program = c_shader_loader::create_program("Resources/Shaders/PositionOnly.vert",
	                                                         "Resources/Shaders/FadeColor.frag");
	// ** Vertex data **
	GLfloat vertices_hexagon[] = {
		//Index      // Position		    // Color
		/* 0*/	     0.0f,   0.0f, 0.0f,	    0.0f, 0.0f, 0.0f, // Center
		/* 1*/	    -0.5f,  0.85f, 0.0f,	    0.0f, 0.0f, 0.0f, // Top left
		/* 2*/	     0.5f,  0.85f, 0.0f,	    0.0f, 0.0f, 0.0f, // Top right
		/* 3*/	     1.0f,   0.0f, 0.0f,	    0.0f, 0.0f, 0.0f, // Right
		/* 4*/	     0.5f, -0.85f, 0.0f,        0.0f, 0.0f, 0.0f, // Bottom right
		/* 5*/	    -0.5f, -0.85f, 0.0f,        0.0f, 0.0f, 0.0f, // Bottom left
		/* 6*/	    -1.0f,   0.0f, 0.0f,	    0.0f, 0.0f, 0.0f, // Left
	};

	// Array of indices for the hexagon.
	GLuint indices_hexagon[] = {
		0, 1, 2, // First triangle (Center, Top Left, Top Right)
		0, 2, 3, // Second triangle (Center, Top Right, Right)
		0, 3, 4, // Third triangle (Center, Right, Bottom Right)
		0, 4, 5, // Fourth triangle (Center, Bottom Right, Bottom Left)
		0, 5, 6, // Fifth triangle (Center, Bottom Left, Left)
		0, 6, 1  // Sixth triangle (Center, Left, Top Left)
	};

	// *** VAO \ VBO \ EBO ***
	// Generate & bind the vertex array object
	glGenVertexArrays(1, &vao_hexagon);
	glBindVertexArray(vao_hexagon);
	// Generate & bind the element buffer object
	glGenBuffers(1, &ebo_hexagon);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_hexagon);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_hexagon), indices_hexagon, GL_STATIC_DRAW); // Creates and initializes a buffer object's data store.
	// Generate & bind the vertex buffer object
	glGenBuffers(1, &vbo_hexagon);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_hexagon);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_hexagon), vertices_hexagon, GL_STATIC_DRAW);

	// ** Set up the vertex attributes **
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr)); // Position attribute
	glEnableVertexAttribArray(0);    // Enable the vertex attribute array.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);    // Enable the color attribute array.

	return program; // Pass the program ID back to main.
}

GLuint initialize_quads()
{
	    GLuint program = c_shader_loader::create_program("Resources/Shaders/Texture.vert",
                                                     "Resources/Shaders/Texture.frag");

    // ** Vertex data **
    GLfloat vertices_quad[] = {
        // Positions          // Colors           // Texture Coords
        -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 2.0f, // Top Left
         0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 2.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   2.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Bottom Left
    };

    GLuint indices_quad[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    // *** VAO \ VBO \ EBO ***
	// Generate & bind the vertex array object
    glGenVertexArrays(1, &vao_quad);
    glBindVertexArray(vao_quad);
	// Generate & bind the element buffer object
    glGenBuffers(1, &ebo_quad);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);
	// Generate & bind the vertex buffer object
    glGenBuffers(1, &vbo_quad);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0); // Position attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // Color attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2); // Texture attribute (UVs)

    // Load and create a texture
    glGenTextures(1, &texture_alien);
    glBindTexture(GL_TEXTURE_2D, texture_alien);

	// Load the image data
    int image_width, image_height, image_components;
	stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load("Resources/Textures/alien.png", &image_width, &image_height,
                                          &image_components, 0);

	// Generate the texture & mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

	// Free up the image data, and unbind the texture.
    stbi_image_free(image_data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return program;
}

void update()
{
	// *** Calculate Matrices ***
	// * First Model Matrix *
	translation_matrix = glm::translate(glm::mat4(1.0f), quad_position1);
	rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(quad_rotation_angle1), glm::vec3(0.0f, 0.0f, 1.0f));
	scale_matrix = glm::scale(glm::mat4(1.0f), quad_scale1);
	model_matrix1 = translation_matrix * rotation_matrix * scale_matrix; // Collate the matrices into the model matrix.
	// * Second Model Matrix *
	translation_matrix = glm::translate(glm::mat4(1.0f), quad_position2);
	rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(quad_rotation_angle2), glm::vec3(0.0f, 0.0f, 1.0f));
	scale_matrix = glm::scale(glm::mat4(1.0f), quad_scale2);
	model_matrix2 = translation_matrix * rotation_matrix * scale_matrix; // Collate the matrices into the model matrix.

	// * First Hexagon Model Matrix *
	hexagon_translation_matrix = glm::translate(glm::mat4(1.0f), hexagon_position1);
	hexagon_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(hexagon_rotation_angle1), glm::vec3(0.0f, 0.0f, 1.0f));
	hexagon_scale_matrix = glm::scale(glm::mat4(1.0f), hexagon_scale1);
	hexagon_model_matrix1 = hexagon_translation_matrix * hexagon_rotation_matrix * hexagon_scale_matrix; // Collate the matrices into the model matrix.
	// * Second Hexagon Model Matrix *
	hexagon_translation_matrix = glm::translate(glm::mat4(1.0f), hexagon_position2);
	hexagon_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(hexagon_rotation_angle2), glm::vec3(0.0f, 0.0f, 1.0f));
	hexagon_scale_matrix = glm::scale(glm::mat4(1.0f), hexagon_scale2);
	hexagon_model_matrix2 = hexagon_translation_matrix * hexagon_rotation_matrix * hexagon_scale_matrix; // Collate the matrices into the model matrix.

	// *** Poll for events ***
	glfwPollEvents(); // Updates any window events such as input or window resizing.
	// ** update variables **
	current_time = static_cast<float>(glfwGetTime()); // Get the current time in seconds.
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers.

	// ***** Start of the rendering pipeline *****

	// ** Texture **
	glActiveTexture(GL_TEXTURE0); // Activate texture unit 0.
	glBindTexture(GL_TEXTURE_2D, texture_alien); // Bind the texture object to the target slot.
	glUniform1i(glGetUniformLocation(program_texture, "texture_0"), 0); // Set the texture sampler to use texture unit 0.


	// *** Drawing ***

	// ** Quads **
	glUseProgram(program_texture);	    // Start using the program object. This activates the shader program.
	glBindVertexArray(vao_quad);        // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.
	// * render first quad *
	GLint model_matrix_loc = glGetUniformLocation(program_texture, "model_matrix");

	// Make the first quad mirror the texture when it goes out of bounds.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // Call again invert

	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix1));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // Draw quad. 6 indices, 2 triangles, 3 vertices each.
	// * render second quad *
	// Make the second quad draw the texture normally.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Grab one corner for animating.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix2));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// ** Hexagons **
	glUseProgram(program_hexagon);	       // Start using the program object. This activates the shader program.
	glBindVertexArray(vao_hexagon);        // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.
	// * render first hexagon *
	model_matrix_loc = glGetUniformLocation(program_hexagon, "model_matrix");
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(hexagon_model_matrix1));
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr); // Draw hexagon. 18 indices, 6 triangles, 3 vertices each.
	// * render second hexagon *
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(hexagon_model_matrix2));
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

	// Send the array of colors to the shader.
    GLint colors_loc = glGetUniformLocation(program_hexagon, "colors");
    glUniform3fv(colors_loc, 7, glm::value_ptr(colors[0]));

	// Send the input color to the shader.
    GLint input_color_loc = glGetUniformLocation(program_hexagon, "input_color");
    glUniform3f(input_color_loc, 1.0f, 0.0f, 0.0f); // Example: Red color

    // Send the blend color to the shader.
    GLint blend_color_loc = glGetUniformLocation(program_hexagon, "blend_color");
	// Loop through the colors and send them to the shader
	for (const auto& color : colors) {
	    glUniform3f(blend_color_loc, color.r, color.g, color.b);
	}

	// Send the current time to the shader.
	GLint current_time_loc = glGetUniformLocation(program_hexagon, "current_time");
	glUniform1f(current_time_loc, current_time);

	// ***** End of the rendering pipeline *****

	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
};

void initialize_glfw()
{
	glfwInit(); // Must be called before any other GLFW functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
}

int initialize_glew()
{
    /*
    * -- Note to self --
    * glewInit
    * This function must be called after the initialization of the GLFW window and before any OpenGL functions are called.
    * This populates all the OpenGL function pointers with the correct functions that are supported by the graphics card.
    */
    if (glewInit() != GLEW_OK)
    {
        // Terminate GLFW if GLEW failed to initialise.
        std::cout << "Failed to initialise GLEW" << '\n';
        std::cin.get();

        glfwTerminate();
        return -1; // Return an error code.
    }
    return 0; // Return 0 if initialization is successful.
}