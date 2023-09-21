#link: https://curl.se/libcurl/c/smtp-mail.html

# 1_SendGmail

The goal of this project is to write a C++ class to send emails from a Gmail account.  

This is the first of a few tasks in which I split the project [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower). 

## Sending and retrieving emails with `curl`

Sending and retrieving emails is one of those basic tasks that one would expect to be straightforward in C++, but they really aren't. 

Searching for suitable libraries I found https://www.vmime.org/ and https://pocoproject.org/index.html, both of which seemed quite complicated. Even ChatGPT, when queried directly advised against C++ and proposed using the python Gmail API instead! See e.g. https://humberto.io/blog/sending-and-receiving-emails-with-python/.

Eventually I came across a recommendation to use `libcurl`, which is a C API for the `curl` command, as a way to send and receive email from a C++ program.

I decided to try first to make it work in the command line, using `curl` directly, and even that was a struggle. [Simple commands to send email via SMTP](https://everything.curl.dev/usingcurl/smtp) didn't work due to Gmail security settings. [These instructions](https://www.spamresource.com/2022/04/lets-send-emailwith-curl.html) - which describe also how to activate two-factor authentication in Gmail settings and create an app password - finally worked. 

Rather than hardcoding the password in the command, it seems a better idea to put the password in a `./secret` file and use `"``cat /home/mhered/cpp_100daysofcode/code/Day100_04-07-23/1_SendGmail/secret``"` to read it from there.

This idea I got from this link: https://helge.w.uib.no/use-curl-to-read-your-imap-emails/, which explains how to retrieve email with `curl` using IMAP. Note that this link was also the starting point for project [2_RetrieveAndParseEmail](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/2_RetrieveAndParseEmail) to write a class that retrieves email from a Gmail inbox and parses it to extract the fields.

Here is the final `curl` command:
```bash
$ curl --ssl-reqd --url 'smtps://smtp.gmail.com:465' --user "watchtower.test2023@gmail.com:`cat /home/mhered/cpp_100daysofcode/code/Day100_04-07-23/1_SendGmail/secret`" --mail-from 'watchtower.test2023@gmail.com' --mail-rcpt 'spam.mhered@gmail.com' --upload-file - << EOF
From: Watchtower Tester <watchtower.test2023@gmail.com>
To: SPAM <spam.mhered@gmail.com>
Subject: Test 

Email body

EOF
```

## Using libcurl to implement 1_SendGmail in a C++ program

Next step was going from the above `curl` command to a C++ program that would achieve the same result using `libcurl`:

First I followed this `libcurl` tutorial: https://www.youtube.com/watch?v=g83kYIQNRwU, see project [0_LibcurlIntro](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/0_LibcurlIntro).

Then I went to ChatGPT for help: https://chat.openai.com/share/a11264b1-6d55-4fed-9703-1d181db571dd 

ChatGPT struggled to provide a proper set up of CURLOPT_READFUNCTION and CURLOPT_READDATA. It sent me looking at SSL settings and STARTTLS and whatnot. It was not successful either at helping me get proper debug info. 

Eventually I found an answer in this example: https://curl.se/libcurl/c/smtp-mail.html : I was not setting explicitly CURLOPT_UPLOAD to 1L which apparently was needed to tell `libcurl` to use the data provided by the CURLOPT_READFUNCTION callback as the request body. The result in [./old_main.cpp.txt](./old_main.cpp.txt), which was the first version that worked.

To conclude, I asked ChatGPT to refactor the code and encapsulate it in a class. This, it did reasonably well, but the truth is that at every step I had to manually fine tune and guide ChatGPT to get the desired result. Still helpful, but far from autonomous.

The `EmailSender` class public methods are a constructor, a destructor and a `sendEmail()` method. The `getPassword()` private method reads the password from the file `./secret`. In this simple implementation, server and username are hardcoded.

I also created auxiliary function `getRFC5322FormattedCurrentDateTime()` to format the current date as per the RFC 5322 standard used by email.

## Resources
- [How to send email using c++ (curl) - Stack Overflow](https://stackoverflow.com/questions/51044049/how-to-send-email-using-c-curl?rq=3)            
- [libcurl - programming tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)            
- [libcurl example - smtp-ssl.c](https://curl.se/libcurl/c/smtp-ssl.html)            
- [libcurl example - smtp-mail.c](https://curl.se/libcurl/c/smtp-mail.html)            
- [Sending email - Everything curl](https://everything.curl.dev/usingcurl/smtp)            
- [Let's send email....with curl!](https://www.spamresource.com/2022/04/lets-send-emailwith-curl.html)            
- [bash - Fetching and deleting a message over IMAP using cURL - Stack Overflow](https://stackoverflow.com/questions/49429092/fetching-and-deleting-a-message-over-imap-using-curl?rq=3)            
- [Python quickstart  | Gmail  | Google for Developers](https://developers.google.com/gmail/api/quickstart/python)            
- [Use Curl to read your imap emails – Helge's blog](https://helge.w.uib.no/use-curl-to-read-your-imap-emails/)            
- [Mailboxes with children are reported as "(\HasNoChildren)" if mailbox with similar name · Issue #3182 · cyrusimap/cyrus-imapd](https://github.com/cyrusimap/cyrus-imapd/issues/3182)            
- [Using libcurl to send a gmail message](https://groups.google.com/g/curlpp-devel/c/AeVImjan2S4?pli=1)            
- [embeddedmz/mailclient-cpp: C++ client for making POP/SMTP/IMAP requests](https://github.com/embeddedmz/mailclient-cpp)            
- [Test an IMAP connection with cURL – Bram.us](https://www.bram.us/2020/01/16/test-an-imap-connection-with-curl/)        

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [x] dates_times: timezones
- [x] file_management: input, output, folders and files
- [ ] testing
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
- [x] web_scraping
- [ ] OpenCV
- [x] email