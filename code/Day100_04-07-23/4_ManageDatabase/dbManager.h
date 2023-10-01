#ifndef DBMANAGER_H
#define DBMANAGER_H

#pragma once

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <sstream>

class Record
{
public:
    std::string link;
    std::string title;
    std::string comments;
    std::string sender;
    std::string date;
    std::vector<std::string> tags;
    Record(){};
    Record(std::string link,
           std::string title,
           std::string comments,
           std::string sender,
           std::string date,
           std::vector<std::string> tags) : link(link),
                                            title(title),
                                            comments(comments),
                                            sender(sender),
                                            date(date),
                                            tags(tags){};
    void display();
};

void Record::display()
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "Link: " << link << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Comments: " << comments << std::endl;
    std::cout << "Sender: " << sender << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Tags: ";
    std::string separator = "";

    for (const std::string &tag : tags)
    {
        std::cout << separator << tag;
        if (separator == "")
            separator = ", ";
    }
    std::cout << std::endl;
};

class dbManager
{
private:
    sqlite3 *db;
    bool createTable();
    bool isOpen();

public:
    dbManager(){};
    ~dbManager()
    {
        sqlite3_close(db);
    };

    bool init(const std::string &dbName);

    bool addRecord(const Record &record);

    bool updateRecord(int UID, const Record &record);
    bool updateRecord(std::string link, const Record &record);

    bool deleteRecord(const std::string &link);

    bool queryByLink(const std::string &link, Record &result);
    bool queryBySender(const std::string &sender, std::vector<Record> &results);
    bool queryByDateRange(const std::string &startDate,
                          const std::string &endDate,
                          std::vector<Record> &results);
    bool queryByTag(const std::string &tag, std::vector<Record> &results);
};

bool dbManager::createTable()
{
    const char *createTableSQL =
        "CREATE TABLE IF NOT EXISTS Records ("
        "   UID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   link TEXT NOT NULL UNIQUE,"
        "   title TEXT,"
        "   comments TEXT,"
        "   sender TEXT,"
        "   date_added DATE,"
        "   tags TEXT"
        ");";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        exit(1);
        return false;
    }
    return true;
}

bool dbManager::addRecord(const Record &record)
{
    Record retrieveRecord;
    if (queryByLink(record.link, retrieveRecord))
    {
        std::cerr << "Cannot add Record. Link \"" << record.link << "\" already exists in db" << std::endl;
        return false;
    }

    const char *insertSQL =
        "INSERT INTO Records (link, title, comments, sender, date_added, tags) VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, record.link.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, record.comments.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, record.sender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, record.date.c_str(), -1, SQLITE_STATIC);

    // Convert the tags vector into a comma-separated string
    std::string tagsStr;
    for (const std::string &tag : record.tags)
    {
        tagsStr += tag + ",";
    }
    if (!tagsStr.empty())
    {
        tagsStr.pop_back(); // Remove the trailing comma
    }

    sqlite3_bind_text(stmt, 6, tagsStr.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool dbManager::updateRecord(int UID, const Record &record)
{
    const char *updateSQL =
        "UPDATE Records SET link = ?, title = ?, comments = ?, sender = ?, date_added = ?, tags = ? WHERE UID = ?;";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, record.link.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, record.comments.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, record.sender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, record.date.c_str(), -1, SQLITE_STATIC);

    // Convert the tags vector into a comma-separated string
    std::string tagsStr;
    for (const std::string &tag : record.tags)
    {
        tagsStr += tag + ",";
    }
    if (!tagsStr.empty())
    {
        tagsStr.pop_back(); // Remove the trailing comma
    }

    sqlite3_bind_text(stmt, 6, tagsStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, UID);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool dbManager::updateRecord(std::string link, const Record &record)
{

    // 

    const char *updateSQL =
        "UPDATE Records SET title = ?, comments = ?, sender = ?, date_added = ?, tags = ? WHERE link = ?;";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, record.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.comments.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, record.sender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, record.date.c_str(), -1, SQLITE_STATIC);

    // Convert the tags vector into a comma-separated string
    std::string tagsStr;
    for (const std::string &tag : record.tags)
    {
        tagsStr += tag + ",";
    }
    if (!tagsStr.empty())
    {
        tagsStr.pop_back(); // Remove the trailing comma
    }

    sqlite3_bind_text(stmt, 5, tagsStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, record.link.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool dbManager::deleteRecord(const std::string &link)
{
    const char *deleteSQL = "DELETE FROM Records WHERE link = ?;";
    sqlite3_stmt *stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, link.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool dbManager::queryByLink(const std::string &link, Record &result)
{
    const char *querySQL = "SELECT * FROM Records WHERE link = ?;";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false; // Return false on error
    }

    sqlite3_bind_text(stmt, 1, link.c_str(), -1, SQLITE_STATIC);

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        result.link = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        result.title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        result.comments = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        result.sender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        result.date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

        // Parse the tags field into a vector of strings
        const char *tagsStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::istringstream iss(tagsStr);
        std::string tag;
        while (std::getline(iss, tag, ','))
        {
            result.tags.push_back(tag);
        }

        sqlite3_finalize(stmt);
        return true; // Return true when the record is found
    }

    sqlite3_finalize(stmt);
    return false; // Return false if no matching record is found
}

bool dbManager::queryBySender(const std::string &sender, std::vector<Record> &results)
{
    const char *querySQL = "SELECT * FROM Records WHERE sender = ?;";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false; // Return false on error
    }

    sqlite3_bind_text(stmt, 1, sender.c_str(), -1, SQLITE_STATIC);

    bool found = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        found = true; // Set found to true since at least one record is found

        Record result;
        result.link = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        result.title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        result.comments = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        result.sender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        result.date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

        // Parse the tags field into a vector of strings
        const char *tagsStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::istringstream iss(tagsStr);
        std::string tag;
        while (std::getline(iss, tag, ','))
        {
            result.tags.push_back(tag);
        }

        results.push_back(result);
    }

    sqlite3_finalize(stmt);
    return found; // Return true if at least one record is found, false otherwise
}

bool dbManager::queryByDateRange(const std::string &startDate,
                                 const std::string &endDate,
                                 std::vector<Record> &results)
{

    const char *querySQL = "SELECT * FROM Records WHERE date_added BETWEEN ? AND ? ORDER BY date_added ASC;";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false; // Return false on error
    }

    sqlite3_bind_text(stmt, 1, startDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, endDate.c_str(), -1, SQLITE_STATIC);
    bool found = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        found = true; // Set found to true since at least one record is found

        Record result;
        result.link = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        result.title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        result.comments = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        result.sender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        result.date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

        // Parse the tags field into a vector of strings
        const char *tagsStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::istringstream iss(tagsStr);
        std::string tag;
        while (std::getline(iss, tag, ','))
        {
            result.tags.push_back(tag);
        }

        results.push_back(result);
    }

    sqlite3_finalize(stmt);
    return found; // Return true if at least one record is found, false otherwise
}

bool dbManager::queryByTag(const std::string &tag, std::vector<Record> &results)
{
    const char *querySQL = "SELECT * FROM Records WHERE tags LIKE ?;";

    // Construct a search pattern to find the tag within the comma-separated list
    std::string searchPattern = "%" + tag + "%";

    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false; // Return false on error
    }

    sqlite3_bind_text(stmt, 1, searchPattern.c_str(), -1, SQLITE_STATIC);

    bool found = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        found = true; // Set found to true since at least one record is found

        Record result;
        result.link = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        result.title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        result.comments = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        result.sender = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        result.date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

        // Parse the tags field into a vector of strings
        const char *tagsStr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::istringstream iss(tagsStr);
        std::string tagStr;
        while (std::getline(iss, tagStr, ','))
        {
            result.tags.push_back(tagStr);
        }

        results.push_back(result);
    }

    sqlite3_finalize(stmt);
    return found; // Return true if at least one record is found, false otherwise
}

bool dbManager::init(const std::string &dbName)
{
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc)
    {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
        return false;
    }

    if (createTable())
        return true;
    else
        return false;
}

bool dbManager::isOpen()
{
    return db != nullptr;
}

#endif