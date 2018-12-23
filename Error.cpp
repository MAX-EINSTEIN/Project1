#include "Error.h"
#include <SDL.h>



void fatalError(std::string errorDescription) {
	std::cout << errorDescription << std::endl;
	std::cout << "\nEnter any key to Quit!!!" << std::endl;
	system("pause");
	SDL_Quit();
	exit(1);
}
