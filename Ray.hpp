// source: https://raytracing.github.io/books/RayTracingInOneWeekend.html 

#ifndef RAY_H
#define RAY_H

#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Ray {
public:
    Ray();
    Ray(const glm::vec3& origin,const glm::vec3& direction);

    glm::vec3 get_origin();
    glm::vec3 get_direction();

    glm::vec3 at(float t);

	glm::vec3 origin;
	glm::vec3 direction;
};

#endif