#ifndef USERDAO_H
#define USERDAO_H

#include <iostream>
#include <sqlite3.h>
#include "classes/User.h"

class UserDAO {
private:
    // Static member variable for the shared database connection
    static sqlite3 *db;

public:
    // Constructor and destructor to open and close the database connection
    UserDAO() {
        if (db == nullptr) {
            int rc = sqlite3_open("D:\\dsa_PROJ\\resources\\database.db", &db);
            if (rc != SQLITE_OK) {
                std::cout << "Error opening the database." << std::endl;
                sqlite3_close(db);
                db = nullptr; // Set db to nullptr to avoid using an invalid connection
            }
        }
    }

    ~UserDAO() {
        if (db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    void insert(std::string username, std::string userpassword) {
    try {
    if (db == nullptr) {
        std::cout << "Error: Database connection is not open.usl" << std::endl;
        return;
    }

    std::string count_query = "SELECT COUNT(*) FROM USERS";
    sqlite3_stmt* count_statement;

    int rc = sqlite3_prepare_v2(db, count_query.c_str(), -1, &count_statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cout << "Error preparing count statement." << std::endl;
        return;
    }

    rc = sqlite3_step(count_statement);
    int count;

    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(count_statement, 0);
    } else if (rc != SQLITE_DONE) {
        std::cout << "Error executing the count query.uso" << std::endl;
    }

    sqlite3_finalize(count_statement);

    std::string query_insert;

    if (count == 0) {
        query_insert = "INSERT INTO USERS (UserId, UserName, Password) VALUES (0, ?, ?)";
    } else {
        query_insert = "INSERT INTO USERS (UserId, UserName, Password) VALUES ((SELECT COALESCE(MAX(UserId), 0) + 1 FROM USERS), ?, ?)";
    }

    sqlite3_stmt* statement_insert;
    rc = sqlite3_prepare_v2(db, query_insert.c_str(), -1, &statement_insert, nullptr);
    if (rc != SQLITE_OK) {
        std::cout << "Error preparing insert statement." << std::endl;
        return;
    }

    // Bind parameters
    rc = sqlite3_bind_text(statement_insert, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_bind_text(statement_insert, 2, userpassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(statement_insert);

    if (rc != SQLITE_DONE) {
        std::cout << "Error executing insert statement: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "User inserted successfully." << std::endl;
    }

    sqlite3_finalize(statement_insert);
} catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
}

}

    bool is_unique(std::string username) {
       try {
        if (db == nullptr) {
            std::cout << "Error: Database connection is not open.us1" << std::endl;
            return false;
        }

        std::string query = "SELECT COUNT(*) FROM USERS WHERE UserName = ?";
        sqlite3_stmt* stmt_check;

        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt_check, nullptr);
        if (rc != SQLITE_OK) {
            std::cout << "Error preparing check statement for unique." << std::endl;
            return false;
        }

        // Bind parameter
        rc = sqlite3_bind_text(stmt_check, 1, username.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt_check);
        if (rc == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt_check, 0);

            if (count == 0) {
                std::cout << "Username is unique." << std::endl;
                return true;
            } else {
                std::cout << "Username is not unique." << std::endl;
                return false;
            }
        } else if (rc != SQLITE_DONE) {
            std::cout << "Error executing check query for unique." << std::endl;
            return false;
        }

        sqlite3_finalize(stmt_check);
        return false;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
        }
    }

vector<User> selectAllFromTable(void) {
    vector<User> users;
    try {
        if (db == nullptr) {
            cout << "Error: Database is not opened.us2" << endl;
            return users;  // Return an empty vector since there's an Error
        }

        string query = "SELECT * FROM USERS";
        sqlite3_stmt* statement;

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) == SQLITE_OK) {
            while (sqlite3_step(statement) == SQLITE_ROW) {
                int retrieveduserID = sqlite3_column_int(statement, 0);
                const char* usernameCStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
                std::string retrievedUsername(usernameCStr != nullptr ? usernameCStr : "");
                const char* passwordCStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
                std::string retrievedPassword(passwordCStr != nullptr ? passwordCStr : "");

                users.push_back(User(retrieveduserID, retrievedUsername, retrievedPassword));
            }

            sqlite3_finalize(statement);
        } else {
            cout << "Error: could not prepare select query." << endl;
            return users;  // Return an empty vector since there's an error
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return users;
}

int count() {
    if (db == nullptr) {
        cout << "Error: Database cannot be opened.us3" << endl;
        return -1;
    }

    string query = "SELECT COUNT(*) FROM Users";
    sqlite3_stmt* stmt;
    int count = -1;

    if (sqlite3_prepare(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }

        sqlite3_finalize(stmt);
    } else {
        cout << "Error preparing the count user query!" << endl;
    }

    return count;
}

        std::vector<std::string> getUsernamesFromIds(std::vector<int> userIDs) {
        std::vector<std::string> usernames;

        try {
            if (db == nullptr) {
                std::cout << "Error: Database connection is not open. us4" << std::endl;
                return usernames;  // Return an empty vector since there's an error
            }

            std::string query = "SELECT UserName FROM USERS WHERE UserId = ?";  // Assuming your table is named "USERS"
            sqlite3_stmt* statement;

            // Prepare the statement outside the loop
            if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
                std::cout << "Error: could not prepare select query." << std::endl;
                return usernames;  // Return an empty vector since there's an error
            }

            for (int userID : userIDs) {
                // Bind the parameter
                if (sqlite3_bind_int(statement, 1, userID) != SQLITE_OK) {
                    std::cout << "Error: could not bind parameter." << std::endl;
                    return usernames;  // Return an empty vector since there's an error
                }

                // Execute the statement
                int stepResult = sqlite3_step(statement);

                if (stepResult == SQLITE_ROW) {
                    const char* usernameCStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
                    std::string retrievedUsername(usernameCStr != nullptr ? usernameCStr : "");
                    usernames.push_back(retrievedUsername);
                } else if (stepResult != SQLITE_DONE) {
                    std::cout << "Error executing the select query." << std::endl;
                    return usernames;  // Return an empty vector since there's an error
                }

                // Reset the statement for the next iteration
                sqlite3_reset(statement);
            }

            // Finalize the statement after the loop
            sqlite3_finalize(statement);

        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        return usernames;
    }

};
#endif