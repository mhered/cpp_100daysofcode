#link:

# 4_ManageDatabase

The goal of this project is to write C++ classes to manage a SQLite database in which to persist the records of news pieces.  

This is the fourth of a few tasks in which I split the project [Watchtower](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day100_04-07-23/Watchtower).

## Implementation Details
On Day 052 we introduced SQLite databases as a way to persist data, see project [SQLite](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day052_17-05-23/SQLite).

The file [./dbManager.h](./dbManager.h) implements two classes:

* class `Record` contains fields `link`, `title`, `comments`, `sender`, `date` and a list of `tags`, as well as a basic `display()` method to print out records.

* class `SQLiteManager` implements several public methods to manage a SQLite database:
  * constructor and destructor
  * `init()` to open a database and create a `Records` table
  *  methods for record manipulation: `addRecord()`,`updateRecord()` and `deleteRecord()`
  *  methods to query the db: `queryByLink()`, `queryBySender()`, `queryByDateRange()` and `queryByTag()`

## To do
- [x] move code to a header file
- [x] create unit tests
- [ ] integrate with Watchtower


# Tags
#tags: 

- [x] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [x] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [x] databases: SQLite
- [ ] API
- [ ] web_scraping
- [ ] OpenCV