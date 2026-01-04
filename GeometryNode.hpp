// Termm--Fall 2020

#pragma once

#include "SceneNode.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "Texture.hpp"

class GeometryNode : public SceneNode {
public:
	GeometryNode( const std::string & name, Primitive *prim, 
		Material *mat = nullptr, Texture *texture = nullptr );

	void setMaterial( Material *material );
	void setTexture( Texture *texture );
	virtual bool hit(Ray &ray, float t_min, float t_max, Intersection &record) override;

	Material *m_material;
	Primitive *m_primitive;
	Texture *m_texture;
};
