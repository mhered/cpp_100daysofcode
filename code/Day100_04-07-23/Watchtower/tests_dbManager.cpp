#include "dbManager.h"
#include <cstdio>
#include <gtest/gtest.h>

// Define a test fixture class
class dbManagerTest : public ::testing::Test
{
protected:
    // Create an instance of your dbManager
    dbManager manager; // Open a database connection
    // This function will be called before each test
    void SetUp() override
    {
        manager.init("test_db.db");
        Record testRecord1("https://example.com", "Example 1", "A sample page", "Sender1", "2023-08-08", {"sample", "page"});
        Record testRecord2("https://example2.com", "Example 2", "Another sample page", "Sender1", "2023-08-09", {"another", "sample", "page"});
        Record testRecord3("https://example3.com", "Example 3", "One more sample page", "Sender1", "2023-09-02", {"sample", "page", "more"});
        Record testRecord4("https://example4.com", "Example 4", "Yet another sample page", "Sender2", "2023-09-01", {"yet", "another", "sample", "page"});
        Record testRecord5("https://example5.com", "Example 5", "One sample page more", "Sender2", "2023-09-02", {"one", "more", "sample", "page"});
        Record testRecord6("https://example6.com", "Example 6", "Keep'em coming sample pages", "Sender3", "2023-09-04", {"sample"});

        // add the testRecords to the database
        manager.addRecord(testRecord1);
        manager.addRecord(testRecord2);
        manager.addRecord(testRecord3);
        manager.addRecord(testRecord4);
        manager.addRecord(testRecord5);
        manager.addRecord(testRecord6);
    }

    // This function will be called after each test
    void TearDown() override
    {
        // Close the database connection
        // You may want to clean up the test database file
        std::remove("test_db.db");
    }
};

// Test the addRecord() method
TEST_F(dbManagerTest, AddRecordTest)
{
    // create a Record
    Record addedRecord("https://example-added.com", "Added Example7", "A new page", "Sender1", "2023-09-10", {"new", "page"});

    // add the record
    manager.addRecord(addedRecord);

    // check record exists
    Record retrievedRecord;
    bool queryResult = manager.queryByLink("https://example-added.com", retrievedRecord);

    // Check if the query was successful
    ASSERT_TRUE(queryResult);

    // Check if the retrieved record matches the test record
    ASSERT_EQ(retrievedRecord.link, addedRecord.link);
    ASSERT_EQ(retrievedRecord.title, addedRecord.title);
    ASSERT_EQ(retrievedRecord.comments, addedRecord.comments);
    ASSERT_EQ(retrievedRecord.sender, addedRecord.sender);
    ASSERT_EQ(retrievedRecord.date, addedRecord.date);
    ASSERT_EQ(retrievedRecord.tags, addedRecord.tags);
}

// Test the updateRecord(UID, Record) method
TEST_F(dbManagerTest, UpdateRecordByUIDTest)
{
    // retrieve a record
    Record testRecord;
    bool queryResult = manager.queryByLink("https://example.com", testRecord);

    // update fields
    testRecord.link = "https://example-updated.com";
    testRecord.title = "Updated Example1";
    testRecord.comments = "An updated page";
    testRecord.sender = "Sender1";
    testRecord.date = "2023-09-10";
    testRecord.tags = {"updated", "page"};

    // put updated record in the db
    ASSERT_TRUE(manager.updateRecord(1, testRecord));

    Record retrievedRecord;
    // attempt to retrieve Record by the original link should fail
    queryResult = manager.queryByLink("https://example.com", retrievedRecord);
    ASSERT_FALSE(queryResult);

    // Check query is successful with updated link
    queryResult = manager.queryByLink("https://example-updated.com", retrievedRecord);
    ASSERT_TRUE(queryResult);

    // Check if the retrieved record matches the test record
    ASSERT_EQ(retrievedRecord.link, testRecord.link);
    ASSERT_EQ(retrievedRecord.title, testRecord.title);
    ASSERT_EQ(retrievedRecord.comments, testRecord.comments);
    ASSERT_EQ(retrievedRecord.sender, testRecord.sender);
    ASSERT_EQ(retrievedRecord.date, testRecord.date);
    ASSERT_EQ(retrievedRecord.tags, testRecord.tags);
}

// Test the updateRecord(link, Record) method
TEST_F(dbManagerTest, UpdateRecordByLinkTest)
{
    // retrieve a record
    Record testRecord;
    bool queryResult = manager.queryByLink("https://example.com", testRecord);

    // update fields
    testRecord.title = "Updated Example1";
    testRecord.comments = "An updated page";
    testRecord.sender = "Sender1";
    testRecord.date = "2023-09-10";
    testRecord.tags = {"updated", "page"};

    // put updated record in the db
    ASSERT_TRUE(manager.updateRecord("https://example.com", testRecord));

    Record retrievedRecord;
    // retrieve Record by link after update
    queryResult = manager.queryByLink("https://example.com", retrievedRecord);
    ASSERT_TRUE(queryResult);

    // Check if the retrieved record matches the test record
    ASSERT_EQ(retrievedRecord.title, testRecord.title);
    ASSERT_EQ(retrievedRecord.comments, testRecord.comments);
    ASSERT_EQ(retrievedRecord.sender, testRecord.sender);
    ASSERT_EQ(retrievedRecord.date, testRecord.date);
    ASSERT_EQ(retrievedRecord.tags, testRecord.tags);
}

// Test the deleteRecord() method
TEST_F(dbManagerTest, DeleteRecordTest)
{
    // check record exists in db
    Record testRecord;
    bool queryResult;

    queryResult = manager.queryByLink("https://example.com", testRecord);

    ASSERT_TRUE(queryResult);

    // delete record from db
    ASSERT_TRUE(manager.deleteRecord("https://example.com"));

    // attempt to retrieve Record after deletion should fail
    queryResult = manager.queryByLink("https://example.com", testRecord);
    ASSERT_FALSE(queryResult);
}

// Test the queryBySender() method, none found
TEST_F(dbManagerTest, QueryBySenderNoneTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryBySender("Sender4", testRecords);

    ASSERT_FALSE(queryResult);
}

// Test the queryBySender() method, one found
TEST_F(dbManagerTest, QueryBySenderOneTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryBySender("Sender3", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 1);
    ASSERT_EQ(testRecords[0].title, "Example 6");
}

// Test the queryBySender() method, many found
TEST_F(dbManagerTest, QueryBySenderManyTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryBySender("Sender2", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 2);
    ASSERT_EQ(testRecords[0].title, "Example 4");
    ASSERT_EQ(testRecords[1].title, "Example 5");
}

// Test the queryByDateRange() method, invalid input
TEST_F(dbManagerTest, QueryByDateRangeInvalidTest)
{
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByDateRange("InvalidDate", "InvalidDate", testRecords);
    ASSERT_FALSE(queryResult);
    // Check that the vector is empty
    EXPECT_TRUE(testRecords.empty());
}

// Test the queryByDateRange() method, none found
TEST_F(dbManagerTest, QueryByDateRangeNoneTest)
{
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByDateRange("2023-09-05", "2023-09-08", testRecords);

    ASSERT_FALSE(queryResult);
    // Check that the vector is empty
    EXPECT_TRUE(testRecords.empty());
}

// Test the queryByDateRange() method, one found
TEST_F(dbManagerTest, queryByDateRangeOneTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByDateRange("2023-09-04", "2023-09-04", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 1);
    ASSERT_EQ(testRecords[0].title, "Example 6");
}

// Test the queryByDateRange() method, many found
TEST_F(dbManagerTest, queryByDateRangeManyTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByDateRange("2023-08-20",
                                           "2023-09-09", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 4);

    ASSERT_EQ(testRecords[0].title, "Example 4");
    ASSERT_EQ(testRecords[1].title, "Example 3");
    ASSERT_EQ(testRecords[2].title, "Example 5");
    ASSERT_EQ(testRecords[3].title, "Example 6");
}

// Test the queryByTag() method, none found
TEST_F(dbManagerTest, QueryByTagNoneTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByTag("none", testRecords);

    ASSERT_FALSE(queryResult);

    ASSERT_TRUE(testRecords.empty());
}

// Test the queryByTag() method, one found
TEST_F(dbManagerTest, QueryByTagOneTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByTag("one", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 1);
    ASSERT_EQ(testRecords[0].title, "Example 5");
}

// Test the queryByTag() method, many found
TEST_F(dbManagerTest, QueryByTagManyTest)
{
    // check record exists in db
    std::vector<Record> testRecords;
    bool queryResult;

    queryResult = manager.queryByTag("sample", testRecords);

    ASSERT_TRUE(queryResult);

    ASSERT_EQ(testRecords.size(), 6);
    ASSERT_EQ(testRecords[0].title, "Example 1");
    ASSERT_EQ(testRecords[1].title, "Example 2");
    ASSERT_EQ(testRecords[2].title, "Example 3");
    ASSERT_EQ(testRecords[3].title, "Example 4");
    ASSERT_EQ(testRecords[4].title, "Example 5");
    ASSERT_EQ(testRecords[5].title, "Example 6");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*

// original main with a crude testing
int main()
{
    dbManager watchtowerDB("test.db");

    // Add records
    watchtowerDB.addRecord(Record("http://example.com", "Example 1", "A sample page", "Sender1", "2023-08-08", {"sample", "page"}));
    watchtowerDB.addRecord(Record("http://example2.com", "Example 2", "Another sample page", "Sender1", "2023-08-09", {"another", "sample", "page"}));
    watchtowerDB.addRecord(Record("http://example3.com", "Example 3", "One more sample page", "Sender1", "2023-09-01", {"sample", "page", "more"}));
    watchtowerDB.addRecord(Record("http://example4.com", "Example 4", "Yet another sample page", "Sender2", "2023-09-02", {"yet", "another", "sample", "page"}));
    watchtowerDB.addRecord(Record("http://example5.com", "Example 5", "One sample page more", "Sender2", "2023-09-02", {"one", "more", "sample", "page"}));
    watchtowerDB.addRecord(Record("http://example6.com", "Example 6", "Keep'em coming sample pages", "Sender3", "2023-09-04", {"sample"}));

    // Update a record
    watchtowerDB.updateRecord(1, Record("http://example-updated.com", "Updated Example1", "An updated page", "Sender1", "2023-09-10", {"updated", "sample", "page"}));

    std::cout << "------------------------------" << std::endl;
    std::cout << "--Query by link=example5.com--" << std::endl;

    // Query by link
    Record linkResult;
    if (watchtowerDB.queryByLink("http://example5.com", linkResult))
        linkResult.display();

    std::cout << "--------------------" << std::endl;
    std::cout << "--Query by Sender2--" << std::endl;
    // Query by sender
    std::vector<Record> recordsBySender;
    if (watchtowerDB.queryBySender("Sender2", recordsBySender))
    {
        for (auto &item : recordsBySender)
        {
            item.display();
        }
    }
    else
    {
        std::cout << "No records found" << std::endl;
    }

    // Query by date range
    std::cout << "---------------------------" << std::endl;
    std::cout << "--Query by Dates 20/8-9/9--" << std::endl;

    std::vector<Record> recordsByDateRange;
    if (watchtowerDB.queryByDateRange("2023-08-20",
                                      "2023-09-09",
                                      recordsByDateRange))
    {
        for (auto &item : recordsByDateRange)
        {
            item.display();
        }
    }
    else
    {
        std::cout << "No records found" << std::endl;
    }

    // Delete a record
    watchtowerDB.deleteRecord("http://example6.com");

    // Query by tag
    std::cout << "---------------------" << std::endl;
    std::cout << "--Query by Tag: one--" << std::endl;

    std::vector<Record> recordsByTag;
    if (watchtowerDB.queryByTag("one", recordsByTag))
    {
        for (auto &item : recordsByTag)
        {
            item.display();
        }
    }
    else
    {
        std::cout << "No records found" << std::endl;
    }

    // std::remove("test2.db");

    return 0;
}
*/