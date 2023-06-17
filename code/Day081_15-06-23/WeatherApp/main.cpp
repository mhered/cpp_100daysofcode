#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <iterator>
#include <chrono>
#include <random>
#include <iomanip> // setprecision

#include <mutex>

std::map<std::string, double> remote_server, local_cache;
std::mutex mut_remote;
std::mutex mut_local;

template <typename T>
T random_value_in_range(T lower_bound, T upper_bound)
{
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    // std::default_random_engine rng;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    T random_value_in_range = unif(rng);
    return random_value_in_range;
}

void refresh_server_data(std::map<std::string, double> &remote_server)
{
    while (true)
    {

        for (auto &item : remote_server)
        {
            double delta_temp = .2 + random_value_in_range<double>(-.1, .1); // global warming
            // mut_remote.lock();
            item.second += delta_temp;
            // mut_remote.unlock();
        }
        /*std::cout << "SERVER : ";
        for (auto item : remote_server)
            std::cout
                << item.first << ": " << item.second << "C | ";
        std::cout << "\n";*/
        int wait = 2000 + random_value_in_range<int>(-1000, 1000); // changes every 1 to 3sec
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    }
}

void download_from_server(std::map<std::string, double> &local_cache,
                          std::map<std::string, double> &remote_server, bool loop = true)
{
    do
    {
        int wait = 2000; // it takes 2 sec in total
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        // mut_remote.lock();
        std::map<std::string, double> tmp = remote_server;
        // mut_remote.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        // mut_local.lock();
        local_cache = tmp;
        // mut_local.unlock();

        /*std::cout << "LOCAL : ";
        for (auto item : local_cache)
            std::cout
                << item.first << ": " << item.second << "C | ";
        std::cout << "\n";*/
    } while (loop);
}

void user_interface()
{
    system("clear");

    std::map<int, std::string> menu;
    int i = 1;
    for (auto item : local_cache)
        menu.insert(std::make_pair(i++, item.first));

    int usr_choice_idx;

    while (true)
    {
        // display menu
        for (auto item : menu)
            std::cout << item.first << ". " << item.second << "\n";
        std::cout << "Please select a city to track its temperature (1-"
                  << menu.size() << "): ";

        std::string user_choice_str;
        std::cin >> user_choice_str;
        std::cout << std::endl;

        usr_choice_idx = stoi(user_choice_str);
        if (usr_choice_idx >= 0 && usr_choice_idx < menu.size())
            break;
        else
            std::cout << "Invalid selection\n";
    }

    std::string user_choice;
    user_choice = menu[usr_choice_idx];

    int k = 0;
    while (true)
    {
        std::cout << "\r" << user_choice << ": "
                  << std::fixed << std::setprecision(2) << local_cache[user_choice]
                  << std::setw(5) << "C   "
                  << "(" << k++ << ")" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void init()
{
    // mut_remote.lock();
    remote_server.insert(std::make_pair("Sevilla", 26));
    remote_server.insert(std::make_pair("Dubai", 43));
    remote_server.insert(std::make_pair("Warsaw", -8));
    remote_server.insert(std::make_pair("Stuttgart", 7));
    remote_server.insert(std::make_pair("Sheffield", 12));
    // mut_remote.unlock();
    download_from_server(local_cache, remote_server, false);
}

int main()
{
    init();

    // server_worker simulates the process
    // that updates temperature measurements stored in the remote server
    // and their fluctuations at varying intervals
    std::thread server_worker(refresh_server_data, std::ref(remote_server));

    // retrieval worker is a background process that simulates the retrieval of
    // data from the server to the local cache with 4secs delay
    int NUM_THREADS = 10;
    std::vector<std::thread> retrieval_worker;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        retrieval_worker.push_back(std::thread(download_from_server,
                                               std::ref(local_cache),
                                               std::ref(remote_server),
                                               true));
        std::this_thread::sleep_for(std::chrono::milliseconds(2000 / NUM_THREADS));
    }

    // std::thread UI_worker(user_interface);
    user_interface();

    server_worker.join();

    // Join retrieval threads
    for (auto &item : retrieval_worker)
    {
        item.join();
    }

    return 0;
}