#pragma once
#include "Behaviour.h"

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Transform : public Behaviour
{
public:
	Transform() : _localTranslation(glm::vec3()), _localQuat(glm::quat()), _localScale(glm::vec3(1.0f)) {}
	~Transform() {}

	Transform* parent;
	std::vector<Transform*> children;
	void AddChild(Transform* child);

	glm::vec3 xAxis() { return _localQuat * glm::vec3(1, 0, 0); }
	glm::vec3 yAxis() { return _localQuat * glm::vec3(0, 1, 0); }
	glm::vec3 zAxis() { return _localQuat * glm::vec3(0, 0, 1); }
	glm::vec3 GetOrientationVector(glm::vec3 axes) { return _localQuat * axes; }

	glm::vec3 GetLocalPosition() { return _localTranslation; }
	glm::vec3 GetLocalScale() { return _localScale; }
	glm::quat GetLocalRotation() { return _localQuat; }
	glm::mat4 GetWorldMatrix();

	void Translate(glm::vec3 translation);
	void Rotate(glm::vec3 axes);
	void Scale(float scale);

	void Reset();

private:
	bool hasChanged;
	glm::vec3 _localTranslation;
	glm::vec3 eulerAngles;
	glm::quat _localQuat;
	glm::vec3 _localScale;
	glm::mat4 _toWorld;

	glm::mat4 CreateLocalMat();
};