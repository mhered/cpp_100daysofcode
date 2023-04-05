#link: https://edabit.com/challenge/TykFvvciNeGvRDbsS



## Coins Combinations

Given an amount of **money** and an array of **coins denominations**, create a function that counts how many different ways you can make change with the given money.

### Examples

```
coinsCombinations(4, [1, 2]) ➞ 3
// 1+1+1+1 = 4
// 1+1+2 = 4
// 2+2 = 4

coinsCombinations(10, [5, 2, 3]) ➞ 4

coinsCombinations(11, [5, 7]) ➞ 0
```

### Notes

- Order of coins does not matter (i.e. 1+1+2 == 2+1+1).
- You have an infinite amount of coins.

### Bonus
Implement the three different approaches described here: https://www.codingninjas.com/codestudio/library/coin-change-combination-problem and time them (using e.g. this approach https://www.geeksforgeeks.org/how-to-measure-elapsed-time-in-cpp/):

```
target = 11, coins = {1, 2, 5}
Brute force: 11 combinations (Elapsed Time: 8 microseconds)
Top Down dp: 11 combinations (Elapsed Time: 10 microseconds)
Bottom Up dp: 11 combinations (Elapsed Time: 2 microseconds)

target = 37, coins = {1, 2, 5, 10}
Brute force: 160 combinations (Elapsed Time: 191 microseconds)
Top Down dp: 160 combinations (Elapsed Time: 32 microseconds)
Bottom Up dp: 160 combinations (Elapsed Time: 6 microseconds)

target =317, coins =  {1, 2, 5, 10, 50}
Brute force: 125146 combinations (Elapsed Time: 904134 microseconds)
Top Down dp: 125146 combinations (Elapsed Time: 302 microseconds)
Bottom Up dp: 125146 combinations (Elapsed Time: 27 microseconds)
```
