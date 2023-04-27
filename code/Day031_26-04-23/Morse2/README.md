#link: https://en.wikipedia.org/wiki/Morse_code

# Morse (Part 2)
The goal of this 3-part mini series is to build a Morse translator that receives a string message and transmits the message by flashing a LED controlled by an Arduino. 

This exercise was loosely inspired by Tutorial #4 of the Arduino Tutorial series by Paul McWhorter https://www.youtube.com/watch?v=nPOKOi1jIK0&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=9

On Part 2 the task is to build a simple CLI that will accept a string and then: 

- [x] preprocess the string: e.g . strip it of non translatable characters, add appropriate tokens to start, end, etc.
- [x] translate to morse code, including pauses to an intermediate morse string. Use "." for dots, "-" for dashes, separate letters by spaces and words by "/". If a letter cannot be  translated, show a "#" in the output. 
- [x] Use this Online Morse translator https://morsecode.world/international/translator.html for testing. Note that the Online Morse Translator does not add the Start `<CT>` and End of Trasnmission `<SK>` prosigns.
- [x] translate to an appropriate format to transmit to the Arduino considering the durations stipulated by the International Morse Code (cfr. https://morsecode.world/international/morse2.html)

## Durations

- dot: one time unit
- dash: three units. 
- space between the components of one character: one unit
- space between characters in a word: three units
- space between words: seven units
- prosigns - indicated in the table using angled brackets - are combinations of two letters sent together with no space in between 
- other abbreviations and Q codes are sent with the normal spacing

We leave for Part 3 the interface with Arduino, i.e.:

- [ ] send the data through serial to Arduino
- [ ] operate the LED to transmit the message

Example output: 

```bash
$ ./morse -s "Hello, world!"
"-.-.- /.... . .-.. .-.. --- --..-- /.-- --- .-. .-.. -.. -.-.-- /...-.- "
"1110101110101110000000101010100010001011101010001011101010001110111011100011101110101011101110000000101110111000111011101110001011101000101110101000111010100011101011101011101110000000101010111010111000"
Sent Message: "<CT> HELLO, WORLD! <SK>"

$ ./morse -s "abcde FGHIJ klmno PQRST uvwxy z0123 45678 9.,?! ():"
"-.-.- /.- -... -.-. -.. . /..-. --. .... .. .--- /-.- .-.. -- -. --- /.--. --.- .-. ... - /..- ...- .-- -..- -.-- /--.. ----- .---- ..--- ...-- /....- ..... -.... --... ---.. /----. .-.-.- --..-- ..--.. -.-.-- /-.--. -.--.- ---... /...-.- "
"11101011101011100000001011100011101010100011101011101000111010100010000000101011101000111011101000101010100010100010111011101110000000111010111000101110101000111011100011101000111011101110000000101110111010001110111010111000101110100010101000111000000010101110001010101110001011101110001110101011100011101011101110000000111011101010001110111011101110111000101110111011101110001010111011101110001010101110111000000010101010111000101010101000111010101010001110111010101000111011101110101000000011101110111011101000101110101110101110001110111010101110111000101011101110101000111010111010111011100000001110101110111010001110101110111010111000111011101110101010000000101010111010111000"
Sent Message: "<CT> ABCDE FGHIJ KLMNO PQRST UVWXY Z0123 45678 9.,?! (): <SK>"

$ ./morse -s "       Hello!       ; "
"-.-.- /.... . .-.. .-.. --- -.-.-- /# /...-.- "
"1110101110101110000000101010100010001011101010001011101010001110111011100011101011101011101110000000000000101010111010111000"
Sent Message: "<CT> HELLO! ; <SK>"

```



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
- [ ] web_scraping
- [ ] OpenCV