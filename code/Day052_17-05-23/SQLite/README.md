#link: https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/

# Managing a SQLite database

## Getting started

1. Install SQLite with:

```bash
$ sudo apt-get install sqlite3 libsqlite3-dev
```

2. Download a sample database (.db file) e.g. from https://github.com/jOOQ/sakila
3. Install a GUI SQLite browser app e.g. [DB browser]() (or [DBeaver]())

```bash
$ sudo add-apt-repository -y ppa:linuxgndu/sqlitebrowser
$ sudo apt-get update
$ sudo apt-get install sqlitebrowser
```

4. Explore the file

## Compiling
Ensure library and header are in the path
Include the header `# include <sqlite3.h>`
Add `-l sqlite3` To compiler instruction

## Tasks
- Create a database
- Create (if not exists) a table
- Insert (or ignore) records
- Update records
- Delete records
- Show table status (sorted by id) before and after each operation

Better tutorial: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm#

More on SQLite syntax: https://www.geeksforgeeks.org/sqlite-statements-or-syntax/

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
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [x] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV