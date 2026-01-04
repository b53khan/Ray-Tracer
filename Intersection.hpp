#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Material.hpp"
#include <glm/glm.hpp>
//#include "Texture.hpp"

class SceneNode;
class Texture;

struct Intersection {
public:
    Intersection() {};
    float t;
    glm::vec3 hit_pixel;
    glm::vec3 normal;
    Material *material;
    SceneNode *node;

    Texture *getTexture();
};

#endif