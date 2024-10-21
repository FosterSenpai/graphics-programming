# Basic OpenGL Pipeline Project
Foster Rae.  
(c) 2024 Media Design School  
GD1P04, Graphics Programming.

## Overview
This project renders a few cube meshes to the screen using OpenGL.  
I didn't have time to implement the model loading properly so I just used a cube mesh and passed as much of the rubric as i could without models.

Can change between different camera modes, wireframe and fill mode, and change the textures of the cubes by clicking on the ui square.

Camera movement is done with the `Arrow Keys`.

Cube Movement is done by using `WASD` to move the cube along the cameras forward, right and up vectors. The camera up vector is set to world up vector.

### Notes
You can change the texture only once, from the dirt texture to the gravel texture, but are unable to change it back to the dirt texture.  
i had it working but i changed something and it broke and i didn't have time to fix it.  

Both of the textures were created by me using an AI tool, theyre not the real microsoft textures.

## Controls
#### Camera
- `ARROW__KEYS` - Move the camera.
- `Mouse` - Look around.
- `Left Shift` - Increase camera speed.
- `Space` - Move the camera up.
- `Left control` - Move the camera down.

#### Cube Movement
- `W` - Move the cube forward.
- `S` - Move the cube backward.
- `A` - Move the cube left.
- `D` - Move the cube right.
- `Q` - Move the cube up.
- `E` - Move the cube down.

#### View Mode Controls
- `Tab` - Change between camera modes. (Auto Orbit -> Manual Orbit -> Free Cam -> Auto Orbit).
- `CAPSLOCK` - Toggle between wireframe and fill mode.
- `M` - Make cursor visible and print mouse coordinates to console.
- `Left Click` - When mouse is visible, click on the ui square to change the textures of the cubes.

## Dependencies
- [GLFW](https://www.glfw.org/) - For window creation and input handling
- [GLEW](http://glew.sourceforge.net/) - For loading OpenGL functions