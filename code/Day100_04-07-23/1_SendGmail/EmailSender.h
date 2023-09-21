#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>

// auxiliary implements for libcurl
// a struct to store the email data
struct EmailData
{
    const char *data;
    size_t size;
    size_t bytes_read;
};

// Callback function to read data from the email body
static size_t read_data_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    EmailData *email_data = static_cast<EmailData *>(userp);
    size_t room = size * nmemb;

    if (email_data->size == 0)
    {
        return 0;
    }

    const char *data = &email_data->data[email_data->bytes_read];
    if (data)
    {
        size_t len = std::min(room, email_data->size);
        memcpy(ptr, data, len);
        email_data->bytes_read += len;
        email_data->size -= len;

        return len;
    }

    return 0;
}

// a helper function to get the current date and time
// in the format required by RFC 5322
std::string getRFC5322FormattedCurrentDateTime()
{
    std::time_t now = std::time(nullptr);
    std::tm local_time;
    localtime_r(&now, &local_time);

    std::stringstream ss;
    ss << std::put_time(&local_time, "%a, %d %b %Y %H:%M:%S %z");
    return ss.str();
}

class EmailSender
{
public:
    EmailSender();

    ~EmailSender()
    {
        if (curl)
        {
            curl_easy_cleanup(curl);
        }
    }

    bool sendEmail(const std::vector<std::string> &recipients,
                   const std::string &subject,
                   const std::string &body);

private:
    CURL *curl = nullptr;
    std::string password;

    bool getPassword(); // Function to read the password from the file "secret"
};

EmailSender::EmailSender()
{
    // Initialize libcurl
    curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Error initializing libcurl." << std::endl;
        return;
    }
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // SMTP server details
    const std::string url = "smtps://smtp.gmail.com:465";
    const std::string username = "watchtower.test2023@gmail.com";

    if (!getPassword())
    {
        std::cerr << "Error obtaining the password" << std::endl;
        return;
    }

    const std::string mail_from = "watchtower.test2023@gmail.com";

    // Set up libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, mail_from.c_str());

    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
}


bool EmailSender::sendEmail(const std::vector<std::string> &recipients,
                            const std::string &subject,
                            const std::string &body)
{
    // Build the full email content, including headers
    std::string email_content = "From: Watchtower Tester <watchtower.test2023@gmail.com>\r\n";
    email_content += "To: ";
    for (size_t i = 0; i < recipients.size(); ++i)
    {
        email_content += recipients[i];
        if (i < recipients.size() - 1)
        {
            email_content += ",";
        }
    }
    email_content += "\r\n";
    email_content += "Date: " + getRFC5322FormattedCurrentDateTime() + "\r\n";
    email_content += "Subject: " + subject + "\r\n";
    email_content += "\r\n"; // empty line to divide headers from body, see RFC 5322
    email_content += body;

    // Set up the email data for the CURLOPT_READFUNCTION callback
    EmailData email_data = {email_content.c_str(), email_content.size(), 0};
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &email_data);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); // use the data provided by the
                                                // CURLOPT_READFUNCTION callback
                                                // as the request body, to ensure
                                                // that the email content is sent
                                                // correctly

    struct curl_slist *recipients_list = NULL;
    for (const std::string &recipient : recipients)
    {
        recipients_list = curl_slist_append(recipients_list, recipient.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients_list);

    // Send the email
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "Failed to send the email. Error: " << curl_easy_strerror(res) << std::endl;
        curl_slist_free_all(recipients_list);
        return false;
    }

    // Clean up
    curl_slist_free_all(recipients_list);
    return true;
}

bool EmailSender::getPassword()
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

#endif