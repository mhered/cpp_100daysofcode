# cpp_100daysofcode

My log for the #100DaysOfCode challenge with C++

* `code` folder contains one folder per day of the challenge. Inside each folder there is one subfolder per challenge taken in the day. 
* `utils` folder contains some helper python functions and template files used to initialize the folder structure and compose the progress tweets 
  * `init.py` creates the folder structure and template `main.cpp` and `README.md` files

  * `tweet.py` 
    * reads the title of each challenge from the subfolder names inside the day folder that matches the current date 
    * inside each challenge subfolder it searches the file `README.md` for the line that starts with `#link:` to extract the link to each challenge
    * composes a progress tweet to add to the thread and appends it to this README.md
* `todo` folder contains the pipeline of future projects

## C++ learning resources

* https://omkarghotekar.medium.com/100-days-of-code-complete-guide-w-resources-beginner-aae12a8af926 - a guide with resources to approach 100 days of code challenges 

* https://edabit.com/challenges - resource with bite-sized exercises in several languages
* https://www.learncpp.com/ - free resource to learn C++ seems, quite detailed and frequently updated, with example code: OOP, exceptions, STL etc

* https://www.geeksforgeeks.org/c-plus-plus/ -another track including also puzzles, competitive programming etc

* https://en.cppreference.com/w/cpp/links/libs - list of libraries

* [A curated list of (awesome) header-only C++ libraries](https://github.com/p-ranav/awesome-hpp) - more libraries

* https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list - The Definitive C++ Book Guide and List
* https://app.theconstructsim.com/Course/59/ - C++ for Robotics

---


 ## 27-03-23

Day 1 #100DaysOfCode #cpp progress: today I worked on the following challenges: Burrrrrrrp https://edabit.com/challenge/vxpP4nnDhRr2Yc3Lo and PowerCalculator https://edabit.com/challenge/a2D3cva6PKrHyqdXC
 ## 28-03-23

Day 2: #100DaysOfCode in #Cpp progress - today I worked on the challenges AddNumbers https://edabit.com/challenge/XDx6JoaumAimRHgEt, FizzBuzz https://edabit.com/challenge/Ao7fJta5kEMNHSYEa and RockPaperScissors https://edabit.com/challenge/MYqnQ3DpPZi9di4iW
 ## 29-03-23

Day 3: #100DaysOfCode in #Cpp progress - today I worked on the challenges ProductOfOthers https://edabit.com/challenge/aQnur99HSdYbyypLd, SecondLargest https://edabit.com/challenge/pp2DgYDhyhoaXbqQw and CamelToSnake https://edabit.com/challenge/mEEsMKznTCq25PWvD
 ## 30-03-23

Day 4: #100DaysOfCode in #Cpp progress - today I played with basic file input/output FileIO https://www.learncpp.com/cpp-tutorial/basic-file-io/ and worked on the challenges Transpose https://edabit.com/challenge/4KaoDvxaFSmf38bPQ and Sudoku https://edabit.com/challenge/JevwpdjTnoJT5t29F
 ## 31-03-23

Day 5: #100DaysOfCode in #Cpp progress - today I practiced reading from CSV, XML and JSON files and loading the data into a vector of custom objects. In ReadDataFiles https://github.com/mhered/cpp_100daysofcode/tree/main/code/Day005_31-03-23/ReadDataFiles I used #mockaroo #json/nlohmann and #rapidxml but no animals were harmed
 ## 01-04-23

Day 6: #100DaysOfCode in #Cpp progress - today I worked on the challenge DaysUntil2021 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day006_01-04-23/DaysUntil2021 (see https://edabit.com/challenge/Fmo9fFHfZw3u88QLZ) and learned about dates in C++
 ## 02-04-23

Day 7: #100DaysOfCode in #Cpp progress - today I adapted @pybites #Python Bite 332 - Searching for an apartment https://codechalleng.es/bites/332/ to C++ and added some extra fun formatting strings to build the visual representation of the Skyline https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day007_02-04-23/Skyline 
 ## 03-04-23

Day 8: #100DaysOfCode in #Cpp progress - today I worked on the challenges CountingBoomerangs https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day008_03-04-23/CountingBoomerangs ( see https://edabit.com/challenge/oL3q28iPjuo5BWHu9) and TicTacToe https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day008_03-04-23/TicTacToe ( see https://edabit.com/challenge/rscwis53jKokoKRYo)
 ## 04-04-23

Day 9: #100DaysOfCode in #Cpp progress - today I worked on the challenge MakingBoxes https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day009_04-04-23/MakingBoxes (see https://edabit.com/challenge/yHeTBuJ6LDw3nhA7k) 
 ## 05-04-23

Day 10: #100DaysOfCode in #Cpp progress - today I practiced recursive algorithms and timing code execution while working on the challenge CoinChange https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day010_05-04-23/CoinChange (see https://edabit.com/challenge/TykFvvciNeGvRDbsS)
 ## 06-04-23

Day 11: #100DaysOfCode in #Cpp progress - more fun with recursion today building a SudokuSolver https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day011_06-04-23/SudokuSolver (based on https://www.tutorialspoint.com/sudoku-solver-in-cplusplus)
 ## 07-04-23

Day 12: #100DaysOfCode in #Cpp progress - today I learned in this tutorial https://www.youtube.com/watch?v=FOIbK4bJKS8 about wxWidgets to build cross-platform GUIs with C++ and applied it to implement a BasicGUI https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day012_07-04-23/BasicGUI and the game MineSweeper https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day012_07-04-23/MineSweeper
 ## 08-04-23

Day 13: #100DaysOfCode in #Cpp progress - today life took over, but I still found time to keep my fingers warm working on an easy one: Password https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day013_08-04-23/Password (see https://edabit.com/challenge/2MAr9P4TTGooXS8Xa)
 ## 09-04-23

Day 14: #100DaysOfCode in #Cpp progress - today I worked on the challenge EasterDates https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day014_09-04-23/EasterDates (see https://edabit.com/challenge/QMQWmSbvrvTaBFPN6)
 ## 10-04-23

Day 15: #100DaysOfCode in #Cpp progress - today I explored the capabilities of ChatGPT. I asked it to solve a programming exercise, comment the code, help me install Google Test framework and write unit tests, then translate the code to python and refactor it to make it more pythonic. The game-changing result in TestDriveChatGPT https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day015_10-04-23/TestDriveChatGPT (based on https://www.youtube.com/watch?v=QG3IgW-FBRg).
 ## 11-04-23

Day 16: #100DaysOfCode in #Cpp progress - after the yesterday's gentle introduction by ChatGPT, today I  dived into the framework GoogleTest https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day016_11-04-23/GoogleTest (see https://www.youtube.com/watch?v=16FI1-d2P4E) and applied it to a previous challenge: TestEasterDates https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day016_11-04-23/TestEasterDates 
 ## 12-04-23

Day 17: #100DaysOfCode in #Cpp progress - today I worked on the challenges Median https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day017_12-04-23/Median (see https://edabit.com/challenge/iuXEXDGarZ9MxSyZ8) and TestingMedian https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day017_12-04-23/TestingMedian 
 ## 13-04-23

Day 18: #100DaysOfCode in #Cpp progress - a very simple one today: ToyCars https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day018_13-04-23/ToyCars (see https://edabit.com/challenge/Ccoo3SHJwv4qCLKQb)
 ## 14-04-23

Day 19: #100DaysOfCode in #Cpp progress - today I built myself a simple tool to translate edabit tests. It's crude, but it works, and it will save some typing: TestParsing https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day019_14-04-23/TestParsing
 ## 15-04-23

Day 20: #100DaysOfCode in #Cpp progress - today I wrote a TicTacToe computer player inspired by the 80's cult classic WarGames https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day020_15-04-23/WarGames (see https://www.geeksforgeeks.org/finding-optimal-move-in-tic-tac-toe-using-minimax-algorithm-in-game-theory/)
 ## 16-04-23

Day 21: #100DaysOfCode in #Cpp progress - today I added a GUI based on the Minesweeper one from Day012 to yesterday's TicTacToe engine, and the result is: TicTacToeGUI https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day021_16-04-23/TicTacToeGUI #wxWidgets 
 ## 17-04-23

Day 22: #100DaysOfCode in #Cpp progress - today I had fun with LEDs: Arduino101 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day022_17-04-23/Arduino101 and 3Blinks https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day022_17-04-23/3Blinks. The C++ code was trivial, but I explored a world of great tools related to Arduino: IDE, vscode extension, circuit-diagram, fritzing...
 ## 18-04-23

Day 23: #100DaysOfCode in #Cpp progress - today I practiced Recursion https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day023_18-04-23/Recursion with this great Stanford Lecture by Julie Zelenski https://www.youtube.com/watch?v=NdF1QDTRkck. Oh, and on the side I made a really inefficient Lexicon https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day023_18-04-23/Lexicon
 ## 19-04-23

Day 24: #100DaysOfCode in #Cpp progress - yesterday I didn't complete the challenge that I set out to do, but I made some partial progress: CombinationSums https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day024_19-04-23/CombinationSums (see https://stackoverflow.com/questions/4632322/finding-all-possible-combinations-of-numbers-to-reach-a-given-sum?rq=2) #recursion
 ## 20-04-23

Day 25: #100DaysOfCode in #Cpp progress - today I worked on the project PitStops https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day025_20-04-23/PitStops (see https://www.codechef.com/problems/REFUELS?tab=statement)
 ## 21-04-23

Day 26: #100DaysOfCode in #Cpp progress - today I looked around for C++ libraries to plot graphs and I found https://sciplot.github.io/: PlotGraph https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day026_21-04-23/PlotGraph
 ## 22-04-23

Day 27: #100DaysOfCode in #Cpp progress - today I played with the excellent Matplot++ library: 2D and 3D plots, images, maps, heatmaps, word clouds... MorePlots https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day027_22-04-23/MorePlots (see https://github.com/alandefreitas/matplotplusplus)
 ## 23-04-23

Day 28: #100DaysOfCode in #Cpp progress - today added tags to all my projects and built a simple app to keep track of the progress. A nice excuse to practice #filesystem #counters #parsing strings #Matplotplusplus etc: Tags https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day028_23-04-23/Tags 
 ## 24-04-23

Day 29: #100DaysOfCode in #Cpp progress - today I worked on the project 8Queens https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day029_24-04-23/8Queens (see https://www.youtube.com/watch?v=NdF1QDTRkck)
 ## 25-04-23

Day 30: #100DaysOfCode in #Cpp progress - today I worked on the project ToDoListCLI https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day030_25-04-23/ToDoListCLI (see https://www.youtube.com/watch?v=1DR-Sj-RLzQ)
 ## 26-04-23

Day 31: #100DaysOfCode in #Cpp progress - today I started a command line app that takes a string and transmits it in Morse code by flashing an Arduino-controlled LED. I did 2 parts out of 3 today: Morse1 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day031_26-04-23/Morse1 & Morse2 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day031_26-04-23/Morse2, more tomorrow!
 ## 27-04-23

Day 32: #100DaysOfCode in #Cpp progress - today I built the serial interface to get Arduino to transmit Morse code messages: Morse3 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day032_27-04-23/Morse3 (see https://forum.arduino.cc/t/serial-input-basics-updated/382007)
 ## 28-04-23

Day 33: #100DaysOfCode in #Cpp progress - today I worked on the project ProgressBar https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day033_28-04-23/ProgressBar (see https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf/14539953#14539953)
 ## 29-04-23

Day 34: #100DaysOfCode in #Cpp progress - today I learnt to exchange data between C++ and Arduino through serial using the #libSerial library: ArduinoSerial https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day034_29-04-23/ArduinoSerial (see https://libserial.readthedocs.io/en/latest/tutorial.html)
 ## 30-04-23

Day 35: #100DaysOfCode in #Cpp progress - today was an easy one: CumSum https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day035_30-04-23/CumSum 
 ## 01-05-23

Day 36: #100DaysOfCode in #Cpp progress - today I worked with #Matplotcplusplus to improve the progress report: BetterTags https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day036_01-05-23/BetterTags
 ## 02-05-23

Day 37: #100DaysOfCode in #Cpp progress - today I worked on the project PolarHistogram https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day037_02-05-23/PolarHistogram (more #Matplotplusplus)
 ## 03-05-23

Day 38: #100DaysOfCode in #Cpp progress - today I worked on the project OpenCVIntro https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day038_03-05-23/OpenCVIntro (see https://medium.com/analytics-vidhya/how-to-install-opencv-for-visual-studio-code-using-ubuntu-os-9398b2f32d53)
 ## 04-05-23

Day 39: #100DaysOfCode in #Cpp progress - today I celebrated #StarWarsday day with a silly one: StarWarsNameGenerator https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day039_04-05-23/StarWarsNameGenerator
 ## 05-05-23

Day 40: #100DaysOfCode in #Cpp progress - today I practiced real-time video processing with the #OpenCV library - resizing, filtering annotation, and more: MoreOpenCV https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day040_05-05-23/MoreOpenCV (see https://opencv-srf.com/p/opencv-lessons.html)
 ## 06-05-23

Day 41: #100DaysOfCode in #Cpp progress - more #OpenCV today  - I worked on the project DuckieTracker https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day041_06-05-23/DuckieTracker (see https://www.opencv-srf.com/p/opencv-lessons.html)
 ## 07-05-23

Day 42: #100DaysOfCode in #Cpp progress - today I worked on the project LargestIsland https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day042_07-05-23/LargestIsland (see https://edabit.com/challenge/EmEaT9K4wKe3g6QH3)
 ## 08-05-23

Day 43: #100DaysOfCode in #Cpp progress - today I worked on the project Exceptions https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day043_08-05-23/Exceptions (see https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/)
 ## 09-05-23

Day 44: #100DaysOfCode in #Cpp progress - today I worked on the project FaceDetector https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day044_09-05-23/FaceDetector (see https://medium.com/analytics-vidhya/building-a-face-detector-with-opencv-in-c-8814cd374ea1) #OpenCV #AI Credit sample video: Thirdman https://www.pexels.com/video/woman-taking-selfie-with-friends-8020479/
 ## 10-05-23

Day 45: #100DaysOfCode in #Cpp progress - today I worked on the project Pedestrians https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day045_10-05-23/Pedestrians (see https://youtube.com/watch?v=5SzNuPSaISM), detecting movement via image subtraction and processing #OpenCV
 ## 11-05-23

Day 46: #100DaysOfCode in #Cpp progress - today I worked on the project PredictMouseMove https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day046_11-05-23/PredictMouseMove (see https://www.youtube.com/watch?v=Tbcn7XTXunA&t=0s)
 ## 12-05-23

Day 47: #100DaysOfCode in #Cpp progress - today I worked on the project Scrabble https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day047_12-05-23/Scrabble (see https://edabit.com/challenge/7k2mo5kHBuMJGdP5f)
 ## 13-05-23

Day 48: #100DaysOfCode in #Cpp progress - today I worked on the project MultipleObjectTracking https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day048_13-05-23/MultipleObjectTracking (see https://www.youtube.com/watch?v=A4UDOAOTRdw)
 ## 14-05-23

Day 49: #100DaysOfCode in #Cpp progress - today I worked on the project Video2ASCII https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day049_14-05-23/Video2ASCII (see https://thecodingtrain.com/challenges/166-image-to-ascii)

 ## 15-05-23

Day 50: #100DaysOfCode in #Cpp progress - today I worked on the project CountingCars https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day050_15-05-23/CountingCars (see https://www.youtube.com/watch?v=Y3ac5rFMNZ0&t=0s)
 ## 16-05-23

Day 51: #100DaysOfCode in #Cpp progress - today I worked on the project Javelin https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day051_16-05-23/Javelin (see https://edabit.com/challenge/cS48jymeLrkjhDZ8x)
 ## 17-05-23

Day 52: #100DaysOfCode in #Cpp progress - today I worked on the project SQLite https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day052_17-05-23/SQLite (see https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/)
 ## 18-05-23

Day 53: #100DaysOfCode in #Cpp progress - today I played with  a C++ library to control my drone: Tello https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day053_18-05-23/Tello (see https://github.com/herrnamenlos123/tello). I couldn't finish the last of 3 demos I had planned, but it is late and the drone battery is dead. Let's call it a day.
 ## 19-05-23

Day 54: #100DaysOfCode in #Cpp progress - today I worked on the projects Keypress https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day054_19-05-23/Keypress (see https://stackoverflow.com/a/63708756/15472802) and Snakes https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day054_19-05-23/Snakes (see https://stackoverflow.com/questions/61479597/how-can-i-use-kbhit-and-getch-on-linux-c)
 ## 20-05-23

Day 55: #100DaysOfCode in #Cpp progress - today I worked on the project Rubik https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day055_20-05-23/Rubik (see https://live.worldcubeassociation.org/competitions/2634/rounds/36520/projector)
 ## 21-05-23

Day 56: #100DaysOfCode in #Cpp progress - today I worked on the project TextColors https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day056_21-05-23/TextColors (see http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html)
 ## 22-05-23

Day 57: #100DaysOfCode in #Cpp progress - today I worked on the projects Diagonals https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day057_22-05-23/Diagonals and Connect4 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day057_22-05-23/Connect4. My ambition was to code a computer player for Connect4, but it is so slow it only works on a 4x4 board. Next: profiling to speed it up.
 ## 23-05-23

Day 58: #100DaysOfCode in #Cpp progress - today I worked on the project Profiling https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day058_23-05-23/Profiling (see https://www.youtube.com/watch?v=nXaxk27zwlk)
 ## 24-05-23

Day 59: #100DaysOfCode in #Cpp progress - today I worked on the project LinesOfCode https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day059_24-05-23/LinesOfCode (see https://en.wikipedia.org/wiki/Source_lines_of_code)
 ## 25-05-23

Day 60: #100DaysOfCode in #Cpp progress - today I worked on the project GraphPlot https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day060_25-05-23/GraphPlot
 ## 26-05-23

Day 61: #100DaysOfCode in #Cpp progress - today I made a crude attempt at profiling and refactoring. Performance improved x3, but this is still very far from sufficient... :-( ImprovingConnect4 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day061_26-05-23/ImprovingConnect4
 ## 27-05-23

Day 62: #100DaysOfCode in #Cpp progress - today I worked on the project ImprovingConnect4_Part2 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day062_27-05-23/ImprovingConnect4_Part2. Another 40% improvement in performance, but still no cigar...
 ## 28-05-23

Day 63: #100DaysOfCode in #Cpp progress - today I worked on the project ResistorColorCode https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day063_28-05-23/ResistorColorCode (see https://edabit.com/challenge/nWBCvjboaxAvqyWSt)
 ## 29-05-23

Day 64: #100DaysOfCode in #Cpp progress - today I worked on the project LinesOfCodeTable https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day064_29-05-23/LinesOfCodeTable. The final goal is to plot a graph showing the daily the progress in terms of LOC. I am close but not quite there yet.  
 ## 30-05-23

Day 65: #100DaysOfCode in #Cpp progress - today I worked on the project LinesOfCodeGraph https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day065_30-05-23/LinesOfCodeGraph. I got my graphs, but they are ugly though...
 ## 31-05-23

Day 66: #100DaysOfCode in #Cpp progress - today I worked on the project AdjacencyMatrixAndList https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day066_31-05-23/AdjacencyMatrixAndList (see https://www.section.io/engineering-education/graphs-in-data-structure-using-cplusplus/)
 ## 01-06-23

Day 67: #100DaysOfCode in #Cpp progress - today I worked on the project Bitmap2Graph https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day067_01-06-23/Bitmap2Graph
 ## 02-06-23

Day 68: #100DaysOfCode in #Cpp progress - today I worked on the project FasterGraphPlots https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day068_02-06-23/FasterGraphPlots (see https://github.com/alandefreitas/matplotplusplus/blob/master/examples/graphs/graph/graph_3.cpp)
 ## 03-06-23

Day 69: #100DaysOfCode in #Cpp progress - today I worked on the project Dijkstra https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day069_03-06-23/Dijkstra (see https://favtutor.com/blogs/dijkstras-algorithm-cpp)
 ## 04-06-23

Day 70: #100DaysOfCode in #Cpp progress - today I worked on the project 2048 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day070_04-06-23/2048 (see https://play2048.co/)
 ## 05-06-23

Day 71: #100DaysOfCode in #Cpp progress - today I tried different approaches to add a simple logging facility to my C++ programs: Logging1, Logging 2 and Logging3 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day071_05-06-23/ For the third attempt I enlisted the help of ChatGPT (see https://chat.openai.com/share/0df65979-3ea5-4469-8ac9-ca7fcf4f8916). Happy with the result, even if some fiddling was required.
 ## 06-06-23

Day 72: #100DaysOfCode in #Cpp progress - today I worked on the project PlotShortestPath https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day072_06-06-23/PlotShortestPath (see https://github.com/alandefreitas/matplotplusplus/blob/master/examples/graphs/graph/graph_4.cpp)
 ## 07-06-23

Day 73: #100DaysOfCode in #Cpp progress - today I worked on the project SaveGraph https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day073_07-06-23/SaveGraph
 ## 08-06-23

Day 74: #100DaysOfCode in #Cpp progress - today I worked on the projects Bitmap2Graph2 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day074_08-06-23/Bitmap2Graph2 (see ) and PlotShortestPath2 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day074_08-06-23/PlotShortestPath2 (see https://github.com/alandefreitas/matplotplusplus/blob/master/examples/graphs/graph/graph_4.cpp)
 ## 09-06-23

Day 75: #100DaysOfCode in #Cpp progress - today I worked on the project RotateScale https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day075_09-06-23/RotateScale (see https://stackoverflow.com/questions/22041699/rotate-an-image-without-cropping-in-opencv-in-c/33564950#33564950)
 ## 10-06-23

Day 76: #100DaysOfCode in #Cpp progress - today I worked on the project Dobble https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day076_10-06-23/Dobble (see https://www.101computing.net/the-dobble-algorithm/)
 ## 11-06-23

Day 77: #100DaysOfCode in #Cpp progress - threads, threads, threads: https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day077_11-06-23/Threads1 , https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day077_11-06-23/Threads2 and https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day077_11-06-23/Threads3 
 ## 12-06-23

Day 78: #100DaysOfCode in #Cpp progress - more threads: https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day078_12-06-23/MoreThreads1 , https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day078_12-06-23/MoreThreads2 and https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day078_12-06-23/MoreThreads3 (see https://holowczak.com/introduction-to-multithreading-in-cplusplus/?amp=1). 
 ## 13-06-23

Day 79: #100DaysOfCode in #Cpp progress - today I worked on the project MultiThreadingDemo https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day079_13-06-23/MultiThreadingDemo (see https://m.youtube.com/watch?v=xPqnoB2hjjA)
 ## 14-06-23

Day 80: #100DaysOfCode in #Cpp progress - today I worked on the project ParallelImageProcessing https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day080_14-06-23/ParallelImageProcessing (see https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/)
 ## 15-06-23

Day 81: #100DaysOfCode in #Cpp progress - today I worked on the project WeatherApp https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day081_15-06-23/WeatherApp (see https://m.youtube.com/watch?v=xPqnoB2hjjA) #threads
 ## 16-06-23

Day 82: #100DaysOfCode in #Cpp progress - today I worked on the project WebScraping https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day082_16-06-23/WebScraping (see https://www.scrapingbee.com/blog/web-scraping-c++/)
 ## 17-06-23

Day 83: #100DaysOfCode in #Cpp progress - today I worked on the project Rectangle https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day083_17-06-23/Rectangle
 ## 18-06-23

Day 84: #100DaysOfCode in #Cpp progress - today I worked on the projects Ncurses0 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day084_18-06-23/Ncurses0 (see https://www.youtube.com/watch?v=lV-OPQhPvSM) and Ncurses1 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day084_18-06-23/Ncurses1 (see https://www.youtube.com/watch?v=A5lX1h_2zy0)
 ## 19-06-23

Day 85: #100DaysOfCode in #Cpp progress - today I worked on the project Ncurses2to3 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day085_19-06-23/Ncurses2to3 (see https://www.youtube.com/playlist?list=PL2U2TQ__OrQ8jTf0_noNKtHMuYlyxQl4v)
 ## 20-06-23

Day 86: #100DaysOfCode in #Cpp progress - today I worked on the project KeyboardGameControl https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day086_20-06-23/KeyboardGameControl (see https://gamedev.stackexchange.com/questions/144558/key-released-multiple-keys-how-to-go-around-ncurses-limitations)
 ## 21-06-23

Day 87: #100DaysOfCode in #Cpp progress - today I worked on the project CollisionDetection https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day087_21-06-23/CollisionDetection (see https://www.jeffreythompson.org/collision-detection/)
 ## 22-06-23

Day 88: #100DaysOfCode in #Cpp progress - today I worked on the projects GameEngineHelloWorld https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day088_22-06-23/GameEngineHelloWorld (see https://github.com/OneLoneCoder/olcPixelGameEngine) and Arkanoid1 https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day088_22-06-23/Arkanoid1 (see https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/)
 ## 23-06-23

Day 89: #100DaysOfCode in #Cpp progress - today I worked on the project ArkanoidSprites https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day089_23-06-23/ArkanoidSprites (see https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/TUTORIAL---Sprites)
 ## 24-06-23

Day 90: #100DaysOfCode in #Cpp progress - today I worked on the project Asteroids https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day090_24-06-23/Asteroids (see https://www.youtube.com/watch?v=QgDR8LrRZhk)
 ## 25-06-23

Day 91: #100DaysOfCode in #Cpp progress - today I concluded sound in C++ is ridiculously difficult PortaudioPlayWAV https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day091_25-06-23/PortaudioPlayWAV (see https://github.com/albertz/music-player-core/blob/master/examples/portaudio-wavplay-demo.cpp) and PinkNoise https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day091_25-06-23/PinkNoise (see https://github.com/PortAudio/portaudio/blob/master/examples/paex_pink.c)
 ## 26-06-23

Day 92: #100DaysOfCode in #Cpp progress - today I worked on the project SDL2Sounds https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day092_26-06-23/SDL2Sounds (see https://www.youtube.com/watch?v=lBCVC7ubBzs)