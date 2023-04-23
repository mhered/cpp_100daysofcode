
#link: 

# Data formats

Create functions to read a CSV, JSON and XML file into a vector of `class Data`

Sample files created with the Mockaroo schema Students: https://www.mockaroo.com/679447b0 

| Field name | Type in Data class | Comments on format | Sample |
| ------ | ---- | -------- | ------- |
|   `id`   | `int` |          | `1` |
|   `first_name`   | `std::string` |          | `Lois` |
| `last_name`  | `std::string`      |                     | `Lane`      |
| `birthdate`  | `std::string`      | `dd/mm/yyyy`        | `15/3/1958` |
| `gender`     | `std::string`      |                     | `F`         |
| `score`      | `double`           | 0-1 with 4 decimals | `0.9342`    |

### `std::vector<Data> readCSV(std::string filename)` 

loosely based on https://java2blog.com/read-csv-file-in-cpp/ but incorporates other things such as returning a vector of objects

### `std::vector<Data> readJSON(std::string filename)`

Recommended library: https://github.com/nlohmann/json

Install instructions for Ubuntu 20.04 here: https://ubuntu.pkgs.org/20.04/ubuntu-universe-amd64/nlohmann-json3-dev_3.7.3-1_all.deb.html

```bash
$ sudo apt-get update
$ sudo apt-get install nlohmann-json3-dev
```

Documentation: https://json.nlohmann.me/

Quick examples: https://github.com/nlohmann/json#examples were enough to quickly build it. Great!!

### `std::vector<Data> readXML(std::string filename)`

* Library: rapidxml https://rapidxml.sourceforge.net/

Installation instructions: https://ubuntu.pkgs.org/20.04/ubuntu-universe-amd64/librapidxml-dev_1.13-2_all.deb.html

```bash
$ sudo apt-get update
$ sudo apt-get install librapidxml-dev
```

A tutorial: https://www.roxlu.com/2014/034/rapidxml

A better tutorial: https://spin.atomicobject.com/2012/05/20/rapidxml-a-lightweight-xml-library-for-c/

---

Note: I also looked at libxml++ https://libxmlplusplus.github.io/libxmlplusplus/ (but discarded it because I found the documentation unappealing... 

Installation instructions:

```bash
sudo apt-get install libxml++5.0-dev libxml++5.0-doc
```

Compiling instructions: https://libxmlplusplus.github.io/libxmlplusplus/manual/html/sect-comp-link.html

# Tags

#tags: 
- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [x] strings: regex
- [ ] dates_times: timezones
- [x] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [x] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV