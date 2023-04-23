#link: https://edabit.com/challenge/Ccoo3SHJwv4qCLKQb

## Bonus

Write two crude helper functions that take the edabit tests and translates them to gtests and to simple cout statements to check in the `main()`.

i.e. starting with a text file that contains this:

```
Describe(cars_){
It(test1){Assert::That(cars(37, 15, 20), Equals(9));}
It(test2){Assert::That(cars(72, 7, 21), Equals(7));}
It(test3){Assert::That(cars(9, 44, 34), Equals(2));}
It(test4){Assert::That(cars(50, 38, 7), Equals(3));}
It(test5){Assert::That(cars(68, 9, 44), Equals(9));}
It(test6){Assert::That(cars(3, 29, 54), Equals(0));}
It(test7){Assert::That(cars(28, 34, 80), Equals(7));}
It(test8){Assert::That(cars(88, 50, 83), Equals(22));}
It(test9){Assert::That(cars(66, 18, 21), Equals(10));}
It(test10){Assert::That(cars(97, 6, 10), Equals(5));}
It(test11){Assert::That(cars(921, 310, 350), Equals(175));}
It(test12){Assert::That(cars(736, 430, 851), Equals(184));}
It(test13){Assert::That(cars(405, 379, 740), Equals(101));}
It(test14){Assert::That(cars(593, 78, 389), Equals(78));}
It(test15){Assert::That(cars(875, 370, 675), Equals(218));}
It(test16){Assert::That(cars(863, 274, 203), Equals(101));}
It(test17){Assert::That(cars(959, 331, 537), Equals(239));}
It(test18){Assert::That(cars(416, 340, 551), Equals(104));}
It(test19){Assert::That(cars(692, 348, 543), Equals(173));}
It(test20){Assert::That(cars(527, 412, 951), Equals(131));}
};
```

Make a function `bool formatAsGtest(std::string filename)` that outputs this:

```c++
INSTANTIATE_TEST_CASE_P(Default, CarsTest,
  testing::Values(
      Sample({ 37, 15, 20 }, 9),
      Sample({ 72, 7, 21 }, 7),
      Sample({ 9, 44, 34 }, 2),
      Sample({ 50, 38, 7 }, 3),
      Sample({ 68, 9, 44 }, 9),
      Sample({ 3, 29, 54 }, 0),
      Sample({ 28, 34, 80 }, 7),
      Sample({ 88, 50, 83 }, 22),
      Sample({ 66, 18, 21 }, 10),
      Sample({ 97, 6, 10 }, 5),
      Sample({ 921, 310, 350 }, 175),
      Sample({ 736, 430, 851 }, 184),
      Sample({ 405, 379, 740 }, 101),
      Sample({ 593, 78, 389 }, 78),
      Sample({ 875, 370, 675 }, 218),
      Sample({ 863, 274, 203 }, 101),
      Sample({ 959, 331, 537 }, 239),
      Sample({ 416, 340, 551 }, 104),
      Sample({ 692, 348, 543 }, 173),
      Sample({ 527, 412, 951 }, 131),
      ));
```

And a function `bool formatAsCout(std::string filename)` that outputs this:

```c++
std::cout << cars(37, 15, 20) << std::endl; // 9
std::cout << cars(72, 7, 21) << std::endl; // 7
std::cout << cars(9, 44, 34) << std::endl; // 2
std::cout << cars(50, 38, 7) << std::endl; // 3
std::cout << cars(68, 9, 44) << std::endl; // 9
std::cout << cars(3, 29, 54) << std::endl; // 0
std::cout << cars(28, 34, 80) << std::endl; // 7
std::cout << cars(88, 50, 83) << std::endl; // 22
std::cout << cars(66, 18, 21) << std::endl; // 10
std::cout << cars(97, 6, 10) << std::endl; // 5
std::cout << cars(921, 310, 350) << std::endl; // 175
std::cout << cars(736, 430, 851) << std::endl; // 184
std::cout << cars(405, 379, 740) << std::endl; // 101
std::cout << cars(593, 78, 389) << std::endl; // 78
std::cout << cars(875, 370, 675) << std::endl; // 218
std::cout << cars(863, 274, 203) << std::endl; // 101
std::cout << cars(959, 331, 537) << std::endl; // 239
std::cout << cars(416, 340, 551) << std::endl; // 104
std::cout << cars(692, 348, 543) << std::endl; // 173
std::cout << cars(527, 412, 951) << std::endl; // 131
```


# Tags

#tags: 
- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [x] strings: regex
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
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV