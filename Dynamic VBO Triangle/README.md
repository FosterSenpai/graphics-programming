# Dynamic Triangle Project

## Overview
This project demonstrates a dynamic implementation of a triangle that can take vertex data at runtime. It uses OpenGL to render the triangle and includes vertex and fragment shaders.

## Features
- Dynamic vertex data input
- Basic OpenGL setup
- Rendering a triangle
- Vertex and Fragment Shaders

## Prerequisites
- OpenGL 3.3 or higher

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
' -- Dynamic VBO Triangle
	|-- Dynamic VBO Triangle.sln
	|-- README.md
	|-- main.cpp
	|-- c_shader_loader.h
	|-- c_shader_loader.cpp
	|-- glew32.dll
	|-- glfw3.dll
	|
	|-- Dependencies
	|   |-- GLEW
	|   |-- GLFW
	|
	|-- Resources
	|   |-- Shaders
	|   |   |-- FixedColor.frag
	|   |   |-- FixedTriangle.vert
```
## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## Acknowledgements
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)