#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Transform
{
public:
	Transform() : _localTranslation(glm::vec3()), _localQuat(glm::quat()), _localScale(glm::vec3()) {}
	~Transform() {}

	std::vector<Transform> children;

	glm::vec3 xAxis() { return _localQuat * glm::vec3(1, 0, 0); }
	glm::vec3 yAxis() { return _localQuat * glm::vec3(0, 1, 0); }
	glm::vec3 zAxis() { return _localQuat * glm::vec3(0, 0, 1); }
	glm::vec3 GetOrientationVector(glm::vec3 axes) { return _localQuat * axes; }

	glm::vec3 GetLocalPosition() { return _localTranslation; }
	glm::vec3 GetLocalScale() { return _localScale; }
	glm::quat GetLocalRotation() { return _localQuat; }
	
	void Translate(glm::vec3 translation);
	void Rotate(float angle, glm::vec3 axes);
	void Scale(float scale);

	glm::mat4 GetWorldMatrix(glm::mat4 parentMat);

private:
	bool hasChanged;
	glm::vec3 _localTranslation;
	glm::quat _localQuat;
	glm::vec3 _localScale;
	glm::mat4 _toWorld;

	glm::mat4 CreateLocalMat() { return glm::mat4(); }//; //return glm::scale(glm::translate(glm::toMat4(_localQuaternion), _localTranslation), _localScale); }
};