#include "InputManager.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::init()
{
	for (int i = 0; i < 284; i++) {
		_keyMap.insert(std::make_pair(i, false));
	}
}

void InputManager::Update()
{
	CopyNewToOld();

	SDL_Event evnt;
	//process the input eventqueue
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_KEYDOWN: setKeyPressed(evnt.button.button, true);
			break;
		case SDL_KEYUP: setKeyPressed(evnt.button.button, false);
			break;
		case SDL_MOUSEMOTION:
			newMouse.x = evnt.motion.x;
			newMouse.y = evnt.motion.y;
			break;
		}
	}
}

bool InputManager::IsKeyDown(Uint8 key)
{
	return _keyMap[key];
}

void InputManager::CopyNewToOld()
{
	_previousKeyMap = _keyMap;
	oldMouse = newMouse;
}