#include "c_graphics_utils.h"
#include <stb_image.h>
#include "c_texture_loader.h"

// == Public Methods ==
void c_graphics_utils::initialize_glfw()
{
	// Initialize GLFW.
	glfwInit();
	// Set window hint to OpenGL 4.6.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
}
int c_graphics_utils::initialize_glew()
{
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
GLFWwindow* c_graphics_utils::create_window(int width, int height, const char* title)
{
	// Create a windowed mode window and its OpenGL context.
	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		// Terminate GLFW if the window failed to initialise.
		std::cout << "Failed to create GLFW window" << '\n';
		std::cin.get();

		glfwTerminate();
		return nullptr; // Return a nullptr if the window failed to initialise.
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	return window; // Return the window if it was successfully created.
}
