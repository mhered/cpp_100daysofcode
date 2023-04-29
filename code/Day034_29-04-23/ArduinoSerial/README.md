#link: https://libserial.readthedocs.io/en/latest/tutorial.html

# Sending data to Arduino over Serial

I am using the library libSerial:

```bash
$ sudo apt install libserial-dev
```

Finally got it to work after several hiccups:
* this will not work with `miniterm` open. Why?
* Every time you open a port Arduino reboots. You need to wait either providing a long timeout (5 secs) or as implemented keep reading serial until Arduino sends the agreed `<Ready>` message, before you attempt to send data to Arduino.
* apparently the standard behaviour of streams is to skip whitespace, need to add the modifier `std::noskipws`.
* apparently the ending of strings followed by newline when they are input manually with `miniterm` is `\r\n`. This casued me some headaches in a previous project. To replicate this behaviour and keep the same Arduino code for both cases: `my_string += "\r\n";`

## To Do
- [ ] would be nice to integrate this with the C++ code from [Morse2](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day031_26-04-23/Morse2) that generates the 1010s sequences and with the Arduino code from [Morse3](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day032_27-04-23/Morse3) that transmits the Morse code.
- [ ] would be even nicer to also add a [ProgressBar](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day033_28-04-23/ProgressBar) while Arduino is transmitting the morse code.

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