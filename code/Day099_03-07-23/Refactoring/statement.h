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

std::string formatCurrency(double amount)
{
    std::ostringstream formatted;
    formatted.imbue(std::locale("en_US.UTF-8"));
    formatted << "$" << std::fixed << std::setprecision(2) << amount;
    return formatted.str();
}

Play &playFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    return plays[aPerformance.playID];
}

double amountFor(Performance aPerformance,std::map<std::string, Play> plays )
{
    double result = 0;
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

std::string statement(Invoice invoice, std::map<std::string, Play> plays)
{
    double totalAmount = 0;
    int volumeCredits = 0;
    std::string result = "Statement for " + invoice.customer + "\n";

    for (const Performance &perf : invoice.performances)
    {
        double thisAmount = amountFor( perf, plays);

        // Add volume credits
        volumeCredits += std::max(perf.audience - 30, 0);
        // Add extra credit for every ten comedy attendees
        if (playFor(perf, plays).type == "comedy")
            volumeCredits += std::floor(perf.audience / 5.0);

        // Print line for this order
        result += "  " + playFor(perf, plays).name + ": " + formatCurrency(thisAmount / 100.0) +
                  " (" + std::to_string(perf.audience) + " seats)\n";
        totalAmount += thisAmount;
    }

    result += "Amount owed is " + formatCurrency(totalAmount / 100.0) + "\n";
    result += "You earned " + std::to_string(volumeCredits) + " credits\n";
    return result;
}
