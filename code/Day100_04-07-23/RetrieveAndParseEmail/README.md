#link: https://curl.se/libcurl/c/smtp-mail.html

# RetrieveAndParseEmail

The goal of this project is to write a C++ class to retrieve an email by UID from a Gmail account, and then parse the response to extract the date, sender and body, and further process the body to extract the fields link, title and comment.


This is the second of a few tasks in which I split the project [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower).

## Retrieving an email with `curl`

As discussed in the README of the previous project, [SendGmail](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/SendGmail/README.md), sending and retrieving emails using C++ does not appear very straightforward. I was a bit put off by the apparent complexity of libraries such as https://www.vmime.org/ and https://pocoproject.org/index.html, and went for `libcurl`, the C API for the `curl` command. 

First I tried to retrieve an email from my inbox using `curl` directly in the command line, see https://helge.w.uib.no/use-curl-to-read-your-imap-emails/. Note that this only worked after I activated two-factor authentication in Gmail settings and created a dedicated app password. The process is described in these instructions https://www.spamresource.com/2022/04/lets-send-emailwith-curl.html, which also explain how to send email with `curl` and SMTP, and were the basis for project [SendGmail](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/SendGmail).

Below is the basic `curl` command to retrieve an email from a Gmail account by `UID`:

```bash
$ curl --url "imaps://imap.gmail.com:993/INBOX;UID=5" --user "YOUR_GMAIL_ADDRESS:APP_PASSWORD"
```

Note that the `UID` is a unique identifier of the email in the inbox. Here it was easy to choose the `UID` of the email I wanted manually because I was working with a dummy email account I had just created and there were only a handful of mails in the inbox, but I need to investigate more because there must be a better way to retrieve email and to account for deleted emails, moved emails etc.

Again, instead of hardcoding the password I stored it in a `./secret` file and called `"``cat /home/mhered/cpp_100daysofcode/code/Day100_04-07-23/SendGmail/secret``"`. 

Below is the full command and the output (abridged):

```bash
$ curl --url "imaps://imap.gmail.com:993/INBOX;UID=5" --user "watchtower.test2023@gmail.com:`cat /home/mhered/cpp_100daysofcode/code/Day100_04-07-23/RetrieveAndParseEmail/secret`"

Delivered-To: watchtower.test2023@gmail.com
Received: ...
...

[Skipped lots of gibberish]

...

From: Manuel Heredia <spam.mhered@gmail.com>
Date: Fri, 21 Jul 2023 01:38:11 +0200
Message-ID: <CAJ1m860uzxPOiMiJ1oGMoG3Rpu-xP6usOQnVE1gr-AEoJ3759g@mail.gmail.com>
Subject: test1
To: watchtower.test2023@gmail.com
Content-Type: multipart/alternative; boundary="000000000000d29d4f0600f3a4fb"

--000000000000d29d4f0600f3a4fb
Content-Type: text/plain; charset="UTF-8"

hello world

--000000000000d29d4f0600f3a4fb
Content-Type: text/html; charset="UTF-8"

<div dir="ltr">hello world<br></div>

--000000000000d29d4f0600f3a4fb--

```

Upon inspection of the response, regex seemed appropriate to extract the fields of interest .

## Using `libcurl` to implement the `EmailExtractor` class

Next step was going from the curl command:

```bash

$ curl --url "imaps://imap.gmail.com:993/INBOX;UID=5" --user "watchtower.test2023@gmail.com:`cat /path_to/secret`"
```

To a C++ program that would achieve the same result using `libcurl`.

I went to ChatGPT for help: https://chat.openai.com/share/6b51c0f8-79c5-4272-9168-fa94ec1e84c8

ChatGPT suggestion worked very well to download the email, store it in a string instead of printing it, and then parsing the fields. The regex to extract the Plain text and HTML versions of the body did take a few iterations.

Then I refactored the code - again with help from ChatGPT - and encapsulated it in a class `EmailExtractor`, which implements a public method `extractEmailFields()` to parse the `curl` response, and returns the fields of interest in a simple `Email` container class. 

The private method `extractBoundary()` uses regex to extract the delimiter string used to split sections of a multipart body such as Plain Text and HTML. In the example above the string is `000000000000d29d4f0600f3a4fb`, but it is different for each email retrieved.

```c++
class EmailExtractor
{
public:
    Email extractEmailFields(const std::string &emailResponse);

private:
    std::string extractBoundary(const std::string &emailResponse);
};
```

Below the declaration of the `Email` container class that stores the main email fields of interest and implements a simple public `print()` method:
```c++
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
```

The class can be found in the header file [./EmailExtractor.h](./EmailExtractor.h). Some offline unit tests using hardocded values and text files were defined in [./test_Email.cpp](./test_Email.cpp).

## Managing Configuration

Rather than hardcoding the configuration values, I took the time to write a `Configuration` class to retrieve from a JSON file the `username`, `password`, `serverUrl` parameters as well as the `lastEmailUID` - the UID of the last email successfully retrieved, which would later be used to check the inbox for new emails received. See a sample `config.json` below:

```json
{
    "email": "watchtower.test2023@gmail.com",
    "lastEmailUID": "15",
    "password": "PASSWORD",
    "serverUrl": "imaps://imap.gmail.com:993/"
}
```

The class `Configuration` implements a `getConfiguration()` method to read the JSON file from the path provided as parameter, a `updateLastEmailUID()` to update the parameter `lastEmailUID` in the JSON file, and a simple `showConfiguration()` method to display the current values. 

```c++
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
```

The class can be found in the header file [./Configuration.h](./Configuration.h), along with some crude testing in [./test_Configuration.cpp](./test_Configuration.cpp).

## Parsing the body to extract link, title and comments

Last but not least the header file [./ParseBody.h](./ParseBody.h) implements the following helper functions to parse the Plain Text version of the body to extract the fields of interest: `trimString()`, `extractLink()`, `extractTitle()` and `extractComment()`. There is also a simple unit test in [./test_Email.cpp](./test_Email.cpp).

The logic is the following:
- For the link, the code extracts everything after the delimiter `#link:` until either `#comment:`, `#title:` or the end of the string are found. The result is trimmed of any leading or trailing whitespace.
- Similarly for the title, the code extracts everything after the delimiter `#title:` until either `#comment:`, `#link:` or the end of the string are found. The result is trimmed of any leading or trailing whitespace.
- And again for the comments, the code extracts everything after the delimiter `#comment`: until either `#title:`, `#link`: or the end of the string are found. The result is trimmed of any leading or trailing whitespace.

This is not perfect (e.g. the Email signature is included in the last field) and also does not implement tags, therefore some additional future work will be needed.

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [x] strings: regex
- [ ] dates_times: timezones
- [x] file_management: input, output, folders and files
- [x] testing
- [ ] exceptions
- [ ] logging
- [x] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [x] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [x] web_scraping: curl
- [ ] OpenCV
- [x] email