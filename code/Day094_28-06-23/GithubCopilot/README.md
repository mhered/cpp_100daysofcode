#link: https://docs.github.com/en/copilot/quickstart

# Github Copilot

THe link provides instruction to get started with Github's AI tool Copilot:
- sign up for Copilot 
- install [Github Copilot extension](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot) in vscode
- authorise vscode to your Github account
- create an empty `main.cpp`
- Use suggestions to build a `Date` class and a function `WorkingDays()` that counts the number of working days between two dates (i.e. returns the number of weekdays which are not bank holidays).

## Assessment

Copilot suggestions are indeed useful and can save time but at least in this case they didn't solve the issue. A couple of times proposed code unfit for purpose. One of the keys was the function to return the day of the week for a given date. I ended up looking it up in [Stack Overflow](https://stackoverflow.com/a/66094245/15472802), which pointed me to this [Geeksforgeeks blog post](https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/).

Overall the exercise proved to be more complicated than I initially thought. The proposed solution still is rather simplistic, not fully taking into account all cases for leap years, movable bank holidays etc.
- The class has a static list of bank holidays defined as "dd/mm" strings
- I checked for some leap years but not comprehensibly and I am afraid my solution if too simple
  
# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [x] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [x] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [x] AI_tools: Github Copilot
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV