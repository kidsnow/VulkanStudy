#include "VKApplication.h"
#include <iostream>


int main()
{
	VKApplication app;

    try {
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
	
	return 0;
}