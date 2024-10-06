#include "c_shader_loader.h"
#include<iostream>
#include<fstream>
#include<vector>

// == Constructors / Destructors ==
c_shader_loader::c_shader_loader(void) = default;
c_shader_loader::~c_shader_loader(void) = default;

// == Public Methods ==
GLuint c_shader_loader::create_program(const char* vertex_shader_filename, const char* fragment_shader_filename)
{
	// Create the shaders from the filepath.
	GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_filename);
	GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_filename);

	// Create the program handle, attach the shaders and link it.
	GLuint program = glCreateProgram();			// create a program object.
	glAttachShader(program, vertex_shader);		// attach the vertex shader.
	glAttachShader(program, fragment_shader);   // attach the fragment shader.
	glLinkProgram(program); 					// link the shaders into a complete program.

	// Check for linking errors.
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		// Get error details and print them.
		std::string programName = vertex_shader_filename + *fragment_shader_filename;
		print_error_details(false, program, programName.c_str());
		return 0;
	}

	// Detach the shaders and delete them.
	glDeleteShader(vertex_shader); 	    // delete the vertex shader.
	glDeleteShader(fragment_shader);    // delete the fragment shader.

	return program; 				    // return the program ID.
}

// == Private Methods ==
GLuint c_shader_loader::create_shader(GLenum shader_type, const char* shader_name)
{
	// Create shader object and populate with shader code.
	std::string shader_code = read_shader_file(shader_name);  		     // Save the shader code as a string.

	// Create the shader ID and create pointers for source code string and length.
	GLuint shader_id = glCreateShader(shader_type);					     // Create a shader object with the enum 'shader_type' provided.
	const char* p_shader_code = shader_code.c_str(); 				     // Create a pointer to the shader code, convert the string to a char array.
	const int code_length = static_cast<int>(shader_code.size());        // Save the length of the shader code, need for glShaderSource so it knows how many characters to read.

	// Populate the Shader Object (ID) and compile.
	glShaderSource(shader_id, 1, &p_shader_code, &code_length);	 // Populate the shader object with the shader code.
	glCompileShader(shader_id);                                          // Compile the shader.

	// Check for compilation errors.
	int compile_result = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		// Get error details and print them.
		print_error_details(true, shader_id, shader_name);
		return 0;
	}

	return shader_id; // Return the GLuint ID of the compiled shader.
}
std::string c_shader_loader::read_shader_file(const char* filename)
{
	// Open the file and read the contents into a string.
	std::ifstream file(filename, std::ios::in);
	std::string shader_code;

	// Check if the file was opened successfully.
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << '\n';
		return "";
	}

	// Determine the size of the file in characters and resize the string variable to accomodate.
	file.seekg(0, std::ios::end); 			   // set the position of the next character to be read to the end.
	shader_code.resize((unsigned int)file.tellg());    // resizing to the size of tellg cast to an unsigned int, the end position is effectively the size of the file.
	file.seekg(0, std::ios::beg); 			   // set the position of the next character to be read back to the beginning.

	// ** Extract contents of file **
	file.read(&shader_code[0], shader_code.size());	// read the file into the resized string variable.
	file.close(); 											// close the file.
	return shader_code; 									// return the shader code.
}
void c_shader_loader::print_error_details(bool is_shader, GLuint id, const char* name)
{
	int info_log_length = 0;

	// Retrieve the length of characters needed to contain the info log.
	(is_shader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
	std::vector<char> log(info_log_length);

	// Retrieve the log info and populate log variable.
	(is_shader == true) ? glGetShaderInfoLog(id, info_log_length, NULL, &log[0]) : glGetProgramInfoLog(id, info_log_length, NULL, &log[0]);
	std::cout << "Error compiling " << ((is_shader == true) ? "shader" : "program") << ": " << name << '\n';
	std::cout << &log[0] << '\n';
}