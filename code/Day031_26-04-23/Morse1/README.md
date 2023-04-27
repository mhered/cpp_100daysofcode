#link: https://morsecode.world/international/morse2.html

# Morse (Part 1)
The goal of this 3-part mini series is to build a Morse translator that receives a string message and transmits the message by flashing a LED controlled by an Arduino. 

On Part 1 the task is to build an auxiliary an function to read the equivalences between characters and morse codes from the file [morse_table.md](./morse_table.md) and use it to write in the terminal the C++ to initialize an array of `struc Morse` elements.

The format of the input file is a Markdown table i.e:

```markdown
| Symbol | Code |
| ------ | ---- |
| A      | .-   |
| B      | -... |
| C      | -.-. |
| D      | -..  |
| E      | .    |
| F      | ..-. |
| G      | --.  |
| H      | .... |
| I      | ..   |
| J      | .--- |
...
```

The goal is to print something like this, ready to copy&paste in C++: 
```c++
{"A" , ".-"},
{"B" , "-..."},
{"C" , "-.-."},
{"D" , "-.."},
{"E" , "."},
{"F" , "..-."},
{"G" , "--."},
{"H" , "...."},
{"I" , ".."},
{"J" , ".---"},
...
```

## Sources

<img src="./International_Morse_Code.png" style="zoom: 25%;" />

The file  [morse_table.md](./morse_table.md)  contains a subset of morse codes and prosigns of the International Morse Code, cfr. https://morsecode.world/international/morse2.html that will use for this exercise.

# Tags

#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [x] strings: regex
- [ ] dates_times: timezones
- [x] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [x] web_scraping
- [ ] OpenCV