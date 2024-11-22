#include <string>

#include "application.h"

int main(int argc, char* argv[])
{
    std::string configFileName("config.json");
    if (argc >= 2)
    {
        configFileName = std::string(argv[1]);
    }

    Application application(configFileName);
    application.run();
    return 0;
}
