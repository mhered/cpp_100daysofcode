#link: https://stackoverflow.com/questions/4632322/finding-all-possible-combinations-of-numbers-to-reach-a-given-sum?rq=2



# CombinationSums

Given an integer number `target`and a list of int `numbers` return all the possible combinations of the elements in `numbers`, which sum is equal to `target`, allowing repetition but not considering the order. 

````c++
std::vector<std::vector<int>> CombinationsThatSum(int target, 
                                                  std::vector<int> numbers, 
                                                  bool verbose = false)
````

Sample usage: 

```
CombinationsThatSum(5, {1, 2, 3, 4, 5}, true)
5 = 1 + 1 + 1 + 1 + 1 
5 = 1 + 1 + 1 + 2 
5 = 1 + 1 + 3 
5 = 1 + 2 + 2 
5 = 1 + 4 
5 = 2 + 3 
5 = 5 
Found 7 combinations of { 1, 2, 3, 4, 5 } that sum 5
```

What is the motivation? Yesterday I started working in the project PitStop, which tries to determine the optimal F1 race strategy regarding pit stops and refuelling. The goal is to determine how many pit stops should a F1 car make during a race and when. There are two considerations: pit stops take time, but on the other hand loading the car with too much fuel will slow it down - hence it may be better to load less fuel and make more pit stops.

While analyzing this problem I realized I needed a way to explore all possible race strategies i.e. for a race with N laps I needed to consider all possible combinations of stints of 1,2,3,...,N laps each in which the race could be split, with pitstops in between. 

Note this is a variation of the [CoinChange](https://github.com/mhered/cpp_100daysofcode/tree/main/code/Day010_05-04-23/CoinChange) problem from Day010. On that occasion we only needed the number of combinations, and now we need the function to return the actual list of all combinations possible. 

The solution is based on what I learnt about [Recursion](https://github.com/mhered/cpp_100daysofcode/tree/main/code/Day023_18-04-23/Recursion) on Day 023 and also on the StackOverflow Q&A provided in the link.

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