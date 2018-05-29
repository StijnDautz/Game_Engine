#pragma once
#include <map>
#include <SDL\SDL.h>
#include <glm\glm.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void init();
	void Update();
	bool IsKeyDown(Uint8 key);
	glm::vec2 GetMouseMovement() { return newMouse - oldMouse; }
private:
	std::map<Uint8, bool> _keyMap;
	std::map<Uint8, bool> _previousKeyMap;
	glm::vec2 oldMouse;
	glm::vec2 newMouse;

	void CopyNewToOld();
	void setKeyPressed(Uint8 key, bool b) { _keyMap.at(key) = b; }
};