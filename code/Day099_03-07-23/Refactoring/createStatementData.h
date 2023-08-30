#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cmath>

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

struct EnrichedPerformance
{
    Performance performance;
    Play play;
    int amount;
    int volumeCredits;
};

struct Invoice
{
    std::string customer;
    std::vector<Performance> performances;
};

struct Statement
{
    std::string customer;
    std::vector<EnrichedPerformance> enrichedperformances;
    int totalAmount;
    int totalVolumeCredits;
};

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

int totalAmount(Statement data)
{
    return std::accumulate(data.enrichedperformances.begin(),
                           data.enrichedperformances.end(), 0,
                           [](int total, const EnrichedPerformance &perf)
                           {
                               return total + amountFor(perf);
                           });
}

int totalVolumeCredits(Statement data)
{
    return std::accumulate(data.enrichedperformances.begin(),
                           data.enrichedperformances.end(), 0,
                           [](int total, const EnrichedPerformance &perf)
                           {
                               return total + volumeCreditFor(perf);
                           });
}

Play &playFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    return plays[aPerformance.playID];
}

class PerformanceCalculator
{
private:
    Performance performance;
public:
    PerformanceCalculator(Performance aPerformance)
        : performance(aPerformance)
    {
    }

}; 

EnrichedPerformance enrichPerformance(Performance aPerformance,
                                        std::map<std::string, Play> plays)
{
    EnrichedPerformance result;
    PerformanceCalculator calculator(aPerformance);
    result.performance = aPerformance;
    result.play = playFor(aPerformance, plays);
    result.amount = amountFor(result);
    result.volumeCredits = volumeCreditFor(result);
    return result;
}

Statement createStatementData(Invoice invoice, std::map<std::string, Play> plays)
{
    Statement result;
    result.customer = invoice.customer;

    for (const Performance &perf : invoice.performances)
    {
        result.enrichedperformances.push_back(enrichPerformance(perf, plays));
    }
    result.totalAmount = totalAmount(result);
    result.totalVolumeCredits = totalVolumeCredits(result);
    return result;
}