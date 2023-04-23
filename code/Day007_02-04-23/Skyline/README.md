#link: https://codechalleng.es/bites/332/

# Bite 332. Searching for an apartment               

 Bill is looking for a new apartment with good view, away from the crowded city. 

He has been working with some agents and has piles of data of all  sorts of buildings. However he is too busy to go through the data. Can  you help him by designing a fast algorithm to search for the best  possible apartment(s) with the desired view?

The requirement: *find an apartment with either sun set or sun rise view*. Given an list of buildings in height (floors), and desired view, either East (sun rise) or West (sun set), you have to find all the candidate  buildings and return them by their position (index) in the passed in building `std::vector<int> skyline`  

`std::vector<int> search_apartment (std::vector<int> skyline, char direction)`

 ## An example

Here is a visual representation when `skyline` input argument is `{3, 5, 4, 4, 7, 1, 3, 2}` (each `int` represents the height of the building and note that the buildings are in one line with no gaps in between):

 ```
         W                 E
 
                   _        
                  |_|       
             _    |_|       
            |_|_ _|_|       
           _|_|_|_|_|  _    
          |_|_|_|_|_| |_|_  
          |_|_|_|_|_|_|_|_| 
         _|_|_|_|_|_|_|_|_|_
           3 5 4 4 7 1 3 2 
 
 W         1 1 0 0 1 0 0 0 
 E         0 0 0 0 1 0 1 1      
 ```

Expected output for this buildings input list:

* Given direction West (`'W'`) -> the function returns `{0, 1, 4}` = indices of buildings that can see the *sun set*.

* Given direction East (`'E'`) -> the function returns `{4, 6, 7}` = indices of buildings that can see the *sun rise*.

 ## Examples

 ```c++
 search_apartment({3, 5, 4, 4, 7, 1, 3, 2}, 'W'))  # {0, 1, 4}
 search_apartment({3, 5, 4, 4, 7, 1, 3, 2}, 'E'))  # {4, 6, 7}
 search_apartment({1, 1, 1, 1, 1, 2}, 'W')  # {0, 5}
 search_apartment({1, 1, 1, 1, 1, 2}, 'E'))  # {5}
 
 search_apartment({3, 5, 4, 3, 3, 1}, 'W') # {0, 1}                 
 search_apartment({3, 5, 4, 3, 3, 1}, 'E') # {1, 2, 4, 5}
 search_apartment({1, 1, 1, 1, 1}, 'W') # {0}
 search_apartment({2, 1, 1, 1, 1}, 'E') # {0, 4}
 ```

## Bonus!

Write the function that generates the visual representation above

`void plot_skyline (std::vector<int> skyline)`

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