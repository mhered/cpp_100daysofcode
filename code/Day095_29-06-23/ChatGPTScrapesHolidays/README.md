#link: https://chat.openai.com/share/b4077a5c-736d-41d2-be18-2360e0175d3c

# Asking ChatGPT to Scrape Bank Holidays

So after [playing with Github Copilot in the last project](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day094_28-06-23/GithubCopilot) I decided to get back to chatGPT to compare both AI tools.

So I asked chatGPT to write a C++ program to scrape bank holidays for a given country and year from the website https://www.officeholidays.com/

The complete exchange with chatGPT can be found in the link above.

 It came back immediately with a working solution that fetched the raw HTML - complete with instructions to install dependencies (curl) and to compile in linux. 

The second iteration - to process the HTML and write a markdown table - took some more time: 

* First, there was an additional dependency (`libxml2`), but chatGPT was not immediately forthcoming about it, and later on the library in question seemingly refused to cooperate.

I had the add the following to `tasks.json`, including the last option or the compiler just wouldn't find the include files, even though Intellisense did. Don't ask me why:
```json   
        "args": [
            ...
            "-lcurl",
            "-lxml2",
            "-I/usr/include/libxml2"
            ...
```

* Second, chatGPT forgot to mention one of the includes (`#include <libxml/xpathInternals.h>`) and it took many iterations for it to acknowledge it. It even 'invented' a non-existing alternative to the function that was not compiling... I had to ask directly to double check if I was missing an include.

* Then the code comppiled but yielded a segmentation error. chatGPT offered to add some statements to asist debugging and somehow the error went away.

* Still there were errors in the code proposed - mainly that it was fetching the wrong columns. I fixed the errors by hand.

For the final iteration I fed the working code back to chatGPT and asked it to refactor the solution in order to encapsulate the scraping code in the function `std::vector<std::pair<std::string, std::string>> fetchBankHolidays(std::string country, int year)`. This function should return a vector of pairs, each containing the date in "dd/mm" format and the name of the holiday. Although it was a simple task, unfortunately the function refactored by ChatGPT did not work, so I did it myself, by hand. As for the function to convert dates such as "Jan 23" into "23/01" I asked chatGPT separately to produce this and integrated it by hand.

## Conclusion

It was enjoyable and instructive. I did not learn to use the library but learnt other things and managed to get the data scraped. ChatGPT certainly increases your reach but you cannot trust the code it spits out without thoroughly checking it to ensure it does what is expected to do.

## To Do

Explore installing chatGPT directly in vscode: https://www.freecodecamp.org/news/install-chatgpt-in-vscode/

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
- [x] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [x] web_scraping
- [ ] OpenCV