#link: https://www.youtube.com/watch?v=NdF1QDTRkck

# 8 Queens

* Goal: place N Queens in a N by N chess board so none are threatened.
* Queen can attack in any straight line (horizontally, vertically, diagonally)
* Cast in terms of decision
  * Each call will make one decision and recur on rest
  * How many decisions do you have to make?
  * What options do you have for each? 

Implement the 8 Queens Backtracking algorithm (with a GUI, maybe?) as described in Lecture 10 by Julie Zelenski for  the Programming Abstractions Course (CS106B) in the Stanford Computer Science Department (ref. the project [Recursion](https://github.com/mhered/cpp_100daysofcode/tree/main/code/Day023_18-04-23/Recursion) from Day023)

Start with the recursive `Solve()` function below, and implement all the helpers: a`Grid` class with its methods, `PlaceQueen()`, `RemoveQueen()`, `IsSafe()` etc.

```c++
// 8 Queens Backtracking Algorithm
bool Solve(Grid<bool> &board, int col)
{
    if (col >= board.numCols()) // base case
        return true;
    for (int rowToTry = 0; rowToTry < board.numRows(); rowToTry++)
    {
        // for all choices available
        if (IsSafe(board, rowToTry, col))
        {
            // make the choice
            PlaceQueen(board, rowToTry, col);
            // try to solve from here, if works out, you're done
            if (Solve(board, col + 1))
                return true;
            // if not, unmake the choice and keep looking
            RemoveQueen(board, rowToTry, col);
        }
    }
    // tried all choices, no solution found
    return false;
}
```


# Tags

#tags: 

- [ ] basics
- [x] algorithms
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
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV