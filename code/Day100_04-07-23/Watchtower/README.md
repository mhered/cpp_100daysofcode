#link:

# Watchtower

The task is to write an app to help a team create and maintain a news repository or "watchtower".
Each team member can send by email the news pieces they find relevant, using a prespecified format, to a designated email address managed by the app.
Specs:
- the app will monitor the specified email inbox
- when an email is received, the app will parse it to extract the following fields:
  - sender: the email address of the sender
  - date: the date of reception of the email
  - from inside the body of the email: 
    - link: a text field with a valid url 
    - title: a text field
    - comments: a text field
    - tags: a text field with a list of comma separated tags
- the app will process only emails coming from authorized users and where the link field contains a valid URL
- if any fields are missing, the app will reply by email to the sender asking for completion
- the app will check if there is already a record for the same link, and if not a new entry will be created in a persistent database
- if there is already a record for the same link in the database the app will attempt to merge the data and reply to the sender asking for confirmation to resolve any conflicts
- On a weekly basis the app will send out a formatted report to a distribution list

This final project is a complex undertaking, hence I split it into differente modules that I developed in separate projects:
-  [0_LibcurlIntro](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/0_LibcurlIntro): sending/retrieving email appears to be one of these basic tasks that you would expect to be reasonably easy to implement in C++ but are not. After some soul searching I settled for the good old `curl` command through its C API `libcurl`
-  [1_SendGmail](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/1_SendGmail): a class for sending email from Gmail account, including Gmail configuration
-  [2_RetrieveAndParseEmail](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/2_RetrieveAndParseEmail): classes for retrieving email from Gmail inbox by UID and parsing it to extract fields
-  [3_CheckInbox](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/3_CheckInbox): a few failed attempts to monitor an Inbox using IMAP FETCH and IMAP IDLE
-  [4_ManageDatabase](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/4_ManageDatabase): classes to manage a SQLite db to persist the records retrieved from emails
-  [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower): all elements put together

## To do

- [X] write function to read emails using `libcurl` 
- [X] extract fields from email and generate data structure
- [X] check sender has permissions and link is valid

Almost ready:
- [ ] store entry in persistent memory, e.g. with redis or SQLlite
- [ ] check if link already received and in this case merge new data in existing record
- [ ] compose and email periodic summaries

Pending:
- [ ] read tags from a preexisting list
- [ ] check if something is missing and reply to the sender asking for completion
- [ ] fix all README files


## Sending and receiving email with curl



# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [X] strings: regex
- [ ] dates_times: timezones
- [X] file_management: input, output, folders and files
- [X] testing
- [X] exceptions
- [ ] logging
- [X] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV




