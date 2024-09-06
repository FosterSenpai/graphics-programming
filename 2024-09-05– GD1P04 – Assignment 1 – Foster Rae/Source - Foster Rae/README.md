## OpenGL Shader Pipeline Project

### Overview
This project is part of the Bachelor of Software Engineering program at Media Design School, Auckland, New Zealand. 
The project demonstrates the implementation of an OpenGL pipeline with custom shaders for rendering textured quads 
and colored hexagons.

The shaders include functionality for texture mapping, color blending, and dynamic transformations.

### Files Description

#### Source Files

- **main.cpp**: The entry point for the OpenGL pipeline. It initializes the window, sets up the shaders, and handles the rendering loop.
- **c_shader_loader.cpp**: Implementation of the `c_shader_loader` class, which is responsible for loading and compiling shaders.
- **c_shader_loader.h**: Header file for the `c_shader_loader` class.

#### Shader Files

- **Texture.vert**: Vertex shader for textured quads. It handles vertex transformations and passes texture coordinates to the fragment shader.
- **Texture.frag**: Fragment shader for textured quads. It samples the texture and outputs the final color.
- **PositionOnly.vert**: Vertex shader for hexagons. It handles vertex transformations and passes color and time information to the fragment shader.
- **FadeColor.frag**: Fragment shader for hexagons. It blends colors based on a sine function to create a fading effect.

### Dependencies

- **GLEW**: OpenGL Extension Wrangler Library
- **GLFW**: Library for creating windows and handling input
- **GLM**: OpenGL Mathematics library for matrix and vector operations
- **stb_image**: Library for loading images

### Setup and Compilation

2. **Install dependencies**:
    Ensure you have GLEW, GLFW, GLM, and stb_image installed. You can use package managers like `apt`, `brew`, or `vcpkg` to install these libraries.

3. **Compile the project**:
    Use your preferred IDE (e.g., Visual Studio) to open the project and compile it. Ensure that the include paths and library paths for GLEW, GLFW, GLM, and stb_image are correctly set.

### Running the Project

1. **Execute the compiled binary**:
    Run the compiled binary from your IDE or terminal. A window should open displaying the rendered quads and hexagons.

2. **Controls**:

      [IN PROGRESS, CURRENTLY REMOVED]
    - **Right Arrow**: Increase red component of the blend color.
    - **Left Arrow**: Increase blue component of the blend color.
    - **Up Arrow**: Increase green component of the blend color.

### Author

- **Foster Rae**
- **Email**: Foster.Rae@mds.ac.nz; }