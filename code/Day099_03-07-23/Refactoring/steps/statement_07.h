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

std::string renderHtml(Statement data)
{
    std::string result = "<h1>Statement for " + data.customer + "</h1>\n";
    result += "<table>\n";

    result += "<tr><th>play</th><th>seats</th><th>cost</th></tr>\n";

    for (const EnrichedPerformance &perf : data.enrichedperformances)
    {
        // Print line for this order
        result += "<tr>";
        result += "<td>" + perf.play.name + "</td>";
        result += "<td>" + std::to_string(perf.performance.audience) + "</td>";
        result += "<td>" + usd(perf.amount) + "</td>";
        result += "</tr>\n";
    }
    result += "</table>\n";

    result += "<p>Amount owed is <em>" + usd(data.totalAmount) + "</em></p>\n";
    result += "<p>You earned <em>" +
              std::to_string(data.totalVolumeCredits) +
              "</em> credits</p>\n";
    return result;
}

std::string htmlStatement(Invoice invoice, std::map<std::string, Play> plays)
{
    return renderHtml(createStatementData(invoice, plays));
}