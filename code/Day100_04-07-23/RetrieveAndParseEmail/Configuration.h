#ifndef CONFIG_H
#define CONFIG_H

#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Configuration
{
private:
    std::string jsonFilePath;

public:
    std::string email;
    std::string password;
    std::string serverUrl;
    std::string lastEmailUID;
    
    bool getConfiguration(const std::string &jsonFilePath);
    bool updateLastEmailUID(const std::string &newUID);
    void showConfiguration();
};

bool Configuration::getConfiguration(const std::string &aJsonFilePath)
{
    std::ifstream configFile(aJsonFilePath);

    if (!configFile.is_open())
    {
        std::cerr << "Failed to open JSON file: " << jsonFilePath << std::endl;
        return false;
    }

    try
    {
        nlohmann::json jsonData;
        configFile >> jsonData;

        // Check if the required fields exist in the JSON object
        if (jsonData.find("email") != jsonData.end() &&
            jsonData.find("password") != jsonData.end() &&
            jsonData.find("serverUrl") != jsonData.end() &&
            jsonData.find("lastEmailUID") != jsonData.end())
        {

            email = jsonData["email"].get<std::string>();
            password = jsonData["password"].get<std::string>();
            serverUrl = jsonData["serverUrl"].get<std::string>();
            lastEmailUID = jsonData["lastEmailUID"].get<std::string>();

            jsonFilePath = aJsonFilePath; // Update the jsonFilePath member variable

            return true;
        }
        else
        {
            std::cerr << "Required fields missing in JSON file:" << std::endl;
            if (jsonData.find("email") == jsonData.end())
            {
                std::cerr << "  - email" << std::endl;
            }
            if (jsonData.find("password") == jsonData.end())
            {
                std::cerr << "  - password" << std::endl;
            }
            if (jsonData.find("serverUrl") == jsonData.end())
            {
                std::cerr << "  - serverUrl" << std::endl;
            }
            if (jsonData.find("lastEmailUID") == jsonData.end())
            {
                std::cerr << "  - lastEmailUID" << std::endl;
            }
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
        return false;
    }
}

bool Configuration::updateLastEmailUID(const std::string &newUID)
{
    lastEmailUID = newUID;

    try
    {
        nlohmann::json jsonData;
        jsonData["email"] = email;
        jsonData["password"] = password;
        jsonData["serverUrl"] = serverUrl;
        jsonData["lastEmailUID"] = lastEmailUID;

        std::ofstream configFile(jsonFilePath);
        if (configFile.is_open())
        {
            configFile << jsonData.dump(4); // Pretty-print the JSON with an indentation of 4 spaces
            configFile.close();
            return true;
        }
        else
        {
            std::cerr << "Failed to open JSON file for writing: " << jsonFilePath << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error updating JSON file: " << e.what() << std::endl;
    }
    return false;
}

void Configuration::showConfiguration()
{
    std::cout << std::endl;
    std::cout << "Server URL: " << serverUrl << std::endl;
    std::cout << "Username: " << email << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Last Email UID Processed: " << lastEmailUID << std::endl;
    std::cout << std::endl;
}

#endif