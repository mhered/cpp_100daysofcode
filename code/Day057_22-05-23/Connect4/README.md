#link:

# Connect4
Building on the code written to play Tic Tac Toe (see project [WarGames](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day020_15-04-23/WarGames) write a computer player for Connect4.

Instructions:

* standard board size is 6x7
```
_______________
|_|_|_|_|_|_|_|
|O|_|_|_|_|_|_|
|X|_|_|_|_|O|_|
|X|O|X|_|_|O|_|
|X|X|X|O|X|O|_|
|O|O|O|X|X|O|O|
 1 2 3 4 5 6 7 

```
* players take turns, select in which column to drop their token, which falls to the bottom of the column (the lowest row that is empty)
* in their turn, offer the player to select column 
* in the turn of the computer, use the minimax algorithm to calculate the best move

## Notes
* I managed to make it work - and it is actually hard to beat - in a small board of size 4x4, although it takes a long time to calculate the moves, especially the first ones
* For larger boards, calculation takes so long even starting with a board half way through the game that it is not viable...

How can I profile and improve performance?

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
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV