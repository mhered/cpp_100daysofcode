#include <iostream>
#include <vector>
#include <chrono>

// recursive function that counts how many different combinations of the elements in
// the `coins` array can make change to the amount `target` using brute force
// use `verbose = true` to print trace messages that help understand the search
// `index` is an internal variable that tracks position in the coins array during recursion, defaults to 0
// `depth` is an internal variable used to keep track of the depth of recursion, defaults to 0

int coinsCombinations_brute(int target, std::vector<int> coins, bool verbose = false, uint index = 0, uint depth = 0)
{
    int combinations = 0;
    if (verbose)
        std::cout << std::string(depth, '-') << "Searching combinations for " << target << "€" << std::endl;
    if (!target)
    {
        if (verbose)
            std::cout << std::string(depth, '-') << "Combination found!" << std::endl;
        return 1; // if target=0 then 1 combination is possible: selecting no more coins
    }
    // loop over remaining coins
    for (uint i = index; i < coins.size(); i++)
    {
        if (verbose)
            std::cout << std::string(depth, '-') << "Can I use the " << coins[i] << "€ coin as change for " << target << "€?" << std::endl;
        // if a coin is smaller than the target amount it can be used for change
        if (coins[i] <= target)
        {
            if (verbose)
                std::cout << std::string(depth, '-') << "Yes" << std::endl;
            // call recursively and add result
            combinations += coinsCombinations_brute(target - coins[i], coins, verbose, i, ++depth);
        }
        else
        {
            if (verbose)
                std::cout << std::string(depth, '-') << "No" << std::endl;
        }
    }
    if (verbose)
        std::cout << std::string(depth, '-') << "Found a total " << combinations << " combinations for " << target << "€" << std::endl;
    return combinations;
}

int coinsCombinations_topdown_dp(int target,
                                 std::vector<int> coins,
                                 std::vector<std::vector<int>> &dp,
                                 bool verbose = false,
                                 uint index = 0)
{

    if (!target)
    {
        return 1; // if target=0 then 1 combination is possible: selecting no more coins
    }

    if (index == coins.size() || target < 0)
    {
        return 0; // what is this?
    }

    // LookUp in Dp Array
    if (dp[index][(uint)target] != -1)
    {
        return dp[index][(uint)target];
    }

    // pick next coin
    int pick = coinsCombinations_topdown_dp(target - coins[index], coins, dp, verbose, index);
    int non_pick = coinsCombinations_topdown_dp(target, coins, dp, verbose, index + 1);
    return dp[index][(uint)target] = pick + non_pick;
}

int coinsCombinations_bottomup_dp(int target,
                                  std::vector<int> coins,
                                  bool verbose = false)
{
    // Bottom Up DP approach
    // Form dp array - each element will store the number of combinations to reach it
    std::vector<int> dp((uint)target + 1, 0); // initialize with 0s
    // if target=0 there is 1 combination (i.e. not selecting any coin)
    dp[0] = 1;

    // Count coin change combinations
    // for each coin, compute the number of ways to reach each possible target amount j between 1 and target
    // by either not including the current coin or including it once, twice, three times, etc.

    for (uint i = 0; i < coins.size(); i++) // for each coin
    {
        for (uint j = 1; j < dp.size(); j++) // for each j between 1 and target
        {
            if (j < (uint)coins[i])
                continue;                    // skip if coin is too big
            dp[j] += dp[j - (uint)coins[i]]; // increment dp[j] with the number of combinations from j - coin
            if (verbose)
                std::cout << "Updated dp[" << j << "] = " << dp[j] << std::endl;
        }
    }
    return dp[dp.size() - 1];
}

void timed_fun(int target, std::vector<int> coins, bool verbose, char algorithm)
{
    int combinations;
    // Timestamp the start of the code
    auto beg = std::chrono::high_resolution_clock::now();

    switch (algorithm)
    {
    case 'f':
    {
        std::cout << "Brute force: " << std::flush;
        combinations = coinsCombinations_brute(target, coins, verbose);
        std::cout << combinations << " combinations" << std::flush; //  11
    }
    break;

    case 't':
    {
        std::cout << "Top Down dp: " << std::flush;
        std::vector<std::vector<int>> dp(coins.size(), std::vector<int>((uint)target + 1, -1));
        combinations = coinsCombinations_topdown_dp(target, coins, dp, verbose);
        std::cout << combinations << " combinations" << std::flush; //  11
    }
    break;
    case 'b':
    {
        std::cout << "Bottom Up dp: " << std::flush;
        std::vector<std::vector<int>> dp(coins.size(), std::vector<int>((uint)target + 1, -1));
        combinations = coinsCombinations_bottomup_dp(target, coins, verbose);
        std::cout << combinations << " combinations" << std::flush; //  11
    }
    break;
    }

    // Timestamp after the code is ran
    auto end = std::chrono::high_resolution_clock::now();

    // Subtract the timestamps and cast the differenc to microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

    // Display the elapsed time
    std::cout << " (Elapsed Time: " << duration.count() << " microseconds)" << std::endl;
}

int main()
{
    timed_fun(4, {1, 2}, false, 'f'); // 3
    timed_fun(4, {1, 2}, false, 't'); // 3
    timed_fun(4, {1, 2}, false, 'b'); // 3
    std::cout << std::endl;

    timed_fun(10, {5, 2, 3}, false, 'f'); //  4
    timed_fun(10, {5, 2, 3}, false, 't'); //  4
    timed_fun(10, {5, 2, 3}, false, 'b'); //  4
    std::cout << std::endl;

    timed_fun(11, {5, 7}, false, 'f'); //  0
    timed_fun(11, {5, 7}, false, 't'); //  0
    timed_fun(11, {5, 7}, false, 'b'); //  0
    std::cout << std::endl;

    timed_fun(219, {2, 5, 10, 20, 50}, false, 'f'); // 1859
    timed_fun(219, {2, 5, 10, 20, 50}, false, 't'); // 1859
    timed_fun(219, {2, 5, 10, 20, 50}, false, 'b'); // 1859
    std::cout << std::endl;

    timed_fun(419, {2, 5, 10, 20, 50}, false, 'f'); // 18515
    timed_fun(419, {2, 5, 10, 20, 50}, false, 't'); // 18515
    timed_fun(419, {2, 5, 10, 20, 50}, false, 'b'); // 18515
    std::cout << std::endl;

    timed_fun(11, {1, 2, 5}, false, 'f'); // 11
    timed_fun(11, {1, 2, 5}, false, 't'); // 11
    timed_fun(11, {1, 2, 5}, false, 'b'); // 11
    std::cout << std::endl;

    timed_fun(37, {1, 2, 5, 10}, false, 'f'); // 160
    timed_fun(37, {1, 2, 5, 10}, false, 't'); // 160
    timed_fun(37, {1, 2, 5, 10}, false, 'b'); // 160
    std::cout << std::endl;

    timed_fun(317, {1, 2, 5, 10, 50}, false, 'f'); // 125146
    timed_fun(317, {1, 2, 5, 10, 50}, false, 't'); // 125146
    timed_fun(317, {1, 2, 5, 10, 50}, false, 'b'); // 125146
    std::cout << std::endl;

    return 0;
}