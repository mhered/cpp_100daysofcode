#include <iostream>
#include <locale>
#include <sstream>
#include <iomanip>

#include "createStatementData.h"

std::string usd(int numberCents)
{
    std::ostringstream formatted;
    formatted.imbue(std::locale("en_US.UTF-8"));
    formatted << "$" << std::fixed << std::setprecision(2) << numberCents / 100.0;
    return formatted.str();
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

    result += "Amount owed is " + usd(data.totalAmount) + "\n";
    result += "You earned " +
              std::to_string(data.totalVolumeCredits) +
              " credits\n";
    return result;
}



std::string statement(Invoice invoice, std::map<std::string, Play> plays)
{
    return renderPlainText(createStatementData(invoice, plays));
}
