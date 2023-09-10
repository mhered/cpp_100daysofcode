#include <iostream>
#include <curl/curl.h>
#include <string>

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{

    // data is in contents
    // size of data is nmemb units of size size
    size_t realsize = size * nmemb;

    // userp is a pointer to local data

    // Cast to string
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    // Create a handle
    CURL *curl = curl_easy_init();

    if (curl)
    {
        // minimal download example

        // Set options
        curl_easy_setopt(curl, CURLOPT_URL, "https://curl.se"); // Set URL
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);     // Follow redirects

        std::string response_string;
        // set the callback function to write_callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        // ser the userp to response_string
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // perform the transfer. Returns ok or >100 error msgs
        CURLcode result = curl_easy_perform(curl);

        if (result == CURLE_OK)
        {
            char *ct;
            // get the content-type
            result = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if (ct)
            {
                std::cout << "We received Content-Type: " << ct << std::endl;
            }
        }
        else
        {
            std::cerr << "Transfer failed: " << curl_easy_strerror(result) << std::endl;
        }

        // minimal upload example

        // Set options
        curl_easy_setopt(curl, CURLOPT_URL, "https://curl.se"); // Set URL
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Hello");

        // perform the transfer. Returns ok or >100 error msgs
        result = curl_easy_perform(curl);

        if (result != CURLE_OK)
        {
            std::cerr << "Transfer failed: " << curl_easy_strerror(result) << std::endl;
        }

        // Kill handle
        curl_easy_cleanup(curl);
    }
    return 0;
}