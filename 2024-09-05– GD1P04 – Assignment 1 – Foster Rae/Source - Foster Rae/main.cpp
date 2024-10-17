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
#include "c_structs.h"
#include "c_camera.h"
#include "c_cube.h"

// == Global Variables ==
GLFWwindow* window;
std::string window_title;
c_camera camera;
bool wireframe_mode = false;
GLuint vao, vbo, ebo;
std::vector<c_cube*> cubes; // Vector of cube objects.
GLuint shader_program;
// Time variables.
GLfloat current_time;
GLfloat previous_time = 0.0f;
GLfloat delta_time;
// Frame per second variables.
int frame_count = 0;
double elapsed_time = 0.0;

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
	window = c_graphics_utils::create_window(camera.get_window_width(), camera.get_window_height(), window_title.c_str());
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
	// Delete the cube objects.
	for (auto& cube : cubes)
	{
		delete cube;
	}
	return 0;
}

void initial_setup()
{
	// Set Global Blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set to general blend.

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable face culling.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	// Flip the images vertically.
	stbi_set_flip_vertically_on_load(true);
    // Hide & capture the cursor.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse callback function.
    glfwSetCursorPosCallback(window, mouse_callback); // Add this line
    // Create the shader program.
	shader_program = c_shader_loader::create_program("test.vert", "test.frag");

	// === LOAD TEXTURES HERE ===
	std::vector<s_texture> textures;
	s_texture texture1;
	texture1.id = c_graphics_utils::load_image("Resources/Textures/texture_diffuse1.png");
	texture1.type = "texture_diffuse";
	textures.push_back(texture1);


    // Create multiple cube objects with different positions.
	cubes.push_back(new c_cube(textures, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(0.0f, -1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(1.0f, 1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(1.0f, -1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, 1.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));



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
	// Calculate the frames per second.
	frame_count++;
    elapsed_time += delta_time;
    if (elapsed_time >= 0.5) // Update every half second.
    {
        double fps = frame_count / elapsed_time;
        window_title = "Foster's Pipeline - FPS: " + std::to_string(fps);
        glfwSetWindowTitle(window, window_title.c_str());
        frame_count = 0;
        elapsed_time = 0.0;
    }
}
void render()
{
	// Clear the colour buffer and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Send the current time to the shader.
    glUniform1f(glGetUniformLocation(shader_program, "time"), current_time);

	// == START OF RENDERING PIPELINE ==

	// Use the shader program.
	glUseProgram(shader_program);

    
    // Pass camera matrices to the shader.
    c_shader_loader::setMat4(shader_program, "projection", camera.get_projection_matrix());
    c_shader_loader::setMat4(shader_program, "view", camera.get_view_matrix());

	// Set wireframe mode if enabled
    if (wireframe_mode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

	// == DRAW OBJECTS HERE ==
    for (auto& cube : cubes)
    {
        cube->draw(shader_program);
    }

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

	    // Toggle wireframe mode if Caps Lock is pressed.
    if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
    {
        wireframe_mode = !wireframe_mode;
        // Add a small delay to prevent rapid toggling.
        while (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
        {
            glfwPollEvents();
        }
    }
}
