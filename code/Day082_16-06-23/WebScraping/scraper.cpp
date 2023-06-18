#include <iostream>
#include <gumbo.h>
#include <curl/curl.h>
#include <string>
#include <algorithm>
#include <cstring>

// `request` is a facility for making an HTTP request.
// allows the dictionary scraping tool to fetch markup from the Merriam-Webster site.
// Defined in the `request` function are immutable primitives:
// - a client name to identify the scraper via user-agent header,
// - and language artifacts for writing server response markup into memory.
// The sole parameter is the word that constitutes a portion of the URL path,
// definitions of which are sourced by the scraper.
std::string request(std::string word);

// `scrape` function feeds the markup from the `request` into `find_definitions`
// for selectively iterative DOM traversal.
// We use the gumbo parser in this function, which returns a string containing
// a list of word definitions.
std::string scrape(std::string markup);

// `find_definitions` function recursively harvests definitions from the span HTML elements
// with the unique class identifier "dtText". It extracts definition text
// via the extract_text function on each successful iteration
// from each HTML node in which that text is enclosed.
std::string find_definitions(GumboNode *node);

// `extract_text` function extracts text from each node that is not
// a script or style tag. The function funnels the text to the str_replace
// routine, which replaces the leading colon with the binary > symbol.
std::string extract_text(GumboNode *node);

// `str_replace` function replaces every instance of a specified search string
// in a larger string with another string.
std::string str_replace(std::string search, std::string replace, std::string &subject);

int main(int argc, char **argv)
{
    std::string arg;

    if (argc != 2)
    {
        std::cout << "Please provide a valid English word" << std::endl;
        // exit(EXIT_FAILURE);
        arg = "esoteric";
        std::cout << "Using " << arg << " as example..." << std::endl
                  << std::endl;
    }
    else
        arg = argv[1];

    std::string res = request(arg);
    std::cout << "\"" << arg << "\":" << std::endl;
    std::cout << scrape(res) << std::endl;

    return EXIT_SUCCESS;
}

// `request` is a facility for making an HTTP request.
// allows the dictionary scraping tool to fetch markup from the Merriam-Webster site.
// Defined in the `request` function are immutable primitives:
// - a client name to identify the scraper via user-agent header,
// - and language artifacts for writing server response markup into memory.
// The sole parameter is the word that constitutes a portion of the URL path,
// definitions of which are sourced by the scraper.

typedef size_t (*curl_write)(char *, size_t, size_t, std::string *);

std::string request(std::string word)
{
    CURLcode res_code = CURLE_FAILED_INIT;
    CURL *curl = curl_easy_init();
    std::string result;
    std::string url = "https://www.merriam-webster.com/dictionary/" + word;

    curl_global_init(CURL_GLOBAL_ALL);

    if (curl)
    {
        curl_easy_setopt(curl,
                         CURLOPT_WRITEFUNCTION,
                         static_cast<curl_write>([](char *contents, size_t size,
                                                    size_t nmemb, std::string *data) -> size_t
                                                 {
        size_t new_size = size * nmemb;
        if (data == NULL) {
          return 0;
        }
        data -> append(contents, new_size);
        return new_size; }));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple scraper");

        res_code = curl_easy_perform(curl);

        if (res_code != CURLE_OK)
        {
            return curl_easy_strerror(res_code);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return result;
}

// `scrape` function feeds the markup from the `request` into `find_definitions`
// for selectively iterative DOM traversal.
// We use the gumbo parser in this function, which returns a string containing
// a list of word definitions.

std::string scrape(std::string markup)
{
    std::string res = "";
    GumboOutput *output = gumbo_parse_with_options(&kGumboDefaultOptions, markup.data(), markup.length());

    res += find_definitions(output->root);

    gumbo_destroy_output(&kGumboDefaultOptions, output);

    return res;
}

// `find_definitions` function recursively harvests definitions from the span HTML elements
// with the unique class identifier "dtText". It extracts definition text
// via the extract_text function on each successful iteration
// from each HTML node in which that text is enclosed.
std::string find_definitions(GumboNode *node)
{
    std::string res = "";
    GumboAttribute *attr;
    if (node->type != GUMBO_NODE_ELEMENT)
    {
        return res;
    }

    if ((attr = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        strstr(attr->value, "dtText") != NULL)
    {
        res += extract_text(node);
        res += "\n";
    }

    GumboVector *children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i)
    {
        res += find_definitions(static_cast<GumboNode *>(children->data[i]));
    }

    return res;
}

// `extract_text` function extracts text from each node that is not
// a script or style tag. The function funnels the text to the str_replace
// routine, which replaces the leading colon with the binary > symbol.
std::string extract_text(GumboNode *node)
{
    if (node->type == GUMBO_NODE_TEXT)
    {
        return std::string(node->v.text.text);
    }
    else if (node->type == GUMBO_NODE_ELEMENT &&
             node->v.element.tag != GUMBO_TAG_SCRIPT &&
             node->v.element.tag != GUMBO_TAG_STYLE)
    {
        std::string contents = "";
        GumboVector *children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i)
        {
            std::string text = extract_text((GumboNode *)children->data[i]);
            if (i != 0 && !text.empty())
            {
                contents.append("");
            }

            contents.append(str_replace(":", ">", text));
        }

        return contents;
    }
    else
    {
        return "";
    }
}

// `str_replace` function replaces every instance of a specified search string
// in a larger string with another string.
std::string str_replace(std::string search, std::string replace, std::string &subject)
{
    size_t count;
    for (std::string::size_type pos{};
         subject.npos != (pos = subject.find(search.data(), pos, search.length()));
         pos += replace.length(), ++count)
    {
        subject.replace(pos, search.length(), replace.data(), replace.length());
    }

    return subject;
}

/*
std::string strtolower(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);

  return str;
}*/
