#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

const std::string PENDINGFILE = "todo.txt";
const std::string COMPLETEDFILE = "done.txt";

// auxiliary functions

std::string one_liner(int ntasks)
{
    std::string msg;
    if (ntasks == 0)
        msg = "No tasks";
    else if (ntasks == 1)
        msg = "1 task";
    else
        msg = std::to_string(ntasks) + " tasks";

    return msg;
}

std::string get_time_stamp()
{
    // prepare string to log the completed task
    std::string str = "";
    std::time_t time_stamp = std::time(0); // get timestamp
    char time_char[24];                    // format as string
    std::strftime(time_char,
                  24,
                  "%d/%m/%Y %H:%M:%S",
                  localtime(&time_stamp));
    return str.append(time_char); // converts char to std::string
}

bool read_from_file(std::string filename, std::vector<std::string> &tasks)
{

    std::string task;

    std::fstream infile;
    infile.open(filename, std::ios::in);

    if (!infile)
    {
        // If the input file stream cannot be open for reading
        // Print an error and exit
        std::cerr << "ERROR: Could not open " << filename << std::endl;
        return false;
    }
    else
    {
        while (std::getline(infile, task))
        {
            tasks.push_back(task);
        }
    }
    infile.close();
    return true;
}

bool write_to_file(std::vector<std::string> tasks, std::string filename)
{
    // ofstream with option std::ios_base::app to write to file
    std::fstream outfile;
    outfile.open(filename, std::ios::out);

    // If we couldn't open the output file stream for writing
    if (!outfile)
    {
        // Print an error and exit
        std::cerr << "ERROR: Could not open " << PENDINGFILE << " for writing" << std::endl;
        return false;
    }

    for (int i = 0; i < tasks.size(); i++)
    {
        outfile << tasks[i] << "\n";
    }
    outfile.close();
    return true;
}

bool append_to_file(std::string new_task, std::string filename)
{
    // ofstream with option std::ios_base::app to append to file
    std::fstream outfile;
    outfile.open(filename, std::ios::app);

    // If we couldn't open the output file stream for writing
    if (!outfile)
    {
        // Print an error and exit
        std::cerr << "ERROR: Could not open " << PENDINGFILE << " for appending" << std::endl;
        return false;
    }
    outfile << new_task << "\n";
    outfile.close();
    return true;
}

// callback functions

bool add_task(std::string new_task)
{
    if (append_to_file(new_task, PENDINGFILE))
    {
        std::cout << "Adding task : \"" << new_task << "\"" << std::endl;
        return true;
    }
    return false;
}

bool delete_task(int k)
{
    // read tasks from file
    std::vector<std::string> tasks = {};

    if (!read_from_file(PENDINGFILE, tasks))
        return false;

    if (k < 1 || k > tasks.size())
    {
        std::cerr << "ERROR: Invalid task #" << k << ". Nothing was deleted." << std::endl;
        return false;
    }

    if (tasks[k - 1].empty()) // ignore empty lines
        return false;

    std::cout << "Deleting task #" << k << ": \"" << tasks[k - 1] << "\"" << std::endl;
    tasks.erase(tasks.begin() + k - 1);

    if (!write_to_file(tasks, PENDINGFILE))
        return false;

    return true;
}

bool complete_task(int k)
{
    // read tasks from file
    std::vector<std::string> tasks = {};

    if (!read_from_file(PENDINGFILE, tasks))
        return false;

    if (k < 1 || k > tasks.size())
    {
        std::cerr << "ERROR: Invalid task #" << k << ". Nothing was set as complete." << std::endl;
        return false;
    }

    // prepend timestamp to task
    std::string completed_task = "[" + get_time_stamp();
    completed_task += "] \"" + tasks[k - 1] + "\"";

    std::cout << "Setting task #" << k << " as done: \""
              << tasks[k - 1] << "\"" << std::endl;

    // log completed task
    if (!append_to_file(completed_task, COMPLETEDFILE))
        return false;

    // remove completed task from todo list
    tasks.erase(tasks.begin() + k - 1);

    if (!write_to_file(tasks, PENDINGFILE))
        return false; // careful, this is destructive!

    return true;
}

bool prio_task(int k)
{
    // read tasks from file
    std::vector<std::string> tasks = {};

    if (!read_from_file(PENDINGFILE, tasks))
        return false;

    if (k < 1 || k > tasks.size())
    {
        std::cerr << "ERROR: Invalid task #" << k << ". Nothing was prioritized." << std::endl;
        return false;
    }

    std::rotate(tasks.begin(), tasks.begin() + k - 1, tasks.begin() + k);

    if (!write_to_file(tasks, PENDINGFILE))
        return false; // careful, this is destructive!

    return true;
}

bool list_tasks()
{
    std::vector<std::string> tasks = {};
    if (read_from_file(PENDINGFILE, tasks))
    {
        if (tasks.empty())
        {
            std::cout << "NOTHING TO DO" << std::endl;
        }
        else
        {
            std::cout << "TO DO:" << std::endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (!tasks[i].empty())
                    std::cout << "[" << i + 1 << "] - " << tasks[i] << std::endl;
            }
            return true;
        }
    }
    return false;
}

bool log()
{
    std::vector<std::string> completed_tasks = {};
    if (!read_from_file(COMPLETEDFILE, completed_tasks))
        return false;
    if (completed_tasks.empty())
        std::cout << "NOTHING DONE" << std::endl;
    else
    {
        std::cout << "DONE:" << std::endl;
        for (int i = 0; i < completed_tasks.size(); i++)
        {
            std::cout << completed_tasks[i] << std::endl;
        }
    }
    return true;
}

void help()
{
    std::string msg = "task- A simple command line interface To Do manager\n\n";
    msg += "Usage: ./task {command} {parameters}\n\n";
    msg += "Available commands:\n\n";
    msg += "  help - display this help                $ ./task help\n";
    msg += "  ls   - show the list of pending tasks   $ ./task ls\n";
    msg += "  log  - show the log of completed tasks  $ ./task log\n";
    msg += "  add  - add a new pending task           $ ./task add \"New task\" \n";
    msg += "  del  - delete tasks (by #)              $ ./task del 2 3 10\n";
    msg += "  done - set tasks as complete (by #)     $ ./task done 1 2\n";
    msg += "  prio - prioritize a task (by #)         $ ./task prio 6\n";
    msg += "  stat - display a status report          $ ./task stat\n";

    std::cout << msg << std::endl;
}

bool stats()
{
    std::vector<std::string> completed_tasks = {};
    std::vector<std::string> pending_tasks = {};
    if (!read_from_file(COMPLETEDFILE, completed_tasks) ||
        !read_from_file(PENDINGFILE, pending_tasks))
        return false;

    std::string msg = "";

    msg = " Status " + get_time_stamp() + ": ";
    msg += one_liner(pending_tasks.size()) + " Pending. ";
    msg += one_liner(completed_tasks.size()) + " Completed.\n";

    std::cout << msg << std::endl;

    return true;
}

int main(int argc, char *argv[])
{
    // declare variables
    std::string Command, Parameter;
    int k = 0;

    if (argc > 1)
        Command = argv[1];

    if (argc == 1 || Command == "help") // display help
    {
        help();
    }
    else if (Command == "add")
    {
        if (argc == 2)
        {
            std::cout << "ERROR: missing task string. Nothing was added." << std::endl;
            help();
        }
        else
        {
            Parameter = argv[2];
            add_task(Parameter);
        }
    }
    else if (Command == "del")
    {
        if (argc == 2)
        {
            std::cout << "ERROR: missing task number. Nothing was deleted." << std::endl;
            help();
        }
        else
        {
            // can take several inputs
            std::vector<int> Parameters;
            for (int i = 2; i < argc; i++)
            {
                Parameters.push_back(std::stoi(argv[i]));
            }
            // sort in descending order
            std::sort(Parameters.begin(), Parameters.end(), std::greater<int>());
            for (auto Parameter : Parameters)
                delete_task(Parameter);
        }
    }
    else if (Command == "done")
    {
        if (argc == 2)
        {
            std::cout << "ERROR: missing task number. Nothing was marked as completed." << std::endl;
            help();
        }
        else
        {
            // can take several inputs
            std::vector<int> Parameters;
            for (int i = 2; i < argc; i++)
            {
                Parameters.push_back(std::stoi(argv[i]));
            }
            // sort in descending order
            std::sort(Parameters.begin(), Parameters.end(), std::greater<int>());
            for (auto Parameter : Parameters)
                complete_task(Parameter);
        }
    }
    else if (Command == "ls") // display list of pending tasks
    {
        list_tasks();
    }
    else if (Command == "stats") // display report
    {
        stats();
    }
    else if (Command == "log") // display log
    {
        log();
    }
    else if (Command == "prio") // display log
    {
        if (argc == 2)
        {
            std::cout << "ERROR: missing task number. Nothing was prioritized." << std::endl;
            help();
        }
        else
        {
            // can take only one input
            Parameter = argv[2];
            prio_task(std::stoi(Parameter));
        }
    }

    return 0;
}