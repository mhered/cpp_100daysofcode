#link: https://forum.arduino.cc/t/serial-input-basics-updated/382007 

# Morse (Part 3)
The goal of this 3-part mini series is to build a Morse translator that receives a string message and transmits the message by flashing a LED controlled by an Arduino. 

This exercise was loosely inspired by Tutorial #4 of the Arduino Tutorial series by Paul McWhorter https://www.youtube.com/watch?v=nPOKOi1jIK0&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=9

On Part 3 the task is to interface with Arduino, i.e.:

- [x] send the Morse message through serial to Arduino
- [x] operate the LED to transmit the message

I used the tutorial in the link to implement manual input via serial transfer https://forum.arduino.cc/t/serial-input-basics-updated/382007 . I used `miniterm` (see my notes on installation and usage here: https://github.com/mhered/manolobot/blob/main/Part-3-manolobot-Nov22.md)

With this I can copy the output of `morse` (see project [Morse2](https://github.com/mhered/cpp_100daysofcode/tree/main/code/Day031_26-04-23/Morse2)) and manually paste it in `miniterm` to get Arduino to operate the LED:

```bash
$ ./morse -s "Hello, world!"
"-.-.- /.... . .-.. .-.. --- --..-- /.-- --- .-. .-.. -.. -.-.-- /...-.- "
"1110101110101110000000101010100010001011101010001011101010001110111011100011101110101011101110000000101110111000111011101110001011101000101110101000111010100011101011101011101110000000101010111010111000"
Sent Message: "<CT> HELLO, WORLD! <SK>"

$ miniterm

--- Available ports:
---  1: /dev/ttyUSB0         'USB Serial'
--- Enter port index or full name: 1
--- Miniterm on /dev/ttyUSB0  9600,8,N,1 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
Just received: 1110101110101110000000101010100010001011101010001011101010001110111011100011101110101011101110000000101110111000111011101110001011101000101110101000111010100011101011101011101110000000101010111010111000
SUCCESS Message sent!

--- exit ---
```

## To do

Next step is to check this C++ library: https://libserial.readthedocs.io/en/latest/install.html to communicate via serial directly from a C++ program instead of having to manually type or copy & paste the sequence of 01010s

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
- [x] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV