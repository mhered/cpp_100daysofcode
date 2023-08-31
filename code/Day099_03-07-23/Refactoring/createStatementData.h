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

class PerformanceCalculator
{
public:
    PerformanceCalculator(Performance aPerformance, Play aPlay)
        : performance(aPerformance),
          play(aPlay)
    {
    }
    Performance performance;
    Play play;

    virtual int amount();
    int volumeCredits();
};

int PerformanceCalculator::volumeCredits()
{
    int result = std::max(performance.audience - 30, 0);

    if (play.type == "comedy")
        result += std::floor(performance.audience / 5.0);
    return result;
}

int PerformanceCalculator::amount()
{
    int result = 0;

    if (play.type == "tragedy")
    {
        throw std::runtime_error("this is bad: superclass should not be called");
    }
    else if (play.type == "comedy")
    {
        result = 30000;
        if (performance.audience > 20)
        {
            result += 10000 + 500 * (performance.audience - 20);
        }
        result += 300 * performance.audience;
    }
    else
    {
        throw std::runtime_error("unknown type: " + play.type);
    }
    return result;
}

class TragedyCalculator : public PerformanceCalculator
{
    using PerformanceCalculator::PerformanceCalculator;
public:
    int amount()
    {
        int result = 40000;
        if (performance.audience > 30)
        {
            result += 1000 * (performance.audience - 30);
        }

        return result;
    };
};

class ComedyCalculator : public PerformanceCalculator
{
    using PerformanceCalculator::PerformanceCalculator;
};

int totalAmount(Statement data)
{
    return std::accumulate(data.enrichedperformances.begin(),
                           data.enrichedperformances.end(), 0,
                           [](int total, const EnrichedPerformance &perf)
                           {
                               return total + perf.amount;
                           });
}

int totalVolumeCredits(Statement data)
{
    return std::accumulate(data.enrichedperformances.begin(),
                           data.enrichedperformances.end(), 0,
                           [](int total, const EnrichedPerformance &perf)
                           {
                               return total + perf.volumeCredits;
                           });
}

Play &playFor(Performance aPerformance, std::map<std::string, Play> plays)
{
    return plays[aPerformance.playID];
}

PerformanceCalculator *createPerformanceCalculator(
    Performance aPerformance,
    Play aPlay)
{
    if (aPlay.type == "tragedy")
    {
        return new TragedyCalculator(aPerformance, aPlay);
    }
    else if (aPlay.type == "comedy")
    {
        return new ComedyCalculator(aPerformance, aPlay);
    }
    else
    {
        throw std::runtime_error("unknown type: " + aPlay.type);
    }
};

EnrichedPerformance enrichPerformance(Performance aPerformance,
                                      std::map<std::string, Play> plays)
{
    EnrichedPerformance result;
    PerformanceCalculator *calculator = createPerformanceCalculator(
        aPerformance,
        playFor(aPerformance, plays));
    result.performance = aPerformance;
    result.play = calculator->play;
    result.amount = calculator->amount();
    result.volumeCredits = calculator->volumeCredits();
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