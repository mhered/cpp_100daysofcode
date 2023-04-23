#link: https://www.codechef.com/problems/REFUELS?tab=statement

# Racing Refuels

In racing, you refuel your car in the pitstops, and it’s very important to carefully plan pit stops.

1 unit of fuel is enough for exactly 1 lap. At the beginning of each  lap, the number of units of fuel in your car must be a positive integer  that doesn't exceed the tank capacity **N**, and it will decrease by 1 during a lap. After each lap, you can spend **P** seconds to visit a pit stop and  refuel your car (add some fuel). It's allowed to start a lap with only 1 unit of fuel and thus finish it  with 0 units — but you have to visit a pit stop right after that, unless it was the last lap of the race. You can start the race with any allowed (positive integer that doesn't  exceed **N**) number of units of fuel.

The more fuel your car contains, the slower it is. If you start a lap with x units of fuel, you will finish this lap in **t**x seconds. You can assume that **t**x ≤ **t**x+1.

There are **Q** independent races, each described by two integers **K** and **P**, denoting the number of laps and the time needed to visit a pit stop in  that race (let's say that in some races the pit stop crew is lazy and  works slower). For each race, find the minimum possible number of seconds in which you  can finish that race.

### Input

The first line of the input contains two integers **N** and **Q**, denoting the tank capacity and the number of races respectively.

The second line contains **N** integers **t_1**, **t_2**, ..., **t_N**, where **t_x** denotes the time needed to finish a lap if you start it with x units of fuel.

Each of the next **Q** lines contains two integers **K** and **P**, denoting the number of laps and the number of seconds needed to visit a pit stop in one race.

### Output

For each of the **Q** races, in a separate line, print a single integer — the minimum possible number of seconds needed to finish the race. Please note the unusual constraint about the answer.

### Constraints

- 1 ≤ **N**, **Q** ≤ 300,000
- 1 ≤ **K**, **P**, **t**_i ≤ 10^13
- **t_i** ≤ **t_i+1**
- It's guaranteed that the answer fits in the signed 64-bit type.

### Example

```
Input:
3 14
5 7 20
5 60
5 3
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
7 60
999999999 60
1000 123456789123

Output:
104
35
5
5
5
11
12
12
17
19
20
176
30666666576
41111110788607

```



### Explanation

Your car fits up to **N** = 3 units of fuel. Let's take a look at the first two races.

**Race #1.**  This race consists of **K** = 5 laps and you need **P** = 60 seconds to visit a pit stop. One optimal scenario is:

1. Start the race with 3 units of fuel.
2. Spend **t**3 = 20 seconds on the first lap. Now you have 2 units of fuel.
3. Spend **t**2 = 7 seconds on the second lap. Now you have 1 unit of fuel.
4. Spend **t**1 = 5 seconds on the third lap. Now you have 0 units of fuel.
5. Spend 60 seconds to visit a pit stop. Add 2 units of fuel there.
6. Spend **t**2 = 7 seconds on the 4-th lap.
7. Spend **t**1 = 5 seconds on the 5-th lap.

This total time is 20 + 7 + 5 + 60 + 7 + 5 = 104 seconds and it turns out to be the optimal answer.

**Race #2.**  This race also consists of **K** = 5 laps, but this time you need only **P** = 3 seconds to visit a pit stop, so it might be better to visit a pit stop more often.

## My notes

Steps to solve it:

* time for Race with K laps = K/N times (the optimum for N laps + pitstop) + optimum for K%N laps
* need to solve optimum for 1...N laps
* optimum for J (J<N) laps: min (eval(combi(J, J)))
* eval = sum (lapTimes[combi[i]] +pitstop *(len(combi)-1) )
* combi(A,B): all the possible unordered combinations of numbers from 1 to B that add to A (B<=A)

* Finding all possible combinations of numbers to reach a given sum: https://stackoverflow.com/questions/4632322/finding-all-possible-combinations-of-numbers-to-reach-a-given-sum

## Discussion of my results

```
########################################
Race #1: best time is 104s
Race #2: best time is 35s
Race #3: best time is 5s
Race #4: best time is 5s
Race #5: best time is 5s
Race #6: best time is 11s
Race #7: best time is 12s
Race #8: best time is 12s
Race #9: best time is 17s
Race #10: best time is 19s
Race #11: best time is 20s
Race #12: best time is 189s
Race #13: best time is 30666666576s
Race #14: best time is 41111110788620s
```

* Note there are discrepancies between the solution provided and the result of my code:
  * In Race #12 (189s my code vs. 176s from Codechef). I checked Race #12 manually and I confirm my result: 2 stints of 3 laps + 1 final stint of lap =  20 + 7 + 5 + 60+ 20 + 7 + 5 + 60+5 = 189s
  * In Race #14 (41111110788620s my code vs. 41111110788607 from Codechef). I checked Race #14 manually and I confirm my result: 333 stints of 3 laps + 1 final stint of lap =  333* (20 + 7 + 5 + 123456789123)  + 5 = 41111110788620s

* Nevertheless I realize there is overengineering and a flaw in my code. 
  * It was not necessary to use recursion to explore weird combinations of stints, it was enough to determine the most efficient stint `K1` ( be it`1` lap, `2` laps, `3` laps ... that is both < `tankCapacity`and <`numLaps`) 
  * then the best strategy is simply to repeat this most efficient stint of `K1` laps for `K1/numLaps` times 
  * then find the most efficient way to complete the remaining `K1%numLaps` of the race: the most efficient stint `K2`( be it`1` lap, `2` laps, `3` laps ... that is both < `tankCapacity` and <`K1%numLaps`) 
  * and repeat until there is no remainder

#tags: 

- [ ] basics
- [x] algorithms
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