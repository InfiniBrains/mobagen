#include <iostream>
#include "GameLoop.h"

int main()
{
	GameLoop *gameLoop = new GameLoop(1.0/60);
	std::cout << "Hello World!" << std::endl;
}
