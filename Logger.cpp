#include "Logger.h"
#include <iostream>
#include <SDL/SDL.h>

void fatalError(std::string error)
{
	std::cout << "A fatal error occured" << std::endl;
	std::cout << error << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	char c;
	std::cin >> c;
	SDL_Quit();
}