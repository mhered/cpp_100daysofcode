#link:

# Improving Connect4 (2)
Continue refactoring the code of the project [Connect4](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day057_22-05-23/Connect4) to improve performance.

The original code was only working on a small board of size 4x4, although it took a long time to calculate the moves, especially the first ones. For larger boards, calculation took so long even starting with a board half way through the game that it was not viable...

## Tasks
* Add a timer to benchmark.
* Baseline for the 1st move on a 4x4 board: ~31s 


Working on `check_for_win()`

* replace `for(auto diagonal:diagonals)` by `for(int i=0; i< ; i++)` loops -> 15s
* check in each row, colum or diagonal if enough elements remain to reach 4 (count + remaining elements < MIN_DIAG) and skip to next if no chance -> 11s
* scan rows from top to bottom -> 10s 
* replace `std::vector<char> board`  for `bool bool_board[]` -> no improvement. Why?
* precompute the `NCOLS * i + j` for the diagonals -> 9s
* precompute the `NCOLS * i + j` for the horizontals and verticals diagonals -> 15s!! Why?? REVERTED
* refactor `Evaluate` to 1) check for `Connect4::X` and `Connect::O` in the same loop instead of calling sequentially `check_for_win()` for for `Connect4::X` and then `Connect::O` and also 2) in columns, stop exploring when an Connect4::EMPTY is found -> 6s!

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