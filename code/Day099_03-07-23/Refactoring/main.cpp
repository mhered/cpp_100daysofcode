//#include <iostream>

#include <string>
#include <map>

//#include <vector>

//#include <cmath>
//#include <locale>
//#include <sstream>
//#include <iomanip>

#include <fstream>
#include <nlohmann/json.hpp>  // to read JSON files

#include "statement.h"

int main() {

    // Read plays from JSON
    std::ifstream playsFile("plays.json");
    nlohmann::json playsJson;
    playsFile >> playsJson;

    // Read invoice from JSON
    std::ifstream invoicesFile("invoices.json");
    nlohmann::json invoicesJson;
    invoicesFile >> invoicesJson;

    // Convert JSON to C++ data structures
    std::map<std::string, Play> plays;
    for (const auto& entry : playsJson.items()) {
        plays[entry.key()] = {entry.value()["name"], entry.value()["type"]};
    }

    // Process each invoice
    for (const auto& invoiceEntry : invoicesJson) {
        Invoice invoice;
        invoice.customer = invoiceEntry["customer"];
        for (const auto& perf : invoiceEntry["performances"]) {
            invoice.performances.push_back({perf["playID"], perf["audience"]});
        }

        // Generate and print the statement for each invoice
        std::string statementResult = statement(invoice, plays);
        std::cout << statementResult << std::endl;
    }

    return 0;
}