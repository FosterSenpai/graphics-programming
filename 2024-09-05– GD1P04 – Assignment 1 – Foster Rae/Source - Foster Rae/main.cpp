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
GLuint vao, vbo, ebo;
std::vector<c_cube*> cubes;  // Vector of cube objects.
GLuint shader_program;
int frame_count = 0;
double elapsed_time = 0.0;

bool wireframe_mode = false; // Flag for wireframe mode on/off.
bool cursor_visible = false; // Flag for cursor visibility.
double old_x_pos, old_y_pos; // Old mouse position.
// Time variables.
GLfloat current_time;
GLfloat previous_time = 0.0f;
GLfloat delta_time;

// Link the mouse callback to the camera mouse input function.
void mouse_callback(GLFWwindow* glfw_window, double x_pos, double y_pos)
{
    camera.mouse_input(window, x_pos, y_pos);
}

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
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    // Set the mouse callback function.
    glfwSetCursorPosCallback(window, mouse_callback); // Look I found a reason to use the mouse pos callback.

    // Create the shader program.
	shader_program = c_shader_loader::create_program("test.vert", "test.frag");

	// === LOAD TEXTURES HERE ===
	std::vector<s_texture> textures;
	s_texture texture1;
	texture1.id = c_graphics_utils::load_image("Resources/Textures/texture_diffuse1.png");
	texture1.type = "texture_diffuse";
	textures.push_back(texture1);

	// === CREATE CUBE OBJECTS HERE ===
    int grid_size = 5; // Define the size of the grid.
    float spacing = 1.0f; // Define the spacing between cubes.
    float z_offset = -5.0f;
    float x_offset = -2.0f;

    cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -1.0f, -2.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    // First layer of cubes.
    for (int x = 0; x < grid_size; ++x)
    {
        for (int z = 0; z < grid_size; ++z)
        {
            glm::vec3 position((x * spacing) + x_offset, -2.0f, (z * spacing) + z_offset);
            cubes.push_back(new c_cube(textures, position, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
        }
    }
    // Second layer of cubes.
    for (int x = 0; x < grid_size - 2 ; ++x)
	{
		for (int z = 0; z < grid_size - 2; ++z)
		{
			glm::vec3 position((x * spacing) + x_offset + 1, -3.0f, (z * spacing) + z_offset + 1);
			cubes.push_back(new c_cube(textures, position, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
		}
	}
    // Decor cubes.
    cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -3.0f, -1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -4.0f, -2.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -4.0f, -3.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(0.0f, -4.0f, -3.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(-1.0f, -4.0f, -4.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(-2.0f, -3.0f, -2.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    cubes.push_back(new c_cube(textures, glm::vec3(-2.0f, -3.0f, -3.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
    // Set the active cube.
    cubes[0]->set_active_cube(true);

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

	process_input(window);		       // Process input.
    if (!cursor_visible)			   // Only update the camera if the cursor is hidden.
    {
        camera.update(window, delta_time);
    }
    else
    {
	    // Print the mouse position if the cursor is visible.
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);
		std::cout << "Mouse Position: " << x_pos << ", " << y_pos << std::endl;
    }
	glfwPollEvents();				   // Poll for events.

	// Calculate the frames per second for the window title.
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
	// ========== START OF RENDERING PIPELINE ==========

	// Use the shader program.
	glUseProgram(shader_program);

    // Pass camera matrices to the shader.
    c_shader_loader::set_mat_4(shader_program, "projection", camera.get_projection_matrix());
    c_shader_loader::set_mat_4(shader_program, "view", camera.get_view_matrix());

	// Set wireframe mode if enabled
    if (wireframe_mode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

	// == DRAW OBJECTS HERE ==;

    // Draw the cubes.
    for (auto& cube : cubes)
    {
	    cube->draw(shader_program);
    }

	// ========== END OF RENDERING PIPELINE ==========
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

	// Toggle cursor visibility and camera movement if M is pressed.
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        cursor_visible = !cursor_visible;
        if (cursor_visible) // Show the cursor.
        {
			// Save the old cursor position.
			glfwGetCursorPos(window, &old_x_pos, &old_y_pos);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        else // Hide the cursor. Set to raw mouse input.
        {
        	// Set the cursor to the old position.
			glfwSetCursorPos(window, old_x_pos, old_y_pos);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        	// Set the cursor to the old position.
			glfwSetCursorPos(window, old_x_pos, old_y_pos);
			// Force the camera to update the mouse position.
			camera.mouse_input(window, old_x_pos, old_y_pos);
        }

        // Add a small delay to prevent rapid toggling.
        while (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwPollEvents();
        }
    }

    // Cube movement.
    for (auto& cube : cubes)
	{
        if (cube->get_active_cube())
		{
			// Move the cube.
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(0.0f, 0.0f, -1.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(-1.0f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(0.0f, -1.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				cube->move(camera, glm::vec3(0.0f, 1.0f, 0.0f));
			}
            
		}
	}
}
