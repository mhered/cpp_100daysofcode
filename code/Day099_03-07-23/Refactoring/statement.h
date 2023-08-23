#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <locale>
#include <sstream>
#include <iomanip>

struct Performance
{
    std::string playID;
    int audience;
};

struct Play
{
    std::string name;
    std::string type;
};

struct Invoice
{
    std::string customer;
    std::vector<Performance> performances;
};

std::string usd(int numberCents)
{
    std::ostringstream formatted;
    formatted.imbue(std::locale("en_US.UTF-8"));
    formatted << "$" << std::fixed << std::setprecision(2) << numberCents / 100.0;
    return formatted.str();
}

Play &playFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    return plays[aPerformance.playID];
}

int amountFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    int result = 0;

    if (playFor(aPerformance, plays).type == "tragedy")
    {
        result = 40000;
        if (aPerformance.audience > 30)
        {
            result += 1000 * (aPerformance.audience - 30);
        }
    }
    else if (playFor(aPerformance, plays).type == "comedy")
    {
        result = 30000;
        if (aPerformance.audience > 20)
        {
            result += 10000 + 500 * (aPerformance.audience - 20);
        }
        result += 300 * aPerformance.audience;
    }
    else
    {
        throw std::runtime_error("unknown type: " + playFor(aPerformance, plays).type);
    }
    return result;
}

int volumeCreditFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    int result = std::max(aPerformance.audience - 30, 0);

    if (playFor(aPerformance, plays).type == "comedy")
        result += std::floor(aPerformance.audience / 5.0);
    return result;
}

int totalVolumeCredits(std::vector<Performance> performances,
                       std::map<std::string, Play> plays)
{
    int volumeCredits = 0;
    for (const Performance &perf : performances)
    {
        volumeCredits += volumeCreditFor(perf, plays);
    }
    return volumeCredits;
}

std::string statement(Invoice invoice, std::map<std::string, Play> plays)
{
    int totalAmount = 0;
    std::string result = "Statement for " + invoice.customer + "\n";

    for (const Performance &perf : invoice.performances)
    {
        // Print line for this order
        result += "  " + playFor(perf, plays).name + ": " + usd(amountFor(perf, plays)) +
                  " (" + std::to_string(perf.audience) + " seats)\n";
    }

    for (const Performance &perf : invoice.performances)
    {
        totalAmount += amountFor(perf, plays);
    }

    result += "Amount owed is " + usd(totalAmount) + "\n";
    result += "You earned " +
              std::to_string(totalVolumeCredits(invoice.performances, plays)) +
              " credits\n";
    return result;
}
