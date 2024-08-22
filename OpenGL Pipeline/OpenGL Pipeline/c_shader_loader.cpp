#include "c_shader_loader.h"
#include<iostream>
#include<fstream>
#include<vector>


c_shader_loader::c_shader_loader(void) {}
c_shader_loader::~c_shader_loader(void) {}

GLuint c_shader_loader::create_program(const char* vertex_shader_filename, const char* fragment_shader_filename)
{
	// Create the shaders from the filepath
	GLuint vertexShader = create_shader(GL_VERTEX_SHADER, vertex_shader_filename);
	GLuint fragmentShader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_filename);

	// Create the program handle, attach the shaders and link it
	GLuint program = glCreateProgram(); // create a program object
	glAttachShader(program, vertexShader); // attach the vertex shader
	glAttachShader(program, fragmentShader); // attach the fragment shader
	glLinkProgram(program); // link the shaders into a complete program


	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = vertex_shader_filename + *fragment_shader_filename;
		print_error_details(false, program, programName.c_str());
		return 0;
	}


	glDeleteShader(vertexShader); // delete the vertex shader
	glDeleteShader(fragmentShader); // delete the fragment shader

	return program;
}

GLuint c_shader_loader::create_shader(GLenum shader_type, const char* shader_name)
{
	// Read the shader files and save the source code as strings
	std::string ShaderCode = read_shader_file(shader_name); // Save the shader code as a string

	// Create the shader ID and create pointers for source code string and length
	GLuint shader_id = glCreateShader(shader_type); // Create a shader object
	const char* p_code = ShaderCode.c_str(); // Create a pointer to the shader code, convert the string to a char array
	const int code_length = static_cast<int>(ShaderCode.size()); // Save the length of the shader code

	// Populate the Shader Object (ID) and compile
	glShaderSource(shader_id, 1, &p_code, &code_length); // Populate the shader object with the shader code
	glCompileShader(shader_id); // Compile the shader


	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		print_error_details(true, shader_id, shader_name);
		return 0;
	}
	return shader_id;
}

std::string c_shader_loader::read_shader_file(const char* filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << '\n';
		return "";
	}

	// Determine the size of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void c_shader_loader::print_error_details(bool is_shader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(is_shader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(is_shader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((is_shader == true) ? "shader" : "program") << ": " << name << '\n';
	std::cout << &log[0] << '\n';
}
