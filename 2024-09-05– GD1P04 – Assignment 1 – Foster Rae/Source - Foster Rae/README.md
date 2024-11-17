# Basic OpenGL Pipeline Project
Foster Rae.  
(c) 2024 Media Design School  
GD1P04, Graphics Programming.

## Overview
This project renders a few cube meshes to the screen using OpenGL.  
I didn't have time to implement the model loading properly so I just used a cube mesh and passed as much of the rubric as i could without models.

Can change between different camera modes, wireframe and fill mode, and change the textures of the cubes by clicking on the ui square.

### Notes
You can change the texture only once, from the dirt texture to the gravel texture, but are unable to change it back to the dirt texture.  
i had it working but i changed something and it broke and i didn't have time to fix it.  

Both of the textures were created by me using an AI tool, theyre not the real microsoft textures.

Skybox textures from [here](https://vladislavzh.net/notes/retro-skyboxes-released).

## Controls

#### Lights
- `1` - Toggle directional light.
- `2` - Toggle point light.
- `3` - Toggle spot light.

#### Camera
- `WASD` - Move the camera.
- `Mouse` - Look around.
- `Scroll Wheel` - Zoom in and out.
- `Left Shift` - Increase camera speed.
- `Q` - Move the camera up.
- `E` - Move the camera down.

#### Cube Movement
- `ARROW KEYS` - Move the cube.

#### View Mode Controls
- `Tab` - Change between camera modes. (Auto Orbit -> Manual Orbit -> Free Cam -> Auto Orbit).
- `CAPSLOCK` - Toggle between wireframe and fill mode.
- `M` - Make cursor visible and print mouse coordinates to console.
- `Left Click` - When mouse is visible, click on the ui square to change the textures of the cubes.

## Dependencies
- [GLFW](https://www.glfw.org/) - For window creation and input handling
- [GLEW](http://glew.sourceforge.net/) - For loading OpenGL functions