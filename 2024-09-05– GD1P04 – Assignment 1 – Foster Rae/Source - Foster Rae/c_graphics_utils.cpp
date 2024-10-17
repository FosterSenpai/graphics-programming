#include "c_graphics_utils.h"
#include <stb_image.h>

// == Public Methods ==
void c_graphics_utils::initialize_glfw()
{
	// Initialize GLFW.
	glfwInit();
	// Set window hint to OpenGL 4.6.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

GLuint c_graphics_utils::load_image(const char* file_path)
{
	// Get the data, and variables for the image.
	int width, height, components;
	unsigned char* image_data = stbi_load(file_path, &width, &height, &components, 0);

	// Checks.
	if (image_data == nullptr)
	{
		std::cout << "Failed to load image: " << file_path << '\n';
	    return 0;
	}
	if (width <= 0 || height <= 0 || (components != 3 && components != 4)) {
        std::cerr << "Error: Invalid image dimensions or components." << '\n';
        return 0;
    }

	GLuint texture;
	// Generate texture object and bind to GLuint .
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Check how many components the loaded image has.
    GLint loaded_components = (components == 4) ? GL_RGBA : GL_RGB;

	// Generate the texture & mipmap.
	glTexImage2D(GL_TEXTURE_2D, 0, loaded_components, width, height, 0, loaded_components, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image_data); // Free the image data.
	return texture;				 // Return the texture.
}
