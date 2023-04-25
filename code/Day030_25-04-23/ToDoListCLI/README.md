#link: https://www.youtube.com/watch?v=1DR-Sj-RLzQ

# To Do List

The task is building from scratch a basic To Do List manager that uses the command line as interface:

* `help` - display a message with usage instructions
* `ls` - display the list of pending actions
* `log` - display a log of actions completed with corresponding timestaps
* `stat` - display current time, current number of actions pending and actions completed
* `add [STRING]` - add a new task to the list of pending actions
* `del [N1] [N2] [NK]` - delete a batch of tasks (identified by the # shown in `ls`)
* `done [N1] [N2] [NK]`- mark as completed a batch of tasks (identified by the # shown in `ls`)
* `prio [N1] [N2] [NK]`- move a batch of tasks (identified by the # shown in `ls`) to the top of the list 

Persistence of the list of tasks provided by simple text files `todo.txt` and `done.txt`. 

```bash
TASK HELP
help - display this help                $ ./task help
ls   - show the list of pending tasks   $ ./task ls
log  - show the log of completed tasks  $ ./task log
add  - add a new pending task           $ ./task add "New task" 
del  - delete tasks (by #)              $ ./task del 2 3 10
done - set tasks as complete (by #)     $ ./task done 1 2
prio - prioritize tasks (by #)          $ ./task prio 6 3
stat - display a status report          $ ./task stat
``` 

The exercise is originally inspired the video in the link above. I came across it while I was searching for tutorials for C++ CLI libraries. 
I cleaned up the code a bit, e.g. using auxiliary functions to avoid repetition, and added some functionalities such as the ability to delete or complete tasks in batches with a single command, and the command to prioritize tasks

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
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV