#link: https://www.youtube.com/watch?v=NdF1QDTRkck



# Recursion

Explore recursion with Lecture 10 by Julie Zelenski for the Programming Abstractions Course (CS106B) in the Stanford Computer Science Department. 

4 examples of recursive algorithms are discussed in this lesson:

* Find all permutations:  `void ListPermutations(std::string s)`

* Find all subsets (unordered):     `void ListSubsets(std::string s)`
* Backtracking: Find Anagrams `bool IsAnagram(std::string s, Lexicon &lex)`
* Bracktracking: 8 Queens

## Two ideas for future challenges

- [ ] Implement a better Lexicon. I did a really crude implementation using an ordered vector and it grinds to a halt when looking for anagrams of a 9-letter word (and this with very small lexicon of 10,000 words). Strive to make something that works with the ~500k words lexicon linked below!
- [ ] Implement the 8 Queens algorithm (with a GUI, maybe) 

## Resources

* Download course material for non-Stanford students: https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1136/

* a list of the 10,000 most common English words in order of frequency, as determined by n-gram frequency analysis of the Google's Trillion Word Corpus: https://github.com/first20hours/google-10000-english/blob/master/20k.txt
* For serious fun, a text file containing 479k English words (4Mb): https://github.com/dwyl/english-words
* Lexicon ADT case study: a discussion on best data structures to store a lexicon: https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1212/lectures/28-lexicon/slides

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