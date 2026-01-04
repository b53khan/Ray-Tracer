#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include "Primitive.hpp"

//class Intersection; 
class Primitive;

class Texture {
public:
    Texture(std::string filename);
    glm::vec3 get_color(glm::vec3 pixel, Primitive* prim, glm::mat4& invtrans);
    glm::vec2 spherical_map(const glm::vec3& pixel, Primitive* prim, glm::mat4& invtrans);
    glm::vec3 uv_pattern_at(float u, float v);

    std::string filename;
    std::vector<unsigned char> image;
    std::vector<glm::vec3> imageVec;
    unsigned width;
    unsigned height;
};

#endif