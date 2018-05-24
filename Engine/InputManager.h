#pragma once
#include <map>
#include <SDL\SDL.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void init();
	void Update();
	bool IsKeyDown(Uint8 key);

private:
	std::map<Uint8, bool> _keyMap;
	std::map<Uint8, bool> _previousKeyMap;

	void CopyNewToOld();
	void setKeyPressed(Uint8 key, bool b) { _keyMap.at(key) = b; }
};