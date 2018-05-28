#include "Transform.h"

void Transform::Translate(glm::vec3 translation)
{
	_localTranslation += translation;
	hasChanged = true;
}

void Transform::Rotate(float angle, glm::vec3 axes)
{
	glm::rotate(_localQuat, angle, axes);
	hasChanged = true;
}

void Transform::Scale(float scale)
{
	_localScale += scale;
	hasChanged = true;
}

glm::mat4 Transform::GetWorldMatrix(glm::mat4 parentMat)
{
	// due to this flag, the world matrix only needs to be compute when its called and changed
	if (!hasChanged) {
		return _toWorld;
	}

	_toWorld = parentMat * CreateLocalMat();
	hasChanged = false;
	return _toWorld;
}