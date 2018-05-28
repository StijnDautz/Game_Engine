#include "Scene.h"
#include "Intersection.h"

RGBA32 Scene::Trace(Ray ray, int depth)
{
	// find the smallest length the ray had to travel to hit an object
	Intersection intersection = Intersection(ray);
	intersection.ray.length = 100000000.0f;

	float length;
	for (int i = 0; i < _objects.size(); i++) {
		length = _objects[i].primitive->GetHitLength(ray);
		
		// if there was no intersection GetHitLength = 100000000.0f
		if (length < intersection.ray.length) {
			intersection.ray.length = length;
			intersection.obj = _objects[i];
		}
	}

	// return black if ray did not hit an object
	if (intersection.ray.length == 100000000.0f) {
		return RGBA32();
	}

	// else setup the intersection
	intersection.p = intersection.ray.GetTarget();
	intersection.n = intersection.obj.primitive->GetNormal(intersection.p);

	// Compute the color at intersection
	RGBA32 color;
	float diffuse = intersection.obj.diffuse;
	float specular = intersection.obj.specular;

	// DIFFUSE
	if (diffuse > 0) {
		// compute total lighting
		Ray shadowray = Ray(intersection.p);
		float lighting = 0.0f;

		int j;
		for (int i = 0; i < _lights.size(); i++) {
			// add lighting if ray can hit the intersection
			shadowray.SetTarget(_lights[i].p);
			for (j = 0; j < _objects.size(); j++) {
				if (_objects[j].primitive->Intersects(shadowray)) {
					goto newLight;
				}
			}

			// compute the ray light energy and apply floating point accuracy correction
			lighting += _lights[j - 1].intensity * glm::dot(intersection.n, shadowray.d) - 0.0000001f;
		}

		// apply total lightning to diffuse
		color += intersection.obj.GetColorAt(intersection.p) * (lighting * diffuse);

	newLight:;
	}
	/*
	if (specular > 0) {
		if (++depth < DEPTHCAP) {
			color += Trace(intersection.GetReflection(), depth) * specular;
		}
	}*/
	color.color.a = 1.0f;
	return color;       
}