#include <iostream>
#include <sqlite3.h>
#include <string>

// callback allows to get output from SELECT operation
/* Prototype:
typedef int (*sqlite3_callback)(
void*, // Data provided in the 4th argument of sqlite3_exec()
int, // The number of columns in row
char**, // An array of strings representing fields in the row
char** // An array of strings representing column names
);
*/

static int callback(void *data, int argc, char **argv, char **azColName)

{
    //printf("%s\n", (const char *)data); // uncomment to show data
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("--------------------\n");

    return 0;
}




int main(int argc, char **argv)
{
    // open database
    sqlite3 *DB; // declare DB object
    std::string filename = "example.db"; // name of database file

    const char *data = "Callback function called"; // a string to pass to callback
    char *error_msg;     // a string to store error messages

    // open or create a database, returns 0 on success
    if (sqlite3_open(filename.c_str(), &DB) != 0)
    {
        std::cerr << "\nERROR - Could not open Database \"" << filename 
        <<"\": "<< sqlite3_errmsg(DB) << std::endl;
        return -1;
    }
    else
        std::cout << "\nSUCCESS - Database is open\n"
                  << std::endl;

    // create a table

    // Declare the SQL query to create a table
    std::string query = "CREATE TABLE IF NOT EXISTS PERSON ("
                        "ID INT PRIMARY KEY     NOT NULL, "
                        "NAME           TEXT    NOT NULL, "
                        "SURNAME        TEXT, "
                        "AGE            INT     NOT NULL, "
                        "ADDRESS        CHAR(50), "
                        "SALARY         REAL );";

    // execute SQL query to create a table, returns SQLITE_OK on success

    if (sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg) != SQLITE_OK)
    {
        std::cerr << "\nSQL ERROR - Table not created: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
    else
        std::cout << "\nSUCCESS - Table exists\n" << std::endl;

    // query status of DB before insertion
    std::cout << "\nSTATE OF TABLE BEFORE INSERT\n" << std::endl;
    query = "SELECT * FROM PERSON "
            "ORDER BY ID ASC;";
    sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg);

    // Insert 5 records

    query = "INSERT OR IGNORE INTO PERSON (ID,NAME,AGE,ADDRESS,SALARY) "
            "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "
            "INSERT OR IGNORE INTO PERSON (ID,NAME,AGE,ADDRESS,SALARY) "
            "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "
            "INSERT OR IGNORE INTO PERSON (ID,NAME,AGE,ADDRESS,SALARY)"
            "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"
            "INSERT OR IGNORE INTO PERSON (ID,NAME,AGE,ADDRESS,SALARY)"
            "VALUES (4, 'Mark', 25, 'RichMond ', 65000.00 );"
            "INSERT OR IGNORE INTO PERSON (ID,NAME,AGE,ADDRESS,SALARY)"
            "VALUES (5, 'Louis', 28, 'Reykjavik', 43000.00 );";

    if (sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg) != SQLITE_OK)
    {
        std::cerr << "\nSQL ERROR - Records not inserted: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
    else
        std::cout << "\nSUCCESS - Records inserted\n" << std::endl;

    std::cout << "\nSTATE OF TABLE AFTER INSERTION\n" << std::endl;
    query = "SELECT * FROM PERSON "
            "ORDER BY ID ASC;";
    sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg);

   // Update 4 records

    query = "UPDATE PERSON SET "
    "SURNAME = 'Armstrong' WHERE NAME = 'Louis';"
    "UPDATE PERSON SET "
    "SURNAME = 'Anthony' WHERE NAME = 'Mark';"
    "UPDATE PERSON SET "
    "SURNAME = 'McCartney' WHERE NAME = 'Paul';";

    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &error_msg) != SQLITE_OK)
    {
        std::cerr << "\nSQL ERROR - Records not updated: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
    else
        std::cout << "\nSUCCESS - Records updated\n" << std::endl;

    std::cout << "\nSTATE OF TABLE AFTER UPDATE\n" << std::endl;
    query = "SELECT * FROM PERSON "
               "ORDER BY ID ASC;";
     sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg);

   // Delete 2 records

    query = "DELETE FROM PERSON WHERE ID IN (2,3);";
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &error_msg) != SQLITE_OK)
    {
        std::cerr << "\nSQL ERROR - Records not deleted: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
    else
        std::cout << "\nSUCCESS - Records deleted\n" << std::endl;

    std::cout << "\nSTATE OF TABLE AFTER DELETION\n" << std::endl;
    query = "SELECT * FROM PERSON "
               "ORDER BY ID ASC;";
     sqlite3_exec(DB, query.c_str(), callback, (void *)data, &error_msg);

    // close table
    sqlite3_close(DB);

    return 0;
}