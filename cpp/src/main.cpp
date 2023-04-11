#include "common.h"
#include "application.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Please provide a filename(.txt) as the only command line argument!";
        return 0;
    }
    Application app{argv[1]};
    app.run();
    return 0;
}





