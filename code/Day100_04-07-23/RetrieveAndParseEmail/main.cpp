#include <iostream>
#include "EmailExtractor.h"
#include "Configuration.h"
#include "ParseBody.h"

int main()
{
    EmailClient client;

    std::string jsonFilePath = "config.json";

    Configuration config;

    if (!config.getConfiguration(jsonFilePath))
    {
        std::cerr << "Failed to get configuration from JSON file." << std::endl;
        return 0;
    }

    // Fetch and extract email fields
    Email email = client.fetchEmail(config.email, config.password, config.serverUrl, config.lastEmailUID);

    email.print();

    return 0;
}
