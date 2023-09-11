#include <iostream>
#include "Configuration.h"

int main()
{
    std::string jsonFilePath = "config.json";

    Configuration config;

    if (!config.getConfiguration(jsonFilePath))
    {
        std::cerr << "Failed to get configuration from JSON file." << std::endl;
        return 0;
    }

    config.showConfiguration();

    std::string newUid = "15"; // new UID value to be updated in the JSON file

    if (config.updateLastEmailUID(newUid))
    {
        std::cout << "Updated lastEmailUID to: " << newUid << std::endl;
    }
    else
    {
        std::cerr << "Failed to update lastEmailUID in JSON file." << std::endl;
    }

    config.showConfiguration();

    return 0;
}
