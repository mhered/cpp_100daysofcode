#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <unordered_map>

// Function to format the date string
std::string formatDate(const std::string& date)
{
    // Mapping of month names to their corresponding numbers
    std::unordered_map<std::string, std::string> monthMap = {
        {"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"May", "05"}, {"Jun", "06"},
        {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}
    };

    std::string formattedDate;
    
    // Extract the month and day from the date string
    std::string month = date.substr(0, 3);
    std::string day = date.substr(4);
    
    // Check if the month exists in the map
    if (monthMap.count(month) > 0)
    {
        // Format the date as "DD/MM"
        formattedDate = day + "/" + monthMap[month];
    }
    else
    {
        // Invalid month name
        formattedDate = "Invalid";
    }
    
    return formattedDate;
}


// Callback function to write fetched data into a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t total_size = size * nmemb;
    response->append(static_cast<char *>(contents), total_size);
    return total_size;
}

std::vector<std::pair<std::string, std::string>> fetchBankHolidays(std::string country, int year)
{
    // Variable for storing output
    std::vector<std::pair<std::string, std::string>> bankHolidays;

    // Create the URL string
    std::string url = "https://www.officeholidays.com/countries/" + country + "/" + std::to_string(year);

    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if (curl)
    {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Create a string to store the fetched data
        std::string response;

        // Set the callback function to write the data into the string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // Parse the HTML response
            htmlDocPtr doc = htmlReadDoc(reinterpret_cast<const xmlChar *>(response.c_str()), nullptr, nullptr, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
            if (doc)
            {
                // Create an XPath context
                xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
                if (xpathCtx)
                {
                    // Register the namespaces used in the XPath expressions
                    xmlXPathRegisterNs(xpathCtx, BAD_CAST "html", BAD_CAST "http://www.w3.org/1999/xhtml");

                    // Evaluate the XPath expression to select the table rows
                    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(BAD_CAST "//html:table[@id='public_holidays']/html:tbody/html:tr", xpathCtx);

                    xpathObj = xmlXPathEvalExpression(BAD_CAST "//table[@class='country-table']//tr[position() > 1]", xpathCtx);
                    if (xpathObj == NULL)
                    {
                        std::cerr << "XPath evaluation failed." << std::endl;
                        // Handle the error
                    }

                    if (xpathObj)
                    {
                        // Iterate over the selected table rows
                        xmlNodeSetPtr nodes = xpathObj->nodesetval;

                        if (nodes != NULL)
                        {
                            for (int i = 0; i < nodes->nodeNr; ++i)
                            {
                                // Extract the date and holiday name from each row
                                xmlNodePtr node = nodes->nodeTab[i];
                                xmlNodePtr weekdayNode = xmlFirstElementChild(node);
                                xmlNodePtr dateNode = xmlNextElementSibling(weekdayNode);
                                xmlNodePtr holidayNode = xmlNextElementSibling(dateNode);

                                // Get the date and holiday name as strings
                                std::string date = reinterpret_cast<char *>(xmlNodeGetContent(dateNode));
                                std::string holiday = reinterpret_cast<char *>(xmlNodeGetContent(holidayNode));

                                // Add the date and holiday name to the vector
                                bankHolidays.push_back(std::make_pair(formatDate(date), holiday));
                            }
                        }
                        else
                        {
                            std::cerr << "Nodes object is NULL." << std::endl;
                            // Handle the error
                        }

                        // Cleanup XPath object
                        xmlXPathFreeObject(xpathObj);
                    }

                    // Cleanup XPath context
                    xmlXPathFreeContext(xpathCtx);
                }

                // Cleanup parsed document
                xmlFreeDoc(doc);
            }
        }

        // Clean up curl
        curl_easy_cleanup(curl);
    }

    return bankHolidays;
}

int main()
{
    std::string country_code;
    int year;

    std::cout << "Enter the country code (e.g., us, uk): ";
    std::cin >> country_code;
    std::cout << "Enter the year: ";
    std::cin >> year;

    std::vector<std::pair<std::string, std::string>> holidays = fetchBankHolidays(country_code, year);

    std::cout << "| Date | Holiday |\n";
    std::cout << "|------|---------|\n";

    for (const auto &holiday : holidays)
    {
        std::cout << "| " << holiday.first << " | " << holiday.second << " |\n";
    }

    return 0;
}