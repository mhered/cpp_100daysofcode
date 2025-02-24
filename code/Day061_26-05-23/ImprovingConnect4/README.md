#link:

# Improving Connect4
Refactor the code written for the project [Connect4](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day057_22-05-23/Connect4) to improve performance.

The original code was only working on a small board of size 4x4, although it took a long time to calculate the moves, especially the first ones. For larger boards, calculation took so long even starting with a board half way through the game that it was not viable...

## Tasks
* Add a timer to benchmark.
* Baseline for the 1st move on a 4x4 board: ~31s 


Working on `check_for_win()`

* replace `for(auto diagonal:diagonals)` by `for(int i=0; i< ; i++)` loops -> 15s
* check in each row, colum or diagonal if enough elements remain to reach 4 (count + remaining elements < MIN_DIAG) and skip to next if no chance -> 11s
* scan rows from top to bottom -> 10s 
* replace `std::vector<char> board`  for `bool bool_board[]` -> no improvement. Why?

## Links

* [connect 4 c++ - Google Search](https://www.google.com/search?channel=fs&client=ubuntu&q=connect+4+c%2B%2B) 
* [connect 4 game - C++ Forum](https://cplusplus.com/forum/general/67675/) 
* [c++ - Connect4 With AI - Code Review Stack Exchange](https://codereview.stackexchange.com/questions/119291/connect4-with-ai) 
* [An Exhaustive Explanation of Minimax, a Staple AI Algorithm](https://www.flyingmachinestudios.com/programming/minimax/) 
* https://gummianime.tripod.com/tutorials/connect4.txt
*  [connect 4 computer player c++ - Google Search](https://www.google.com/search?q=connect+4+computer+player+c%2B%2B&client=ubuntu&hs=R0i&channel=fs&sxsrf=APwXEdd-9VcZDV7H-SFnk30_p-Hcidd_zg%3A1684738575932&ei=DxJrZN3CONGgkdUP3qKY4Ag&ved=0ahUKEwidhu6irIj_AhVRUKQEHV4RBowQ4dUDCA4&uact=5&oq=connect+4+computer+player+c%2B%2B&gs_lcp=Cgxnd3Mtd2l6LXNlcnAQAzIFCAAQogQyBQgAEKIEMgUIABCiBDoKCAAQRxDWBBCwAzoGCAAQFhAeOggIABCKBRCGAzoFCCEQoAE6CAghEBYQHhAdOgcIIRCgARAKOgoIIRAWEB4QDxAdSgQIQRgAUJ0EWPMJYJELaAFwAXgAgAGYAYgBjQSSAQMwLjSYAQCgAQHIAQjAAQE&sclient=gws-wiz-serp) 
* [connect-4/main.cpp at master · shashwatregmi/connect-4](https://github.com/shashwatregmi/connect-4/blob/master/main.cpp)

# Tags
#tags: 

- [ ] basics
- [x] algorithms
- [ ] data_structures: trees, graphs
- [x] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [x] object_oriented_programming
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
- [x] games