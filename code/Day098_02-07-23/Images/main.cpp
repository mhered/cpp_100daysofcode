#include <string>
#include <iostream>

#include <filesystem>

#include <fstream>
#include <vector>
#include <sstream>

#include <algorithm>

namespace fs = std::filesystem; // requires -std=c++17


// auxiliary function to extract substring between two delimiters from a string
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

// auxiliary function returns true if a string is found in list of strings, false otherwise
bool contains(std::vector<std::string> str_list, std::string str)
{
    for (auto str_in_list : str_list)
    {
        if (str_in_list == str)
            return true;
    }
    return false;
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

    // list of folders to not explore
    std::vector<std::string> EXCLUDE_FOLDERS = {
        "sandbox",
        "cpp_redis",
        "portaudio"};

    for (const auto &entry : fs::directory_iterator(path))
    {

        if (entry.is_directory() && !contains(EXCLUDE_FOLDERS, entry.path().filename()))
        {

            std::vector<Project> more_projects = scanDirectory(entry.path(), verbose);
            // append
            projects.insert(std::end(projects), std::begin(more_projects), std::end(more_projects));
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


// auxiliary function to make a string lowercase
std::string tolower_str(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return str;
}

bool findDayImage(fs::path path, fs::path &image, bool verbose = false)
{

    if (verbose)
    {
        std::cout << "Scanning: " << path.filename() << std::endl;
    }

    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())

        {

            std::string extension = tolower_str(entry.path().filename().extension().string());
            if (extension == ".jpg" || extension == ".jpeg")
            {
                if (verbose)
                {
                    std::cout << "Found JPG at : " << entry.path() << std::endl;
                }
                image = entry.path();
                return true;
            }
            if (extension == ".png")
            {
                if (verbose)
                {
                    std::cout << "Found PNG at : " << entry.path() << std::endl;
                }
                image = entry.path();
                return true;
            }
            if (extension == ".webp")
            {
                if (verbose)
                {
                    std::cout << "Found WEBP at : " << entry.path() << std::endl;
                }
                image = entry.path();
                return true;
            }
            if (extension == ".gif")
            {
                if (verbose)
                {
                    std::cout << "Found GIF at : " << entry.path() << std::endl;
                }
                image = entry.path();
                return true;
            }
        }
    }
    return false;
}

bool writeTextToFile(std::string filename, std::string text)
{
    // ofstream is used for writing files
    // We'll make a file called Sample.txt
    std::ofstream outf{filename};

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        // Print an error and exit
        std::cerr << "File " << filename << " could not be opened for writing\n";
        return false;
    }

    // Write text into this file
    outf << text << "\n";
    return true;

    // When outf goes out of scope, the ofstream
    // destructor will close the file
}

int main()
{

    fs::path root_path = "/home/mhered/cpp_100daysofcode/"; // fs::current_path();

    fs::path subfolder("code"); //"sandbox"
    fs::path path = root_path / subfolder;
    std::cout << path << std::endl;
    std::vector<Project> projects = scanDirectory(path);
    sort(projects.begin(), projects.end(), compareProjectsByDayThenName); // sort projects by day then name

    std::string current_date = "";
    std::string last_date = "";
    std::stringstream ss;
    ss << "| Day | Image | Projects |" << std::endl;
    ss << "| --- | --- | --- " << std::flush;

    for (auto project : projects)
    {
        if (!project.Tags.empty()) // skip projects with no tags
        {
            current_date = project.Date;
            if (current_date != last_date)
            {
                std::stringstream ss2;
                ss2 << "Day " << std::setfill('0') << std::setw(3) << project.Day;
                std::string Day_str = ss2.str();
                fs::path Image_path;
                ss << "|" << std::endl;
                if (findDayImage(project.Path.parent_path(), Image_path))
                {
                    ss << "| " << Day_str << " | ![](" << Image_path.string() << ") | " << std::flush;
                }
                else
                    ss << "| " << Day_str << " | NO IMAGE | " << std::flush;

                last_date = current_date;
            }
            ss << "[" << project.Name << "](" << project.Path.string() << ")<br />" << std::flush;
        }
    }
    ss << "|" << std::endl;

    if (writeTextToFile("output.md", ss.str()))
        return 0;
    return -1;
}