#include "Texture.hpp"
#include <lodepng/lodepng.h>
#include <iostream>
#include "SceneNode.hpp"

using namespace std;

Texture::Texture(std::string filename): filename(filename) {
    unsigned error = lodepng::decode(image, width, height, filename);
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    for (size_t i = 0; i < image.size(); i += 4) {
        glm::vec3 rgb(image[i] / 100.0f, image[i+1] / 100.0f, image[i+2] / 100.0f);
        imageVec.push_back(rgb);
    }
};

// source: http://raytracerchallenge.com/bonus/texture-mapping.html
glm::vec2 Texture::spherical_map(const glm::vec3& pixel, Primitive* prim, glm::mat4& invtrans) {
    auto pix = glm::vec3(invtrans * glm::vec4(pixel, 0));
    auto m_pos = prim->m_sphere_pos;
    auto p = glm::normalize(glm::vec3(pix) - glm::vec3(m_pos));
    double u = 0.5 + (atan2(p.x, p.z) / (2 * glm::pi<float>()));
    double v = 0.5 - (acos(p.y) / glm::pi<float>());
    return glm::vec2(u, v);
}

glm::vec3 Texture::uv_pattern_at(float u, float v) {
    float u2 = floor(u * width * 4);
    float v2 = floor(v * height * 4);
    glm::vec3 p = imageVec[(v2 * width) + u2];
    return p;
}

glm::vec3 Texture::get_color(glm::vec3 pixel, Primitive *prim, glm::mat4& invtrans)
{
    glm::vec2 uv = spherical_map(pixel, prim, invtrans);
    return uv_pattern_at(uv.x, uv.y);
}