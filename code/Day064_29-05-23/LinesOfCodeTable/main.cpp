#include <string>
#include <iostream>
#include <filesystem>

#include <fstream>
#include <vector>
#include <sstream>

#include <algorithm>

#include <unordered_map>
#include <matplot/matplot.h>

#include "File.h"

namespace fs = std::filesystem;

// aux function to extract substring from string
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
    int CountTotalLines;
    int CountCodeLines;
    int CountCommentLines;
    int CountBlankLines;
    bool ReadTagsFromReadme(fs::path filename, bool verbose);

    // we override the << operator to have a stream method for Project
    friend std::ostream &operator<<(std::ostream &os, const Project &obj)
    {
        os << "| " << std::setw(3) << obj.Day;
        os << " | " << std::setw(8) << obj.Date;
        os << " | " << std::setw(25) << obj.Name;
        os << " | " << std::setw(8) << obj.CountTotalLines;
        os << " | " << std::setw(8) << obj.CountCodeLines;
        os << " | " << std::setw(8) << obj.CountCommentLines;
        os << " | " << std::setw(8) << obj.CountBlankLines << " |";

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
    std::vector<Project> projects; // to accumulate projects in path
    int CountTotalLines = 0;
    int CountCodeLines = 0;
    int CountCommentLines = 0;
    int CountBlankLines = 0;

    if (verbose)
    {
        std::cout << "Scanning: " << path.filename() << std::endl;
    }

    for (const auto &entry : fs::directory_iterator(path))
    {

        if (entry.is_directory())
        {
            if (entry.path().filename() != "sandbox" && entry.path().filename() != "bin")
            {
                std::vector<Project> more_projects = scanDirectory(entry.path(), verbose); // recursive call
                // append
                projects.insert(std::end(projects), std::begin(more_projects), std::end(more_projects));
            }
        }

        if (entry.is_regular_file())
        {
            std::string ext = entry.path().filename().extension();
            if (ext == ".cpp" || ext == ".h" || ext == ".hpp") // only for sourc files
            {
                std::string project_folder = fs::canonical(entry.path().parent_path()).filename().string();
                std::string day_folder = fs::canonical(entry.path().parent_path().parent_path()).filename().string();

                File file(entry.path());

                CountTotalLines += file.count_total_lines;
                CountCodeLines += file.count_code_lines;
                CountCommentLines += file.count_comment_lines;
                CountBlankLines += file.count_blank_lines;

                if (verbose)
                {
                    std::cout << "Found source file " << entry.path().filename() << " at : " << day_folder
                              << " / " << project_folder << std::flush;
                    std::cout << "Total lines in file: " << file.count_total_lines << std::endl;
                    std::cout << "of which: " << std::endl;
                    std::cout << file.count_code_lines << " code lines" << std::endl;
                    std::cout << file.count_comment_lines << " comment lines" << std::endl;
                    std::cout << file.count_blank_lines << " blank lines" << std::endl;
                    std::cout << std::endl;
                }

                Project project;
                project.Name = project_folder;
                project.Day = stoi(extract(day_folder, "Day", "_"));
                project.Date = extract(day_folder, "_", "");
                project.Path = fs::canonical(entry.path().parent_path());
                project.CountTotalLines = CountTotalLines;
                project.CountCodeLines = CountCodeLines;
                project.CountCommentLines = CountCommentLines;
                project.CountBlankLines = CountBlankLines;

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

std::string toCamelCase(std::string str)
{
    for (uint i = 0; i < str.length(); i++)
    {
        if (str[i] == '_')
        {
            char uppercase = (char)std::toupper(str[i + 1]);
            std::string replacestr(1, uppercase);
            str.replace(i, 2, replacestr);
        }
    }
    return str;
}

std::vector<std::size_t> sort_descending(const std::vector<int> &vec)
{
    std::vector<std::size_t> p(vec.size());
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),
              [&](std::size_t i, std::size_t j)
              { return (vec[i] > vec[j]); });
    return p;
}

template <typename T>
std::vector<T> apply_sorting(const std::vector<T> &vec,
                             const std::vector<std::size_t> &p)
{
    std::vector<T> sorted_vec(vec.size());
    std::transform(p.begin(), p.end(), sorted_vec.begin(),
                   [&](std::size_t i)
                   { return vec[i]; });
    return sorted_vec;
}

int main()
{

    fs::path root_path = "/home/mhered/cpp_100daysofcode/"; // fs::current_path();

    fs::path subfolder("code");
    fs::path path = root_path / subfolder;
    std::vector<Project> projects = scanDirectory(path);
    sort(projects.begin(), projects.end(), compareProjectsByDayThenName); // sort projects by day then name

    std::cout << "| Day |   Date   |                   Project |    Lines |     Code | Comments |    Blank |" << std::endl;
    std::cout << "|-----|----------|---------------------------|----------|----------|----------|----------|" << std::endl;

    for (auto project : projects)
        std::cout << project << std::flush;

    return 0;
}