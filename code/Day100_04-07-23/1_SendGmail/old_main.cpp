#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <curl/curl.h>

struct EmailData {
    const char* data;
    size_t size;
    size_t bytes_read;
};

// Callback function to read data from the email body
static size_t read_data_callback(void *ptr, size_t size, size_t nmemb, void *userp) {
    EmailData *email_data = static_cast<EmailData *>(userp);
    size_t room = size * nmemb;

    if (email_data->size == 0) {
        return 0;
    }

    const char *data = &email_data->data[email_data->bytes_read];
    if (data) {
        size_t len = std::min(room, email_data->size);
        memcpy(ptr, data, len);
        email_data->bytes_read += len;
        email_data->size -= len;

        return len;
    }

    return 0;
}

bool get_password(std::string &password)
{
    // Read the password from the file "secret"
    std::ifstream secret_file("./secret");
    if (secret_file.is_open())
    {
        getline(secret_file, password);
        secret_file.close();
        return true;
    }
    return false;
}

int main()
{
    //struct upload_status upload_ctx = {0};

    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Error initializing libcurl." << std::endl;
        return 1;
    }
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // Email content
    const char *payload_text =
        "From: Watchtower Tester <watchtower.test2023@gmail.com>\r\n"
        "To: SPAM <spam.mhered@gmail.com>\r\n"
        "Subject: Sending an email with LIBCURL\r\n"
        "\r\n" // empty line to divide headers from body, see RFC 5322
        "Ain't this a cool email test?\r\n";

    // SMTP server details
    const std::string url = "smtps://smtp.gmail.com:465";
    const std::string username = "watchtower.test2023@gmail.com";
    std::string password; // To store the password

    if (!get_password(password))
    {
        std::cerr << "Error obtaining the password" << std::endl;
        return 2;
    }

    const std::string mail_from = "watchtower.test2023@gmail.com";
    const std::string mail_rcpt = "spam.mhered@gmail.com";

    // Set up the email data for the CURLOPT_READFUNCTION callback
    EmailData email_data = { payload_text, strlen(payload_text), 0 };
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &email_data);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); // use the data provided by the 
                                                // CURLOPT_READFUNCTION callback 
                                                // as the request body, to ensure
                                                // that the email content is sent 
                                                // correctly

    // Set up libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, mail_from.c_str());

    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, mail_rcpt.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    // Send the email
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "Failed to send the email. Error: " << curl_easy_strerror(res) << std::endl;
    }
    else
    {
        std::cout << "Email sent successfully." << std::endl;
    }

    // Clean up
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    return 0;
}