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

struct EnrichedPerformance
{
    Performance performance;
    Play play;
    int amount;
    int volumeCredits;
};

struct Statement
{
    std::string customer;
    std::vector<EnrichedPerformance> enrichedperformances;
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

int amountFor(EnrichedPerformance aPerformance)
{
    int result = 0;

    if (aPerformance.play.type == "tragedy")
    {
        result = 40000;
        if (aPerformance.performance.audience > 30)
        {
            result += 1000 * (aPerformance.performance.audience - 30);
        }
    }
    else if (aPerformance.play.type == "comedy")
    {
        result = 30000;
        if (aPerformance.performance.audience > 20)
        {
            result += 10000 + 500 * (aPerformance.performance.audience - 20);
        }
        result += 300 * aPerformance.performance.audience;
    }
    else
    {
        throw std::runtime_error("unknown type: " + aPerformance.play.type);
    }
    return result;
}

int volumeCreditFor(EnrichedPerformance aPerformance)
{
    int result = std::max(aPerformance.performance.audience - 30, 0);

    if (aPerformance.play.type == "comedy")
        result += std::floor(aPerformance.performance.audience / 5.0);
    return result;
}

int totalVolumeCredits(Statement data)
{
    int result = 0;
    for (const EnrichedPerformance &perf : data.enrichedperformances)
    {
        result += volumeCreditFor(perf);
    }
    return result;
}

int totalAmount(Statement data)
{
    int result = 0;
    for (const EnrichedPerformance &perf : data.enrichedperformances)
    {
        result += amountFor(perf);
    }

    return result;
}

std::string renderPlainText(Statement data)
{
    std::string result = "Statement for " + data.customer + "\n";

    for (const EnrichedPerformance &perf : data.enrichedperformances)
    {
        // Print line for this order
        result += "  " + perf.play.name + ": " + usd(perf.amount) +
                  " (" + std::to_string(perf.performance.audience) + " seats)\n";
    }

    result += "Amount owed is " + usd(totalAmount(data)) + "\n";
    result += "You earned " +
              std::to_string(totalVolumeCredits(data)) +
              " credits\n";
    return result;
}

EnrichedPerformance enrichPerformance(Performance aPerformance,
                                                    std::map<std::string, Play> plays)
{
        EnrichedPerformance result;
        result.performance = aPerformance;
        result.play = playFor(aPerformance, plays);
        result.amount = amountFor(result);
        result.volumeCredits = volumeCreditFor(result);
    return result;
}

std::string statement(Invoice invoice, std::map<std::string, Play> plays)
{
    Statement statementData;
    statementData.customer = invoice.customer;

    for (const Performance &perf : invoice.performances)
    {
        statementData.enrichedperformances.push_back(enrichPerformance(perf, plays));
    }

    return renderPlainText(statementData);
}
