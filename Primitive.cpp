// Termm--Fall 2020

#include "Primitive.hpp"
#include <iostream>
#include "Mesh.hpp"

using namespace glm;

Primitive::~Primitive() {}

bool Primitive::hit(Ray &ray, float t_min, float t_max, Intersection &record) {
    return false;
}

Sphere::Sphere() {
    sphere = new NonhierSphere(vec3(0.0, 0.0, 0.0), 1.0);
}

Sphere::~Sphere() {
    delete sphere;
}

bool Sphere::hit(Ray &ray, float t_min, float t_max, Intersection &record) {
    // std::cout << "Sphere hit" << std::endl;
    return sphere->hit(ray, t_min, t_max, record);
}

Cube::Cube() {
    cube = new NonhierBox(vec3(0.0, 0.0, 0.0), 1.0);
}

Cube::~Cube() {
    delete cube;
}

bool Cube::hit(Ray &ray, float t_min, float t_max, Intersection &record) {
    // std::cout << "Cube hit" << std::endl;
    return cube->hit(ray, t_min, t_max, record);
}

NonhierSphere::NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius) {
      m_sphere_pos = pos;
      m_sphere_radius = radius;
}

NonhierSphere::~NonhierSphere() {
}

bool NonhierSphere::hit(Ray &ray, float t_min, float t_max, Intersection &record) {
    // std::cout << "nonhier hit" << std::endl;
    vec3 oc = ray.get_origin() - m_pos;
    double A = dot(ray.get_direction(), ray.get_direction());
    double B = 2 * dot(ray.get_direction(), oc);
    double C = dot(oc, oc) - m_radius * m_radius;
    double roots[2];
    size_t n_roots =  quadraticRoots(A, B, C, roots);

    float t = 0;
    if (n_roots == 0) {
        return false;
    } else if (n_roots == 1) {
        t = roots[0];
    } else {
        t = glm::min(roots[0], roots[1]);
    }

    if ( t <= t_min || t >= t_max ) return false;

    record.t = t;
    record.hit_pixel = ray.at(t);
    record.normal = record.hit_pixel - m_pos;

    return true;
}

NonhierBox::NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size) {

    m_cube_pos = pos;
    m_cube_size = size;

    std::vector<glm::vec3> vert = {
        m_pos + glm::vec3(0.0, 0.0, 0.0),
        m_pos + glm::vec3(m_size, 0.0, 0.0),
        m_pos + glm::vec3(m_size, 0.0, m_size),
        m_pos + glm::vec3(0.0, 0.0, m_size),
        m_pos + glm::vec3(0.0, m_size, 0.0),
        m_pos + glm::vec3(m_size, m_size, 0.0),
        m_pos + glm::vec3(m_size, m_size, m_size),
        m_pos + glm::vec3(0.0, m_size, m_size)
    };

    std::vector<Triangle> faces = {
        Triangle(0, 1, 2),
        Triangle(0, 2, 3),
        Triangle(0, 7, 4),
        Triangle(0, 3, 7),
        Triangle(0, 4, 5),
        Triangle(0, 5, 1),
        Triangle(6, 2, 1),
        Triangle(6, 1, 5),
        Triangle(6, 5, 4),
        Triangle(6, 4, 7),
        Triangle(6, 7, 3),
        Triangle(6, 3, 2)
    };

    mesh = new Mesh(vert, faces);
}

NonhierBox::~NonhierBox()
{
    delete mesh;
}

bool NonhierBox::hit(Ray &ray, float t_min, float t_max, Intersection &record)
{
    return mesh->hit(ray, t_min, t_max, record);
}
