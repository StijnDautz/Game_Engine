#include "Scene.h"
#include "Intersection.h"
#include "Constants.h"

#include "Engine\Logger.h"
#include "Engine\TextureEditor.h"

RGBA32 Scene::MultiSampleTrace(Ray r, glm::vec3 target, glm::vec3 xInterval, glm::vec3 yInterval, Constant c) {
	RGBA32 color = RGBA32();
	glm::vec3 start = target;

	// subdivide the interval
	xInterval *= c.div1count;
	yInterval *= c.div1count;

	for (float y = 0; y < c.count; y++) {
		target = start + (y * yInterval);                            // 4x +, *
		for (int y = 0; y < c.count; y++) {
			r.SetTarget(target);						// is this possible without normalization???
			color += Trace(r, 0);
			target += xInterval;                            // x+^2 + x+ + x* + 2* x = 4 -> 26 60% less operations
		}
	}
	return color * c.div1countSquared;
}

RGBA32 Scene::Trace(Ray ray, int depth)
{
	// find the smallest length the ray had to travel to hit an object
	Intersection intersection = Intersection(ray);
	intersection.ray.length = RAYLENGTHCAP;

	float length;
	for (unsigned int i = 0; i < _objects.size(); i++) {
		length = _objects[i]->primitive->GetHitLength(ray);
		
		// if there was no intersection GetHitLength = RAYLENGTHCAP
		if (length < intersection.ray.length) {
			intersection.ray.length = length;
			intersection.obj = _objects[i];
		}
	}

	// return black if ray did not hit an object
	if (intersection.ray.length == RAYLENGTHCAP) {
		return BLACK;
	}

	// else setup the intersection
	intersection.p = intersection.ray.GetTarget();
	intersection.n = intersection.obj->GetNormal(intersection.p);

	// Compute the color at intersection
	RGBA32 color = BLACK;
	float diffuse = intersection.obj->diffuse;
	float specular = intersection.obj->specular;

	// DIFFUSE
	if (diffuse > 0) {
		// compute total lighting
		Ray shadowray = Ray(intersection.p);
		RGBA32 lighting = BLACK;
		float dot;
		float attenuation;

		for (unsigned int i = 0; i < _lights.size(); i++) {
			// add lighting if ray can hit the intersection
			shadowray.SetTarget(_lights[i].p);
			
			attenuation = 1.0f / (shadowray.length * shadowray.length);
			if (attenuation < 0.0001f) {
				goto newLight;
			}

			dot = glm::dot(intersection.n, shadowray.d);
			for (unsigned int j = 0; j < _objects.size(); j++) {
				if (_objects[j]->primitive->Intersects(shadowray, dot)) {
					goto newLight;
				}
			}

			// compute the ray light energy and apply floating point accuracy correction
			lighting += attenuation * _lights[i].intensity * dot - 0.0000001f;

			newLight:;
		}

		lighting.clamp();

		// apply total lightning to diffuse
		color += intersection.obj->GetColorAt(intersection.p) * lighting * diffuse;
	}

	// SPECULAR
	if (specular > 0 && ++depth < DEPTHCAP) {
		Ray reflection = ray.reflection(intersection.p, intersection.n);
		reflection.applyOffset();

		color += Trace(reflection, depth) * specular;
	}

	color.color.a = 1.0f;
	return color;       
}

// DEBUGGING METHOD
RGBA32 Scene::TraceAndDebug(Texture* texture, Ray ray, int depth)
{
	// find the smallest length the ray had to travel to hit an object
	Intersection intersection = Intersection(ray);
	intersection.ray.length = RAYLENGTHCAP;

	float length;
	for (unsigned int i = 0; i < _objects.size(); i++) {
		length = _objects[i]->primitive->GetHitLength(ray);

		// if there was no intersection GetHitLength = RAYLENGTHCAP
		if (length < intersection.ray.length) {
			intersection.ray.length = length;
			intersection.obj = _objects[i];
		}
	}

	// cast primary ray
	// make sure the target is within the debugImage's boundaries
	DrawRay(texture, intersection.ray, depth);

	// return black if ray did not hit an object
	if (intersection.ray.length == RAYLENGTHCAP) {
		return BLACK;
	}

	// else setup the intersection
	intersection.p = intersection.ray.GetTarget();
	intersection.n = intersection.obj->primitive->GetNormal(intersection.p);

	// Compute the color at intersection
	RGBA32 color;
	float diffuse = intersection.obj->diffuse;
	float specular = intersection.obj->specular;

	// DIFFUSE
	if (diffuse > 0) {
		// compute total lighting
		Ray shadowray = Ray(intersection.p);
		RGBA32 lighting = BLACK;
		float attenuation;

		for (unsigned int i = 0; i < _lights.size(); i++) {
			// add lighting if ray can hit the intersection
			shadowray.SetTarget(_lights[i].p);

			attenuation = 1.0f / (shadowray.length * shadowray.length);
			if (attenuation < 0.0001f) {
				goto newLight;
			}

			float dot = glm::dot(intersection.n, shadowray.d);
			for (unsigned int j = 0; j < _objects.size(); j++) {
				DrawRay(texture, shadowray, depth);
				if (_objects[j]->primitive->Intersects(shadowray, dot)) {
					goto newLight;
				}
			}

			// compute the ray light energy and apply floating point accuracy correction
			lighting += attenuation * _lights[i].intensity * dot - 0.0000001f;
		}

		// make sure the lighting does exceed 1
		lighting.clamp();

		// apply total lightning to diffuse
		color += intersection.obj->GetColorAt(intersection.p) * lighting * diffuse;

	newLight:;
	}

	// SPECULAR
	if (specular > 0 && ++depth < DEPTHCAP) {
		Ray reflection = ray.reflection(intersection.p, intersection.n);
		reflection.applyOffset();

		color += TraceAndDebug(texture, reflection, depth) * specular;
	}

	color.color.a = 1.0f;
	return color;
}

void Scene::DrawDebug(Texture * texture)
{
	for (unsigned int i = 0; i < _objects.size(); i++) {
		_objects[i]->primitive->DrawDebug(texture);
	}
}

void Scene::DrawRay(Texture* texture, Ray ray, int depth)
{
	// make the line fits into the image
	// target
	Ray debugRay = ray;
	glm::vec3 p = debugRay.GetTarget();
	texture->worldToTextureCoords(20, 0, 0, p);
	while (p.x < 0 || p.x > texture->width || p.z < 0 || p.z > texture->height) {
		debugRay.length *= 0.1f;
		p = debugRay.GetTarget();
		texture->worldToTextureCoords(20, 0, 0, p);
	}

	// origin
	texture->worldToTextureCoords(20, 0, 0, ray.o);

	// draw the debug ray
	TextureEditor::drawLine(texture, p.x, p.z, (int)ray.o.x, (int)ray.o.z, depth > 0 ? REFLECTRAYCOLOR : PRIMARYRAYCOLOR);
}