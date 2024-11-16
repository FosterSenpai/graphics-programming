// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_sky_box.h
// Description : Skybox class to render a skybox around the scene.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/

#pragma once
#include <vector>
#include <string>
#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLEW/glew.h"

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces);
    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    void setupSkybox();
    void loadCubemap(const std::vector<std::string>& faces);

    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
    GLuint shaderProgram;
};
