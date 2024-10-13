# Basic OpenGL Pipeline Project

## Overview
This project demonstrates a basic implementation of an OpenGL pipeline. It renders a simple triangle using hard-coded vertex data and includes a vertex and fragment shader.

## Features
- Basic OpenGL setup
- Rendering a triangle
- Vertex and Fragment Shaders

## Prerequisites
- OpenGL 3.3 or higher
- C++11 or higher

## Dependencies
- [GLFW](https://www.glfw.org/) - For window creation and input handling
- [GLEW](http://glew.sourceforge.net/) - For loading OpenGL functions

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/FosterSenpai/graphics-programming.git
2. Create a build directory and navigate to it:
    ```sh
   mkdir build
   cd build


## Project Structure
```
' -- OpenGL Pipeline
	|-- OpenGL Pipeline.sln
	|-- README.md
	|-- OpenGL Pipeline (Can't rename source pls help)
	|   |-- main.cpp
	|   |-- c_shader_loader.h
	|   |-- c_shader_loader.cpp
	|   |-- glew32.dll
	|   |-- glfw3.dll
	|
	|-- Resources
	|   |-- Shaders
	|   |   |-- FixedColor.frag
	|   |   |-- FixedTriangle.vert
	|
	|-- Dependencies
	|   |-- GLEW
	|   |-- GLFW
```
## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## Acknowledgements
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)