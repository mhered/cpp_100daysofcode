#ifndef EMAILEXTRACT_H
#define EMAILEXTRACT_H

#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <regex>
#include <stdexcept>

// Custom exception class for CURL errors
class CurlException : public std::runtime_error
{
public:
    CurlException(const std::string &message) : std::runtime_error(message) {}
};

// Define an Email class to store email fields
class Email
{
public:
    std::string date;
    std::string from;
    std::string to;
    std::string subject;
    std::string plainTextBody;
    std::string htmlBody;

    void print();
};

void Email::print()
{
    // Print the extracted fields
    std::cout << "Date: " << date << std::endl;
    std::cout << "From: " << from << std::endl;
    std::cout << "To: " << to << std::endl;
    std::cout << "Subject: " << subject << std::endl;
    std::cout << "Plain Text Body:\n"
              << plainTextBody << std::endl;
    std::cout << "HTML Body:\n"
              << htmlBody << std::endl;
}

// Callback function to write data to a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

// Define an EmailExtractor class for email extraction
class EmailExtractor
{
public:
    Email extractEmailFields(const std::string &emailResponse);

private:
    std::string extractBoundary(const std::string &emailResponse);
};

std::string extractEmail(std::string aString){
    // Regular expression to extract email
    //std::regex emailRegex("([a-z\.\-_]+@[a-z\.\-_]+)");
    std::regex emailRegex("([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4})");

    // std::regex emailRegex("(a-z\.+@[a-z\.+)");
    std::smatch matches;
    if (std::regex_search(aString, matches, emailRegex))
    {
        return matches[1];
    }
    return "";
}


Email EmailExtractor::extractEmailFields(const std::string &emailResponse)
{
    Email email;

    // Regular expressions to extract email fields
    std::regex dateRegex(R"(Date: (.+))");
    std::regex fromRegex(R"(From: (.+))");
    std::regex toRegex(R"(To: (.+))");
    std::regex subjectRegex(R"(Subject: (.+))");

    // Extract date, from, to, and subject
    std::smatch matches;
    if (std::regex_search(emailResponse, matches, dateRegex))
    {
        email.date = matches[1];
    }
    if (std::regex_search(emailResponse, matches, fromRegex))
    {
        email.from = extractEmail(matches[1]);
    }
    if (std::regex_search(emailResponse, matches, toRegex))
    {
        email.to = matches[1];
    }
    if (std::regex_search(emailResponse, matches, subjectRegex))
    {
        email.subject = matches[1];
    }

    // Find the boundary marker in the Content-Type header
    std::string boundary = extractBoundary(emailResponse);

    if (!boundary.empty())
    {
        size_t boundaryStart = emailResponse.find(boundary);

        while (boundaryStart != std::string::npos)
        {
            boundaryStart += boundary.size();
            // Find the end of the current boundary section
            size_t boundaryEnd = emailResponse.find(boundary, boundaryStart);
            if (boundaryEnd != std::string::npos)
            {
                // Extract the content within the boundary section
                std::string boundarySection = emailResponse.substr(boundaryStart, boundaryEnd - boundaryStart);

                // Determine the section header
                size_t headerStart = boundarySection.find("Content-Type:");
                if (headerStart != std::string::npos)
                {
                    size_t headerEnd = boundarySection.find("\r\n\r\n", headerStart);
                    if (headerEnd != std::string::npos)
                    {
                        std::string sectionHeader = boundarySection.substr(headerStart, headerEnd - headerStart);

                        // Determine if it's plain text or HTML and store in the appropriate variable
                        std::string content = boundarySection.substr(headerEnd);

                        if (sectionHeader.find("text/plain") != std::string::npos)
                        {
                            email.plainTextBody = content;
                        }
                        else if (sectionHeader.find("text/html") != std::string::npos)
                        {
                            email.htmlBody = content;
                        }
                    }
                }

                // Move to the next boundary
                boundaryStart = boundaryEnd;
            }
            else
            {
                // No more boundaries found, exit the loop
                break;
            }
        }
    }

    return email;
}

std::string EmailExtractor::extractBoundary(const std::string &emailResponse)
{
    std::regex boundaryRegex(R"(Content-Type: .*boundary=["']?([^"'\s]+)["']?)");
    std::smatch matches;
    if (std::regex_search(emailResponse, matches, boundaryRegex))
    {
        return "--" + matches[1].str();
    }
    return "";
}

// Define an EmailClient class for handling email operations
class EmailClient
{
public:
    Email fetchEmail(const std::string &username,
                     const std::string &password,
                     const std::string &serverURL,
                     const std::string &emailUID);
};

Email EmailClient::fetchEmail(const std::string &username,
                              const std::string &password,
                              const std::string &serverURL,
                              const std::string &emailUID)
{
    CURL *curl;
    CURLcode res;
    std::string response; // To store the response

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl)
    {
        // Set the URL
        std::string url = serverURL + "INBOX;UID=" + emailUID;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set user credentials
        std::string credentials = username + ":" + password;
        curl_easy_setopt(curl, CURLOPT_USERPWD, credentials.c_str());

        // Set the write callback function to store the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        std::string errorMessage;

        // Check for errors
        if (res != CURLE_OK)
        {
            errorMessage = "CURL request failed(";
            errorMessage += res;
            errorMessage += "): ";
            errorMessage += std::string(curl_easy_strerror(res));
            if (res == CURLE_REMOTE_FILE_NOT_FOUND)
            {
                curl_easy_cleanup(curl);
                throw CurlException(errorMessage);
            }
            std::cerr << errorMessage << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr << "Failed to initialize libcurl." << std::endl;
    }

    // Now, 'response' contains the response data as a string
    EmailExtractor extractor;
    return extractor.extractEmailFields(response);
}

#endif