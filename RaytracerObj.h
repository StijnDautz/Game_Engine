#pragma once
#include "Primitive.h"
#include "MaterialComponent.h"
#include "NormalComponent.h"

class RaytracerObj
{
public:
	float diffuse;
	float specular;
	Primitive* primitive;
	MaterialComponent* materialComp;
	NormalComponent* normalComp;

	RaytracerObj() : diffuse(0.0f), specular(1.0f) {}
	RaytracerObj(Primitive* p, NormalComponent* n) : primitive(p), normalComp(n), diffuse(0.0f), specular(1.0f) {}
	RaytracerObj(Primitive* p, MaterialComponent* m, NormalComponent* n, float d, float s) : 
		primitive(p), 
		materialComp(m), 
		normalComp(n), 
		diffuse(d), 
		specular(s) {}
	~RaytracerObj() {}

	virtual RGBA32 GetColorAt(glm::vec3 p) { return materialComp->GetColorAt(p); }
	virtual glm::vec3 GetNormal(glm::vec3 p) { return normalComp->GetNormalAt(p); }
};