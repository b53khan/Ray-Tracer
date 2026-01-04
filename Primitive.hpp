// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>
#include "Intersection.hpp"
#include "Ray.hpp"
#include "polyroots.hpp"
#include <cmath>

class Mesh;

class Primitive {
public:
  virtual ~Primitive();
  virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record);
  float m_sphere_radius;
  float m_cube_size;
  glm::vec3 m_sphere_pos;
  glm::vec3 m_cube_pos;
};

class Sphere : public Primitive {
  Primitive * sphere;
public:
  Sphere();
  virtual ~Sphere();
  virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record);
};

class Cube : public Primitive {
  Primitive * cube;
public:
  Cube();
  virtual ~Cube();
  virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius);
  virtual ~NonhierSphere();
  virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record);
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size);
  
  virtual ~NonhierBox();
  virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record);

private:
  glm::vec3 m_pos;
  double m_size;
  Primitive * mesh;
};
