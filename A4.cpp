// Termm--Fall 2020

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "A4.hpp"
#include "PhongMaterial.hpp"
#include "GeometryNode.hpp"

using namespace std;
using namespace glm;

#define EPSILON 1.0e-3

float REFLECTION_COEFF = 0.2;
float MAX_FLOAT = numeric_limits<float>::max();

vec3 rayColor(Ray &ray, SceneNode *root, const std::list<Light *> & lights, 
			  const glm::vec3 & eye, const glm::vec3 & ambient, const int traceLimit=5)
{
	vec3 color;
	Intersection record;
	if (root->hit(ray, 0, MAX_FLOAT, record))
	{
		record.normal = normalize(record.normal);
		record.hit_pixel += record.normal * EPSILON;

		PhongMaterial *material = static_cast<PhongMaterial *>(record.material);

		// Ambient
		color = material->get_kd() * ambient;

		for (Light * light : lights) {
			Ray shadowRay(record.hit_pixel, light->position - record.hit_pixel);
			Intersection shadowRay_record;
			
			if (root->hit(shadowRay, 0, MAX_FLOAT, shadowRay_record)) continue;

			vec3 L_in = normalize(shadowRay.get_direction());		// light ray
			vec3 N = normalize(record.normal);						// normal
			vec3 L_out = normalize(2 * N * dot(N, L_in) - L_in);	// reflected ray
			vec3 v = normalize(eye - record.hit_pixel);				// direction of reflected ray
			double r = length(shadowRay.get_direction());
			
			// Texture mapping
			glm::vec3 kd = material->get_kd();
			Texture *texture = record.getTexture();
            if (texture) {
				auto m_node = dynamic_cast<GeometryNode*>(record.node);
				kd = texture->get_color(record.hit_pixel, m_node->m_primitive, record.node->invtrans);
            }

			double attenuation = 1.0 / ( light->falloff[0] + light->falloff[1] * r + light->falloff[2] * r * r );

			// Diffuse
			color += dot(L_in, N) * attenuation * kd * light->colour;

			// Specular
			color += pow(glm::max(0.0, (double)dot(L_out, v)), material->get_shininess()) * attenuation * material->get_ks() * light->colour;
		}

		// Reflection
		if (material->m_enable_reflection && traceLimit > 0) {
			vec3 reflection_direction = ray.get_direction() - 2 * record.normal * dot(ray.get_direction(), record.normal);
            Ray reflection_ray(record.hit_pixel, reflection_direction);
			color = glm::mix(color, rayColor(reflection_ray, root, lights, eye, ambient, traceLimit - 1), REFLECTION_COEFF);
		}

	} else {
		vec3 unit_direction = glm::normalize(ray.get_direction());
        float t = unit_direction.y;
        color += (1.0 - t) * vec3(0.5, 0.7, 1.0) + t * vec3(1.0, 1.0, 1.0);
	}
	return color; 
}

void A4_Render(
		// What to render  
		SceneNode * root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  // Fill in raytracing code here...  

//   std::cout << "F20: Calling A4_Render(\n" <<
// 		  "\t" << *root <<
//           "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
//           "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
// 		  "\t" << "view: " << glm::to_string(view) << std::endl <<
// 		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
// 		  "\t" << "fovy: " << fovy << std::endl <<
//           "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
// 		  "\t" << "lights{" << std::endl;

// 	for(const Light * light : lights) {
// 		std::cout << "\t\t" <<  *light << std::endl;
// 	}
// 	std::cout << "\t}" << std::endl;
// 	std:: cout <<")" << std::endl;

	size_t h = image.height();
	size_t w = image.width();

	// Viewport
	vec3 _w = normalize(view); 			// z-axis
	vec3 u = normalize(cross(_w, up)); 	// x-axis
	vec3 v = cross(u, _w); 				// y-axis
	float d = h / 2 / glm::tan(glm::radians(fovy / 2));
	vec3 upper_left_pixel = _w * d - u * (float)w / 2 - v * (float)h / 2;

	// for (uint y = 0; y < h; ++y) {
	// 	for (uint x = 0; x < w; ++x) {
	// 		const vec3 direction = upper_left_pixel + (float)(h - y) * v + (float)x * u;
	// 		Ray ray = Ray(eye, direction);
	// 		vec3 color;
			
	// 		color += rayColor(ray, root, lights, eye, ambient);
	// 		// Red: 
	// 		image(x, y, 0) = (double)color.r;
	// 		// Green: 
	// 		image(x, y, 1) = (double)color.g;
	// 		// Blue: 
	// 		image(x, y, 2) = (double)color.b;
	// 	}
	// }

	// Anti-aliasing parameter
    int samples = 9;

    for (uint y = 0; y < h; ++y) {
        for (uint x = 0; x < w; ++x) {
            vec3 color;
            for (int s = 0; s < samples; ++s) {
                float jitterX = static_cast<float>(rand()) / RAND_MAX - 0.5f;
                float jitterY = static_cast<float>(rand()) / RAND_MAX - 0.5f;
                const vec3 direction = upper_left_pixel + (float)(h - y + jitterY) * v + (float)(x + jitterX) * u;
                Ray ray = Ray(eye, direction);
                color += rayColor(ray, root, lights, eye, ambient);
            }
            
            color /= samples;
            image(x, y, 0) = (double)color.r;
            image(x, y, 1) = (double)color.g;
            image(x, y, 2) = (double)color.b;
        }
    }
}
