#include <gtest/gtest.h>
#include <gmock/gmock.h> // For nice value comparison

#include "statement.h" // Include the file containing the code

// Define a custom matcher to compare currency strings
MATCHER_P(CurrencyEq, expected, "Currency equality matcher") {
    return (std::abs(std::stod(arg) - std::stod(expected)) < 0.01);
}

// Test fixture for the statement function
class StatementTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test data
        playData = {
            {"hamlet", {"Hamlet", "tragedy"}},
            {"as-like", {"As You Like It", "comedy"}},
            {"othello", {"Othello", "tragedy"}}
        };
    }

    // Helper function to create a Performance
    Performance createPerformance(const std::string& playID, int audience) {
        Performance perf;
        perf.playID = playID;
        perf.audience = audience;
        return perf;
    }

    // Helper function to create an Invoice
    Invoice createInvoice(const std::string& customer, const std::vector<Performance>& performances) {
        Invoice invoice;
        invoice.customer = customer;
        invoice.performances = performances;
        return invoice;
    }

    std::map<std::string, Play> playData;
};


// This test is the original test case from the book
TEST_F(StatementTest, OriginalStatement) {
    Invoice invoice = createInvoice("Customer A", {
        createPerformance("hamlet", 55),
        createPerformance("as-like", 35),
        createPerformance("othello", 40)
    });
    std::string statementResult = statement(invoice, playData);
    std::string expectedStatement = "Statement for Customer A\n  Hamlet: $650.00 (55 seats)\n  As You Like It: $580.00 (35 seats)\n  Othello: $500.00 (40 seats)\nAmount owed is $1,730.00\nYou earned 47 credits\n";
    EXPECT_EQ(statementResult, expectedStatement);
}

// The following tests are new tests that I added to test the code more thoroughly
TEST_F(StatementTest, SingleTragedyStatement) {
    Invoice invoice = createInvoice("Customer B", {createPerformance("hamlet", 60)});
    std::string statementResult = statement(invoice, playData);
    std::string expectedStatement = "Statement for Customer B\n  Hamlet: $700.00 (60 seats)\nAmount owed is $700.00\nYou earned 30 credits\n";
    EXPECT_EQ(statementResult, expectedStatement);
}

TEST_F(StatementTest, SingleComedyStatement) {
    Invoice invoice = createInvoice("Customer C", {createPerformance("as-like", 40)});
    std::string statementResult = statement(invoice, playData);
    std::string expectedStatement = "Statement for Customer C\n  As You Like It: $620.00 (40 seats)\nAmount owed is $620.00\nYou earned 18 credits\n";
    EXPECT_EQ(statementResult, expectedStatement);
}

TEST_F(StatementTest, MultiplePerformancesStatement) {
    Invoice invoice = createInvoice("Customer D", {
        createPerformance("hamlet", 20),
        createPerformance("as-like", 40),
        createPerformance("othello", 15)
    });
    std::string statementResult = statement(invoice, playData);
    std::string expectedStatement = "Statement for Customer D\n  Hamlet: $400.00 (20 seats)\n  As You Like It: $620.00 (40 seats)\n  Othello: $400.00 (15 seats)\nAmount owed is $1,420.00\nYou earned 18 credits\n";
    EXPECT_EQ(statementResult, expectedStatement);
}

// Test that the statement function throws an exception when given an unknown play type
TEST_F(StatementTest, SingleUnknownPlayTypeStatement) {
    Invoice invoice = createInvoice("Customer E", {createPerformance("unknown-play", 25)});
    EXPECT_THROW(statement(invoice, playData), std::runtime_error);
}

// Test that the statement function returns a void statement when given an empty list of plays
TEST_F(StatementTest, EmptyInvoiceStatement) {
    Invoice invoice = createInvoice("Customer F", {});
    std::string statementResult = statement(invoice, playData);
    std::string expectedStatement = "Statement for Customer F\nAmount owed is $0.00\nYou earned 0 credits\n";
    EXPECT_EQ(statementResult, expectedStatement);
}
// Test that the formatCurrency function formats currency correctly
TEST(FormatCurrencyTest, Formatting) {
    EXPECT_EQ(formatCurrency(100.0), "$100.00");
    EXPECT_EQ(formatCurrency(1234.5678), "$1,234.57");
    EXPECT_EQ(formatCurrency(0.123), "$0.12");
}

// Test that the usd function formats currency correctly
TEST(CentsToUSDTest, Formatting) {
    EXPECT_EQ(usd(10000), "$100.00");
    EXPECT_EQ(usd(123457), "$1,234.57");
    EXPECT_EQ(usd(12), "$0.12");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}