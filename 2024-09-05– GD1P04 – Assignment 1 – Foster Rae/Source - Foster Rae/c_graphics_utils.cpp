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

GLuint c_graphics_utils::initialize_quads(GLuint& quad_vao, GLuint& quad_vbo, GLuint& quad_ebo, GLuint& texture_id1, GLuint& texture_id2)
{
			// Create the program object.
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
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);
	// Generate & bind the element buffer object
    glGenBuffers(1, &quad_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);
	// Generate & bind the vertex buffer object
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0); // Position attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // Color attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2); // Texture attribute (UVs)

    //Create two textures to fade between on one quad.
    // == Texture 1 ==
    // Save the image data.
    int image_1_width, image_1_height, image_1_components;
    unsigned char* image_1_data = stbi_load("Resources/Textures/Run (4).png", &image_1_width, &image_1_height, &image_1_components, 0);
    // Generate the texture.
    texture_id1 = c_texture_loader::create_texture(image_1_data, image_1_width, image_1_height, image_1_components);
    // Free the image data.
    stbi_image_free(image_1_data);

    // == Texture 2 ==
    // Save the image data.
    int image_2_width, image_2_height, image_2_components;
    unsigned char* image_2_data = stbi_load("Resources/Textures/Run (6).png", &image_2_width, &image_2_height, &image_2_components, 0);
    // Generate the texture.
    texture_id2 = c_texture_loader::create_texture(image_2_data, image_2_width, image_2_height, image_2_components);
    // Free the image data.
    stbi_image_free(image_2_data);


	return program;
}
