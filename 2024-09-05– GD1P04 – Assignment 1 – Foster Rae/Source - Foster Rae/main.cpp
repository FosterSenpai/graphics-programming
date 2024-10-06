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

// == Objects ==
// Quad objects.
GLuint quad_vao, quad_vbo, quad_ebo, alien_texture_id, program_quad;
// Hexagon objects.
GLuint hex_vao, hex_vbo, hex_ebo, program_hex;
// Hexagon colors.
glm::vec3 colors[] = {
    glm::vec3(1.0f, 0.0f, 0.0f), // Red
    glm::vec3(0.0f, 1.0f, 0.0f), // Green
    glm::vec3(0.0f, 0.0f, 1.0f), // Blue
    glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
    glm::vec3(1.0f, 0.0f, 1.0f), // Magenta
    glm::vec3(0.0f, 0.0f, 0.0f)  // Black
};
// Transformations.
c_transformations quad1_transform(glm::vec3(-0.35f, -0.5f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 1.0f));
c_transformations quad2_transform(glm::vec3(0.4f, -0.5f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 1.0f));
c_transformations hexagon1_transform(glm::vec3(-0.35f, 0.5f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 1.0f));
c_transformations hexagon2_transform(glm::vec3(0.45f, 0.5f, 0.0f), 0.0f, glm::vec3(0.3f, 0.3f, 1.0f));

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
    // Create the quads.
    program_quad = c_graphics_utils::initialize_quads(quad_vao, quad_vbo, quad_ebo, alien_texture_id);
    // Create the hexagons.
    program_hex = c_graphics_utils::initialize_hexagons(hex_vao, hex_vbo, hex_ebo);

	// Prepare the window.
	glClearColor(0.56f, 0.57f, 0.60f, 1.0f); // Set the clear color to a light grey.
	glViewport(0, 0, window_width, window_height); // Maps the range of the window size to NDC space.
}
void update()
{
	// Update objects.
	quad1_transform.update();
	quad2_transform.update();
	hexagon1_transform.update();
	hexagon2_transform.update();

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


	// == QUADS ==
	// Quad texture.
	glActiveTexture(GL_TEXTURE0); // Activate texture unit 0.
	glBindTexture(GL_TEXTURE_2D, alien_texture_id); // Bind the texture object to the target slot.
	glUniform1i(glGetUniformLocation(program_quad, "texture_0"), 0); // Set the texture sampler to use texture unit 0.
	// Use the quad program.
	glUseProgram(program_quad); // Start using the program object. This activates the shader program.
	glBindVertexArray(quad_vao); // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.
	// Quad uniforms.
	GLint model_matrix_loc = glGetUniformLocation(program_quad, "model_matrix"); // Get the location of the model matrix uniform.

	// == QUAD 1 ==
	// Change address mode to mirrored repeat.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // Call again invert
	// Pass the model matrix to the shader AND draw the quad.
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(quad1_transform.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// == QUAD 2 ==
	// reset the address mode.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Pass the model matrix to the shader AND draw the quad.
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(quad2_transform.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	// == HEXAGONS ==
	// Use the hexagon program.
	glUseProgram(program_hex); // Start using the program object. This activates the shader program.
	glBindVertexArray(hex_vao); // Bind to the VAO target slot. Subsequent VAO operations will affect this VAO.
	// Hexagon uniforms.
	model_matrix_loc = glGetUniformLocation(program_hex, "model_matrix"); // Get the location of the model matrix uniform.

	// == HEXAGON 1 ==
	// Pass the model matrix to the shader AND draw the hexagon.
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(hexagon1_transform.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

	// == HEXAGON 2 ==
	// Pass the model matrix to the shader AND draw the hexagon.
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(hexagon2_transform.get_model_matrix()));
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

	// == HEXAGON COLORS ==
	// Send the array of colors to the shader.
    GLint colors_loc = glGetUniformLocation(program_hex, "colors");
    glUniform3fv(colors_loc, 7, glm::value_ptr(colors[0]));
	// Send the input color to the shader.
    GLint input_color_loc = glGetUniformLocation(program_hex, "input_color");
    glUniform3f(input_color_loc, 1.0f, 0.0f, 0.0f); // Example: Red color
    // Send the blend color to the shader.
    GLint blend_color_loc = glGetUniformLocation(program_hex, "blend_color");
	// Loop through the colors and send them to the shader
	for (const auto& color : colors) {
	    glUniform3f(blend_color_loc, color.r, color.g, color.b);
	}
	// Send the current time to the shader.
	GLint current_time_loc = glGetUniformLocation(program_hex, "current_time");
	glUniform1f(current_time_loc, current_time);


	// == END OF RENDERING PIPELINE ==
	glBindVertexArray(0); // Unbind the VAO.
	glUseProgram(0); // Stop using the program object. Deactivate the program object.
	glfwSwapBuffers(window); // Swap the front and back buffers. End of the rendering pipeline.
}
