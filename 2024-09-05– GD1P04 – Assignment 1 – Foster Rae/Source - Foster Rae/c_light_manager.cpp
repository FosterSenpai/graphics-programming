#include "c_light_manager.h"
#include <glew.h>
#include <string>

c_light_manager::c_light_manager()
	: dir_light_(), spot_light_(), point_lights_on_(true), dir_light_on_(true), spot_light_on_(true)
{
}

void c_light_manager::add_point_light(const s_point_light& light) {
    point_lights_.push_back(light);
}

void c_light_manager::set_directional_light(const s_directional_light& light) {
    dir_light_ = light;
}

void c_light_manager::set_spotlight(const s_spotlight& light) {
    spot_light_ = light;
}

void c_light_manager::toggle_point_lights(bool state) {
    point_lights_on_ = state;
}

void c_light_manager::toggle_directional_light(bool state) {
    dir_light_on_ = state;
}

void c_light_manager::toggle_spotlight(bool state) {
    spot_light_on_ = state;
}

void c_light_manager::update_lights_in_shader(unsigned int shader_program) {
    glUseProgram(shader_program);

    // Update point lights.
    for (size_t i = 0; i < point_lights_.size(); ++i) {
        std::string index = std::to_string(i);
        glUniform3fv(glGetUniformLocation(shader_program, ("pointLights[" + index + "].position").c_str()), 1, &point_lights_[i].position[0]);
        glUniform3fv(glGetUniformLocation(shader_program, ("pointLights[" + index + "].color").c_str()), 1, &point_lights_[i].color[0]);
        glUniform1f(glGetUniformLocation(shader_program, ("pointLights[" + index + "].constant").c_str()), point_lights_[i].constant);
        glUniform1f(glGetUniformLocation(shader_program, ("pointLights[" + index + "].linear").c_str()), point_lights_[i].linear);
        glUniform1f(glGetUniformLocation(shader_program, ("pointLights[" + index + "].quadratic").c_str()), point_lights_[i].quadratic);
    }

    // Update directional light.
    glUniform3fv(glGetUniformLocation(shader_program, "dirLight.direction"), 1, &dir_light_.direction[0]);
    glUniform3fv(glGetUniformLocation(shader_program, "dirLight.color"), 1, &dir_light_.color[0]);

    // Update spotlight.
    glUniform3fv(glGetUniformLocation(shader_program, "spotLight.position"), 1, &spot_light_.position[0]);
    glUniform3fv(glGetUniformLocation(shader_program, "spotLight.direction"), 1, &spot_light_.direction[0]);
    glUniform1f(glGetUniformLocation(shader_program, "spotLight.cutOff"), spot_light_.cut_off);
    glUniform1f(glGetUniformLocation(shader_program, "spotLight.outerCutOff"), spot_light_.outer_cut_off);
    glUniform3fv(glGetUniformLocation(shader_program, "spotLight.color"), 1, &spot_light_.color[0]);
    glUniform1f(glGetUniformLocation(shader_program, "spotLight.constant"), spot_light_.constant);
    glUniform1f(glGetUniformLocation(shader_program, "spotLight.linear"), spot_light_.linear);
    glUniform1f(glGetUniformLocation(shader_program, "spotLight.quadratic"), spot_light_.quadratic);

    // Update light toggles.
    glUniform1i(glGetUniformLocation(shader_program, "pointLightsOn"), point_lights_on_);
    glUniform1i(glGetUniformLocation(shader_program, "dirLightOn"), dir_light_on_);
    glUniform1i(glGetUniformLocation(shader_program, "spotLightOn"), spot_light_on_);
}

void c_light_manager::update_spotlight(const glm::vec3& position, const glm::vec3& direction)
{
    // Update with parameters.
	spot_light_.position = position;
	spot_light_.direction = direction;
}
