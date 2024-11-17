#version 460 core
// Output.
out vec4 FragColor;

// Input from vertex shader.
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

// Inputs from application.
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform int active_texture; // Uniform to select which texture to use.
uniform float time; // This isnt being used right now. Remember to use or remove.

// Lighting structs.
struct PointLight {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

// Lighting uniforms.
uniform PointLight pointLights[2];
uniform DirectionalLight dirLight;
uniform Spotlight spotLight;
uniform bool pointLightsOn;
uniform bool dirLightOn;
uniform bool spotLightOn;

// Camera position
uniform vec3 viewPos;

void main()
{
    vec4 color;

    // Select the texture to use based on the active_texture uniform.
    if (active_texture == 0) {
        color = texture(texture_diffuse1, TexCoord);
    } else if (active_texture == 1) {
        color = texture(texture_diffuse2, TexCoord);
    } else if (active_texture == 2) {
        color = texture(texture_diffuse3, TexCoord);
    } else if (active_texture == 3) {
        color = texture(texture_specular1, TexCoord);
    } else if (active_texture == 4) {
        color = texture(texture_specular2, TexCoord);
    } else if (active_texture == 5) {
        color = texture(texture_specular3, TexCoord);
    } else {
        color = vec4(1.0, 0.0, 1.0, 1.0); // Default to magenta if no valid texture is selected.
    }

    // Ambient lighting.
    vec3 ambient = 0.1 * color.rgb;

    // Initialize lighting components.
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    // Calculate normal.
    vec3 norm = normalize(Normal);

    // Point lights.
    if (pointLightsOn) {
        for (int i = 0; i < 2; i++) {
            // Attenuation.
            float distance = length(pointLights[i].position - FragPos);
            float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + pointLights[i].quadratic * (distance * distance));

            // Diffuse.
            vec3 lightDir = normalize(pointLights[i].position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            diffuse += diff * pointLights[i].color * color.rgb * attenuation;

            // Specular.
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
            specular += spec * pointLights[i].color * attenuation;
        }
    }

    // Directional light.
    if (dirLightOn) {
        // Diffuse.
        vec3 lightDir = normalize(-dirLight.direction);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * dirLight.color * color.rgb;
        // Specular.
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 128.0);
        specular += 0.3 * spec * dirLight.color;
    }

    // Spotlight.
    if (spotLightOn) {
        // Spotlight calculations.
        vec3 lightDir = normalize(spotLight.position - FragPos);
        float theta = dot(lightDir, normalize(-spotLight.direction));
        float epsilon = spotLight.cutOff - spotLight.outerCutOff;
        float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
        // Attenuation.
        float distance = length(spotLight.position - FragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
        // Diffuse.
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * spotLight.color * color.rgb * attenuation * intensity;
        // Specular.
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
        specular += spec * spotLight.color * attenuation * intensity;
    }

    // Combine all lighting components.
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, color.a);
}