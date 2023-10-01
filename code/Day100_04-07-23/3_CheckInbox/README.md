#link: https://curl.se/libcurl/c/smtp-mail.html

# CheckInbox

The goal of this project is to write a C++ bot to monitor a Gmail Inbox and perform a given action whenever a new email is received.

This is the third of a few tasks in which I split the project [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower). 

I played with ChatGPT, IMAP FETCH and IMAP IDLE and I got to a while loop that checks regularly and produces a rather useless list of outputs with UIDs and subject length, see sample output below. 

I ended up giving up and changing the approach. 

See project [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower) for the solution I finally implemented instead: 
- store in a config file the UID of the last email that was processed by the app
- at regular intervals check for new email by attempting to download the next email by UID
- if successful, process the new email and repeat until no more email found


```bash
Checking for email...
* 1 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {150}

* 2 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {77}

* 3 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {118}

* 4 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {72}

* 5 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {64}

* 6 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {86}

* 7 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {113}

* 8 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {113}

* 9 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {152}

* 10 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {76}

* 11 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {74}

* 12 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {70}

* 13 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {70}

* 14 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {71}

* 15 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {51}

* 16 FETCH (FLAGS (\Seen) BODY[HEADER.FIELDS (FROM SUBJECT)] {66}

...
```

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [x] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV
- [x] email