#include "Data.h"
#include <iostream>
#include <vector>  //vector
#include <sstream> //ifstream
#include <iomanip> // setfill setw
#include <algorithm>  // sort

bool compare_Data_by_average(Data d1, Data d2)
{
    return (d1.t_avg_secs < d2.t_avg_secs);
}


int main()
{
    std::vector<Data> dataset, dataset_cp;
    std::string filename = "data.txt";

    if (readFromFile(filename, dataset))
    {
        std::cout << "| " << std::setfill(' ') << std::setw(3) << "ID" << std::flush;
        std::cout << " | " << std::setfill(' ') << std::setw(20) << "Participant" << std::flush;
        std::cout << " | " << std::setfill(' ') << std::setw(54) << "Five times" << std::flush;
        std::cout << " | " << std::setfill(' ') << std::setw(8) << "Avg"
                  << " |" << std::endl;
        std::cout << std::string(98, '-') << std::endl;

    dataset_cp = dataset;

    std::sort(dataset_cp.begin(), dataset_cp.end(), compare_Data_by_average);

        for (auto data_pt : dataset_cp)
        {
            data_pt.showtable();
        }
        std::cout << std::string(98, '-') << std::endl;
    }
    return 0;
}