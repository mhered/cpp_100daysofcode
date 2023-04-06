#link: https://www.tutorialspoint.com/sudoku-solver-in-cplusplus

# Sudoku solver

Sudoku is a 9 x 9 number grid, and the whole grid are also divided into 3 x 3 boxes There are some rules to solve the Sudoku.

- We have to use digits 1 to 9 for solving this problem.
- One digit cannot be repeated in one row, one column or in one 3 x 3 box.

We will try to solve Sudoku problem using a backtracking algorithm. When some  cell is filled with a digit, it checks whether it is valid or not. When it is not valid, it checks for other numbers. If all numbers are checked from 1-9, and no valid digit found to place, it backtracks to previous option.

So if the input is:

```
{3, 0, 6, 5, 0, 8, 4, 0, 0},
{5, 2, 0, 0, 0, 0, 0, 0, 0},
{0, 8, 7, 0, 0, 0, 0, 3, 1},
{0, 0, 3, 0, 1, 0, 0, 8, 0},
{9, 0, 0, 8, 6, 3, 0, 0, 5},
{0, 5, 0, 0, 9, 0, 6, 0, 0},
{1, 3, 0, 0, 0, 0, 2, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 7, 4},
{0, 0, 5, 2, 0, 6, 3, 0, 0}
```

The expected output will be:

```
3 1 6 | 5 7 8 | 4 9 2
5 2 9 | 1 3 4 | 7 6 8
4 8 7 | 6 2 9 | 5 3 1
----------------------
2 6 3 | 4 1 5 | 9 8 7
9 7 4 | 8 6 3 | 1 2 5
8 5 1 | 7 9 2 | 6 4 3
----------------------
1 3 8 | 9 4 7 | 2 5 6
6 9 2 | 3 5 1 | 8 7 4
7 4 5 | 2 8 6 | 3 1 9
```

## Bonus

* Encapsulate on a `class Sudoku`

* Some examples to practice: https://sandiway.arizona.edu/sudoku/examples.html
