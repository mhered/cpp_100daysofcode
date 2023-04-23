#include <string>
#include <iostream>
#include <filesystem>

#include <fstream>
#include <vector>
#include <sstream>

#include <algorithm>

#include <unordered_map>
#include <matplot/matplot.h>

namespace fs = std::filesystem;

std::string extract(std::string str, std::string start_delimiter, std::string end_delimiter)
{
    unsigned start = str.find(start_delimiter) + start_delimiter.length();
    unsigned last = str.find(end_delimiter);
    std::string result = str.substr(start, last - start);
    return result;
}

struct Project
{
    std::string Name;
    int Day;
    std::string Date;
    fs::path Path;
    std::vector<std::string> Tags;

    bool ReadTagsFromReadme(fs::path filename, bool verbose);

    // we override the << operator to have a stream method for Project
    friend std::ostream &operator<<(std::ostream &os, const Project &obj)
    {
        os << "Day " << obj.Day << " (" << obj.Date << ") Project: " << obj.Name << "\n";
        os << obj.Path << "\n";
        os << " " << obj.Tags.size() << " Tags: ";
        for (int i = 0; i < obj.Tags.size(); i++)
        {
            os << obj.Tags[i];
            if (i < obj.Tags.size() - 1)
                os << ", ";
        }
        return os << "\n";
    }
};

bool Project::ReadTagsFromReadme(fs::path filename, bool verbose = false)
{
    // ifstream is used for reading files
    std::ifstream inf{filename.string()};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
        return false;
    }

    int linecount = 0;
    while (inf)
    {
        // find tags section
        std::string line;
        std::getline(inf, line);
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        linecount++;
        if (line.rfind("#tags:", 0) == 0)
        {
            if (verbose)
                std::cout << filename << " has a tags section at line " << linecount << std::endl;
            while (inf)
            {
                std::string line;
                std::getline(inf, line);
                line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
                if (line.rfind("-[x]", 0) == 0)
                {
                    std::string tag = extract(line, "-[x]", ":");

                    if (verbose)
                        std::cout << tag << ", " << std::flush;
                    Tags.push_back(tag);
                }
            }
            if (verbose)
                std::cout << std::endl;
        }
    }
    return true;
}

bool compareProjectsByDayThenName(Project p1, Project p2)
{
    bool result;
    if (p1.Day == p2.Day)
        return (p1.Name < p2.Name);
    return (p1.Day < p2.Day);
}

std::vector<Project> scanDirectory(fs::path path, bool verbose = false)
{
    std::vector<Project> projects;

    if (verbose)
    {
        std::cout << "Scanning: " << path.filename() << std::endl;
    }

    for (const auto &entry : fs::directory_iterator(path))
    {

        if (entry.is_directory())
        {
            if (entry.path().filename() != "sandbox")
            {
                std::vector<Project> more_projects = scanDirectory(entry.path(), verbose);
                // append
                projects.insert(std::end(projects), std::begin(more_projects), std::end(more_projects));
            }
        }

        if (entry.is_regular_file())
        {
            if (entry.path().filename() == "README.md")
            {
                std::string project_folder = fs::canonical(entry.path().parent_path()).filename().string();
                std::string day_folder = fs::canonical(entry.path().parent_path().parent_path()).filename().string();

                if (verbose)
                {
                    std::cout << "Found README.md at : " << day_folder
                              << " / " << project_folder << std::flush;
                    std::cout << " Size: " << entry.file_size() << "Kb" << std::endl;
                }

                Project project;
                project.Name = project_folder;
                project.Day = stoi(extract(day_folder, "Day", "_"));
                project.Date = extract(day_folder, "_", "");
                project.Path = fs::canonical(entry.path().parent_path());
                if (project.ReadTagsFromReadme(entry.path(), verbose))
                    projects.push_back(project);
            }
        }
    }
    return projects;
}

std::unordered_map<std::string, int> Counter(std::vector<std::string> stringVector)
{

    std::unordered_map<std::string, int> counter;

    for (auto stringval : stringVector)
    {
        if (counter.find(stringval) == counter.end()) // the first time the key is found
        {
            counter[stringval] = 1; // initialize the counter with value 1
        }
        else
        {
            counter[stringval]++; // if key is already present, increment the counter
        }
    }
    return counter;
}

int main()
{

    fs::path root_path = "/home/mhered/cpp_100daysofcode/"; // fs::current_path();

    fs::path subfolder("code");
    fs::path path = root_path / subfolder;
    // std::cout << path << std::endl;
    std::vector<Project> projects = scanDirectory(path);
    sort(projects.begin(), projects.end(), compareProjectsByDayThenName); // sort projects by day then name

    for (auto project : projects)
        if (!project.Tags.empty())
            std::cout << project << std::endl;

    std::vector<std::string> tags;
    for (auto project : projects)
    {
        // append to list of tags
        tags.insert(std::end(tags), std::begin(project.Tags), std::end(project.Tags));
    }

    std::unordered_map<std::string, int> counter = Counter(tags);

    std::vector<int> y;
    std::vector<std::string> labels;

    for (auto keyvaluepair : counter)
    {
        // .first to access key, .second to access value
        std::cout << keyvaluepair.first << ":" << keyvaluepair.second << std::endl;
        y.push_back(keyvaluepair.second);
        labels.push_back(keyvaluepair.first);
    }
    if (y.size())
    {
        matplot::bar(y)->face_color("g");
        matplot::gca()->x_axis().ticklabels(labels);

        matplot::show();
        // matplot::save("tag_bars.png");
    }
    return 0;
}