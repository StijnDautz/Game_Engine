#include "Transform.h"

void Transform::Translate(glm::vec3 translation)
{
	_localTranslation += translation;
	hasChanged = true;
}

void Transform::Rotate(glm::vec3 rotation)
{
	eulerAngles += rotation;
	glm::quat x = glm::angleAxis(glm::radians(eulerAngles.x), glm::vec3(1, 0, 0));
	glm::quat y = glm::angleAxis(glm::radians(eulerAngles.y), glm::vec3(0, 1, 0));
	glm::quat z = glm::angleAxis(glm::radians(eulerAngles.z), glm::vec3(0, 0, 1));

	//_localQuat = x * y;
	//_localQuat = glm::normalize(_localQuat);

	hasChanged = true;
}

void Transform::Scale(float scale)
{
	_localScale += scale;
	hasChanged = true;
}

void Transform::Reset()
{
	_localTranslation = glm::vec3();
	eulerAngles = glm::vec3();
	_localScale = glm::vec3();

	//_localQuat = glm::quat();
}

glm::mat4 Transform::CreateLocalMat()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _localTranslation);
	
	//glm::mat4 rotationTranslate = glm::translate(glm::mat4(1.0f), -<point to rotate around>) //TODO!!! Translate point to rotate around to origin
	
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), eulerAngles.x, glm::vec3(1, 0, 0)); //Rotate around x-axis
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), eulerAngles.y, glm::vec3(0, 1, 0)); //Rotate around y-axis
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), eulerAngles.z, glm::vec3(0, 0, 1)); //Rotate around z-axis

	//glm::mat4 rotationTranslateBack = glm::translate(glm::mat4(1.0f), <point to rotate around>) //TODO!!! Translate back to the point to rotate around

	glm::mat4 rotate = /*rotationTranslateBack * */rotateX * rotateY * rotateZ /* *rotationTranslate*/;
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(_localScale));
	

	//glm::mat4 mat = glm::translate(glm::mat4(1.0f), _localTranslation);
	//mat = glm::scale(mat, _localScale);
	return scale * rotate * translate; //Matrix multiplication will be executed from Right -> Left
}

void Transform::AddChild(Transform * child)
{
	children.push_back(child);
	child->parent = this;
}

glm::mat4 Transform::GetWorldMatrix()
{
	// due to this flag, the world matrix only needs to be compute when its called and changed
	if (hasChanged) {
		// compute and set world matrix
		_toWorld = parent == nullptr ? CreateLocalMat() : parent->GetWorldMatrix() * CreateLocalMat();
		hasChanged = false;

		// let all other components of the transform's object know, that the worldMatrixChanged
		obj->OnMovement();
	}

	return _toWorld;
}