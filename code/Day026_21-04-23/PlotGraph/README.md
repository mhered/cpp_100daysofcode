#link:  https://sciplot.github.io/



# Plotting data with C++

Top recommendations after some googling (e.g. https://stackoverflow.com/questions/4283731/plotting-package-for-c or https://stackoverflow.com/questions/63667255/plotting-graphs-in-c#63667672):

* [GNU plot](http://www.gnuplot.info/): is a CLI, and there is a [gnuplot-iostream wrapper]( http://stahlke.org/dan/gnuplot-iostream/). Seems old and steep learning curve. 
* [Sciplot](https://sciplot.github.io/): seems to be another wrapper for GNUplot, requires installing GNUplot then a header file. Beautiful and simple syntax
* [Matplotlib](https://github.com/lava/matplotlib-cpp): a C++ wrapper for the popular python package matplotlib. Requires python etc but then only needs to include a header file
* [Koolplot](http://koolplot.codecutter.org/): supposed to be very simple but limited
* CERN's [ROOT](https://root.cern/): A C++ library to plot graphs. Also seems to be a CLI... 
* [Matplot++](https://alandefreitas.github.io/matplotplusplus/): looks super complete and cool. This article makes a comparison to alternatives and sells Matplot++ well: https://alandefreitas.github.io/matplotplusplus/white-paper/#alternatives-for-data-visualization-in-c

## Matplot++

I tried Matplot++ first:

* need `vcpkg` (https://github.com/microsoft/vcpkg#quick-start-unix):

```bash
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh -disableMetrics
$ ./vcpkg integrate bash #activate autocompletion
```

* need Linux developer tools too: 

```bash
$ sudo apt-get install build-essential tar curl zip unzip
```

There are instructions to modify `settings.json` in  vscode: https://github.com/microsoft/vcpkg#using-vcpkg-with-cmake.

Install:

```bash
$ ./vcpkg install matplotplusplus
```

Tried also from here https://www.followchain.org/install-vcpkg-on-ubuntu/:

```bash
$ sudo ln -s ~/vcpkg/vcpkg /usr/local/bin/vcpkg
```

I checked also dependencies listed here: https://alandefreitas.github.io/matplotplusplus/integration/install/build-from-source/dependencies/

```bash
$ g++ --version # > 8 OK
$ cmake --version # > 3.14 OK
$ sudo apt install gnuplot # 5.2.6 OK
$ sudo apt-get install libglfw3-dev
```

I moved manually `include` and `lib` contents to `/usr/local/` and now it finds the headers but does not compile, throws 1K errors!

Cannot get it to work.... I uninstall following these instructions:  https://www.followchain.org/install-vcpkg-on-ubuntu/

## sciplot

Clone repo and make a link to the libraries. It also requires installing gnuplot.

```bash
$ sudo apt install gnuplot 
$ cd ~/git/
$ git clone https://github.com/sciplot/sciplot --recursive
$ sudo ln -s /home/mhered/git/sciplot/sciplot /usr/local/include/sciplot
```

Compiler throws 43 errors. Playing with `c_cpp_properties.json`  did not work, e.g. setting `"cppStandard": "c++17"`  or `"gnu++17"`

I found this in SO: https://stackoverflow.com/questions/49397233/how-to-enable-c17-support-in-vscode-c-extension, and adding  `  "-std=c++17",` to `args` in `tasks.json`  solved the issue! It was not using C++v17 after all!

Maybe I can now go back and try Matplot++ again...

# Tags

#tags: 

 -[ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [x] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV