#include <iostream>
#include "EmailExtractor.h"
#include "Configuration.h"
#include "ParseBody.h"
#include "dbManager.h"
#include <thread>

bool SaveRecord(std::string link,
                std::string title,
                std::string comment,
                std::string date,
                std::string from)
{
    // for the moment this only prints the record to the console
    std::cout << "Found a new record contributed by " << from << " on " << date << "." << std::endl;
    std::cout << "  - Title: " << title << std::endl;
    std::cout << "  - Link: " << link << std::endl;
    std::cout << "  - Comment: " << comment << std::endl
              << std::endl;
    return true;
}

bool isValidURL(std::string aString)
{
    // Regular expression to match a valid URL
    std::regex urlRegex("(https?|ftp)://[^\\s/$.?#].[^\\s]*");

    // Use std::regex_search to check if the string matches the pattern
    return std::regex_search(aString, urlRegex);
}

int main()
{
    // create an Email retriever

    std::string jsonFilePath = "config.json";

    Configuration config;

    if (!config.getConfiguration(jsonFilePath))
    {
        std::cerr << "Failed to get configuration from JSON file:" << jsonFilePath << std::endl;
        return 0;
    }

    // database manager
    dbManager manager;
    // Open a database connection
    manager.init("watchtower.db");

    EmailClient client;
    Email email;

    // Fetch and extract email fields

    int UID = std::stoi(config.lastEmailUID);
    UID++;

    std::string link;
    std::string comment;
    std::string title;

    // increment
    while (true)
    {
        try
        {
            std::cout << "Fetching email with UID " << UID << " : ";
            email = client.fetchEmail(config.email, config.password, config.serverUrl, std::to_string(UID));
        }
        catch (const std::exception &e)
        {
            if (std::string("CURL request failed(N): Remote file not found").compare(e.what()) == 0)
            {
                std::cerr << "Not found. Retrying in 10 secs..." << std::endl;
                // if no more emails: wait and try again same UID
                std::this_thread::sleep_for(std::chrono::seconds(10));
                continue;
            }
            else
            {
                // real error
                std::cout << "<" << e.what() << ">" << std::endl;
                throw e;
            }
        };
        if (config.isSenderAuthorised(email.from))
        {
            link = extractLink(email.plainTextBody);
            if (isValidURL(link))
            { // minimum condition to save a record is that there is a link
                Record newRecord(link,
                                 extractTitle(email.plainTextBody),
                                 extractComment(email.plainTextBody),
                                 email.from,
                                 email.date,
                                 {}); // for the moment no tags

                if (manager.addRecord(newRecord))
                    SaveRecord(newRecord.link,
                               newRecord.title,
                               newRecord.comments,
                               newRecord.date,
                               newRecord.sender);
                // persist the UID
                config.lastEmailUID = std::to_string(UID);
                config.saveCurrentConfiguration();
            }
            else
            {
                std::cout << "No valid link found in body. Skipping..." << std::endl;
            }
        }
        else
        {
            std::cout << "Sender " << email.from
                      << " is not authorised. Skipping..." << std::endl;
        }
        UID++;
    };

    return 0;
}