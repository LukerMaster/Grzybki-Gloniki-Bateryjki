#include <iostream>
#include "src/Application.h"
#include "SFML/Graphics.hpp"
//#pragma comment(lib, "extern\\lib\\*.lib")

int main()
{
	srand(time(NULL));
	Application app(700, 700, 60.0f, false);
	app.Run();
	return 0;
}