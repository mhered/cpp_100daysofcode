#include <iostream>
#include <string>
#include <curl/curl.h>
#include <chrono>
#include <thread>
#include <fstream>

bool getPassword(std::string &password)
{
    std::ifstream secret_file("./secret");
    if (secret_file.is_open())
    {
        getline(secret_file, password);
        secret_file.close();
        return true;
    }
    return false;
}

struct EmailData
{
    std::string sender;
    std::string title;
};

// Callback function to be called when email data is received
size_t EmailReceivedCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t totalSize = size * nmemb;
    EmailData *emailData = static_cast<EmailData *>(userp);
    std::string header(reinterpret_cast<char *>(contents), totalSize);

    std::cout << header << std::endl;

    // Extract sender and title from email header (a basic example)
    size_t fromPos = header.find("From:");
    if (fromPos != std::string::npos)
    {
        size_t endOfLine = header.find("\r\n", fromPos);
        if (endOfLine != std::string::npos)
        {
            emailData->sender = header.substr(fromPos + 6, endOfLine - (fromPos + 6));
        }
    }

    size_t subjectPos = header.find("Subject:");
    if (subjectPos != std::string::npos)
    {
        size_t endOfLine = header.find("\r\n", subjectPos);
        if (endOfLine != std::string::npos)
        {
            emailData->title = header.substr(subjectPos + 9, endOfLine - (subjectPos + 9));
        }
    }

    return totalSize;
}

int main()
{

    std::string username = "watchtower.test2023@gmail.com";
    std::string serverURL = "imaps://imap.gmail.com:993/INBOX";
    std::string password;
    if (!getPassword(password))
    {
        std::cerr << "Error obtaining the password" << std::endl;
        return 1;
    }

    // Initialize the CURL session
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "CURL initialization failed." << std::endl;
        return 2;
    }

    // Set the IMAP server details for Gmail
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, serverURL.c_str());

    // Set the callback function
    EmailData emailData;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, EmailReceivedCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &emailData);

    while (true)
    {
        std::cout << "Checking for email..." << std::endl;

        // Set the FETCH command to retrieve new emails
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH 1:* (FLAGS BODY[HEADER.FIELDS (FROM SUBJECT)])");

        // Perform the IMAP FETCH operation
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "CURL IMAP FETCH failed: " << curl_easy_strerror(res) << std::endl;
        }
        else if (!emailData.sender.empty() && !emailData.title.empty())
        {
            std::cout << "You've got email from " << emailData.sender << ": " << emailData.title << std::endl;
            emailData.sender.clear();
            emailData.title.clear();
        }

        // Wait for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    // Clean up
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
