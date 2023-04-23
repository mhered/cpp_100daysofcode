#link: https://www.youtube.com/watch?v=FOIbK4bJKS8


# Cross Platform Graphical User Interfaces in C++

Main cross-platform options for GUI in C++ are: QT and [wxWidgets](https://www.wxwidgets.org/).

More than a GUI libraries, these frameworks handle many things using the native components for each OS (e.g. exceptions etc). 

Structure of a traditional program (polling):
```
while(running)
{
    GetInput()
    DoStuff()
    UpdateDisplay()
}
```
In GUIs this is abstracted away from the programmer, and simplified to 2 components:
* Structure: layout of the controls and panels. Parent-child tree structure: Main form (or dialog or frame) holds textboxes, buttons, listboxes, etc. 
* Events: e.g OnButtonClicked, which is a combination of OnMouseEntry, OnMouseButtonDown, OnMouseButtonUp, etc. A good GUI framework provides useful events.
* 
Therefore there is a shift of thinking from while loop to nuggets of code that can be called somewhat unpredictably.

## Installation of wxWidgets on Ubuntu

* To install I followed [this tutorial (pdf)](./InstallwxWidgets.pdf) from San Jose State University, source: https://www.cs.sjsu.edu/~mak/tutorials/

* This tutorial has additional information on how to compile a basic program using wxWigdets: https://www.binarytides.com/install-wxwidgets-ubuntu/

Note: for the compile to work I had to modify:
* `c_cpp_properties.json` to add `"/usr/local/include/wx-3.2"` to the include path
* `tasks.json` to remove  ` "-Werror"` and add  `` "`wx-config --cxxflags --libs std\`" `` to the arguments

Note: There is not even an `int main()`! All is masked by the framework.

## First GUI program

Create:

* a `class cApp` inherited from `public wxApp`. Doesn't show anything, it is just a launcher.
* a `class cMain` inherited from `public wxFrame` to make a window. In the constructor we override the base class with parent pointer (none because it is the root window), ID, and title.

# Tags

#tags: 
- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [x] object_oriented_programming
- [x] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV