#link: https://www.learncpp.com/cpp-tutorial/basic-file-io/

# Basic file I/O

Basic exercise defined by myself to practice basic text file input/output as described in the tutorial by www.learncpp.com linked above.

Create 3 functions:

`bool writeTextToFile(std::string filename, std::vector<std::string> lines)` writes a vector of strings as lines to a text file `filename`. Returns `true` if successful `false` otherwise.

`bool appendTextToFile(std::string filename, std::vector<std::string> lines)`

appends a vector of strings as lines to the end of a text file `filename`. Returns `true` if successful `false` otherwise. 

`bool readTextFromFile(std::string filename)`

reads lines from a text file `filename` and prints them out separated by `\n`. Returns `true` if successful `false` otherwise. 
