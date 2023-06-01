#include <string>
#include <iostream>
#include <filesystem>

#include <fstream>
#include <vector>
#include <sstream>

#include <algorithm>

#include <set>
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

// auxiliary function: comparator to sort project list
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

    for (const auto &entry : fs::directory_iterator(path)) // no guarantees about the order it will scan
    {

        if (entry.is_directory())
        {
            if (entry.path().filename() != "sandbox" &&
                entry.path().filename() != "bin" &&
                entry.path().filename() != "Challenge1" &&
                entry.path().filename() != "Challenge2") // skip `sandbox`, `bin` and template folders
            {
                std::vector<Project> more_projects = scanDirectory(entry.path(), verbose); // recursive call
                // append
                projects.insert(std::end(projects), std::begin(more_projects), std::end(more_projects));
            }
        }

        if (entry.is_regular_file())
        {
            std::string ext = entry.path().filename().extension();
            std::string project_folder = fs::canonical(entry.path().parent_path()).filename().string();
            std::string day_folder = fs::canonical(entry.path().parent_path().parent_path()).filename().string();
            if (ext == ".cpp" || ext == ".h" || ext == ".hpp" || ext == ".ino") // only for sourc files
            {

                File file(entry.path());

                CountTotalLines += file.count_total_lines;
                CountCodeLines += file.count_code_lines;
                CountCommentLines += file.count_comment_lines;
                CountBlankLines += file.count_blank_lines;

                if (verbose)
                {
                    std::cout << " - Found source file " << entry.path().filename() << " at : " << day_folder
                              << " / " << project_folder << std::endl;
                    std::cout << "   Total lines in file: " << file.count_total_lines << " of which: " << std::endl;
                    std::cout << "\t" << file.count_code_lines << " code lines" << std::endl;
                    std::cout << "\t" << file.count_comment_lines << " comment lines" << std::endl;
                    std::cout << "\t" << file.count_blank_lines << " blank lines" << std::endl;
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
            else
            {
                if (verbose)
                {
                    std::cout << " - Found non-source file " << entry.path().filename() << " at : " << day_folder
                              << " / " << project_folder << std::endl
                              << std::endl;
                }
            }
        }
    }
    return projects;
}

// auxiliary function : counter for a vector of strings
std::unordered_map<std::string, int> Counter(std::vector<Project> ProjectVector)
{
    // std::vector<int> project_day;
    // std::vector<int> project_code_lines;

    int projects_per_day[100] = {0};
    int codelines_per_day[100] = {0};

    for (auto project : ProjectVector)
    {
        // project_day.push_back(project.Day);
        // project_code_lines.push_back(project.CountCodeLines);

        projects_per_day[project.Day]++;
        projects_per_day[project.Day] += project.CountCodeLines;
    }
}

int main()
{
    bool verbose = true;

    fs::path root_path = "/home/mhered/cpp_100daysofcode/"; // fs::current_path();

    fs::path subfolder("code");
    fs::path path = root_path / subfolder;
    std::vector<Project> projects = scanDirectory(path, verbose);
    sort(projects.begin(), projects.end(), compareProjectsByDayThenName); // sort projects by day then name

    if (verbose)
    {
        std::cout << "| Day |   Date   |                   Project |    Lines |     Code | Comments |    Blank |" << std::endl;
        std::cout << "|-----|----------|---------------------------|----------|----------|----------|----------|" << std::endl;

        for (auto project : projects)
            std::cout << project << std::flush;
    }

    int projects_per_day[100] = {0};
    int files_per_day[100] = {0};
    int codelines_per_day[100] = {0};

    std::set<std::string> project_set;

    for (auto project : projects)
    {
        if (project_set.find(project.Name) == project_set.end()) // if project not seen before, add it
        {
            projects_per_day[project.Day]++;
            project_set.insert(project.Name);
        }

        files_per_day[project.Day]++;
        codelines_per_day[project.Day] += project.CountCodeLines;
    }

    std::vector<int> accum_files_per_day;
    std::vector<int> accum_projects_per_day;
    std::vector<int> accum_codelines_per_day;
    std::vector<int> day;

    int run_sum_files = 0;
    int run_sum_projects = 0;
    int run_sum_codelines = 0;

    for (int i = 0; i < 100; i++)
    {
        run_sum_files += files_per_day[i];
        run_sum_projects += projects_per_day[i];
        run_sum_codelines += codelines_per_day[i];
        accum_files_per_day.push_back(run_sum_files);
        accum_projects_per_day.push_back(run_sum_projects);
        accum_codelines_per_day.push_back(run_sum_codelines);
        day.push_back(i + 1);
    }
    auto f = matplot::gcf();
    f->width(f->width() * 2);
    f->height(f->height() * 2);

    auto ax1 = matplot::subplot(3, 1, 1);
    matplot::plot(ax1, day, accum_projects_per_day);
    matplot::title(ax1, "Projects per day");

    auto ax2 = matplot::subplot(3, 1, 2);
    matplot::plot(ax2, day, accum_codelines_per_day);
    matplot::title(ax2, "Lines of Code per day");

    auto ax3 = matplot::subplot(3, 1, 3);
    matplot::plot(ax3, day, accum_files_per_day);
    matplot::title(ax3, "Source Files per day");

    matplot::show();

    return 0;
}