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
GLuint c_graphics_utils::initialize_quads(GLuint &quad_vao, GLuint &quad_vbo, GLuint &quad_ebo, GLuint &texture_id)
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

    // Load the image data
    int image_width, image_height, image_components;
    unsigned char* image_data = c_texture_loader::load_image("Resources/Textures/alien.png", &image_width, &image_height, &image_components);

    // Create the texture
    texture_id = c_texture_loader::create_texture(image_data, image_width, image_height, image_components);

    // Free up the image data
    stbi_image_free(image_data);

    return program;
}
GLuint c_graphics_utils::initialize_hexagons(GLuint &hex_vao, GLuint &hex_vbo, GLuint &hex_ebo)
{
	// Create the program object.
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
	glGenVertexArrays(1, &hex_vao);
	glBindVertexArray(hex_vao);
	// Generate & bind the element buffer object
	glGenBuffers(1, &hex_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hex_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_hexagon), indices_hexagon, GL_STATIC_DRAW); // Creates and initializes a buffer object's data store.
	// Generate & bind the vertex buffer object
	glGenBuffers(1, &hex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, hex_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_hexagon), vertices_hexagon, GL_STATIC_DRAW);

	// ** Set up the vertex attributes **
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr)); // Position attribute
	glEnableVertexAttribArray(0);    // Enable the vertex attribute array.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);    // Enable the color attribute array.

	return program; // Pass the program ID back to main.
}
