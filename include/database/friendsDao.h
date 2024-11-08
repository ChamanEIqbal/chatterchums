#ifndef FRIENDSDAO_H
#define FRIENDSDAO_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

class FriendsDAO {
private:
    static sqlite3* db;
public:
    FriendsDAO() {
        if(db == nullptr) {
            int rc = sqlite3_open("D:\\dsa_PROJ\\resources\\database.db", &db);
            if(rc != SQLITE_OK) {
                std::cout << "Error in opening db!" << std::endl;
                sqlite3_close(db);
                db = nullptr;
            }
        }
    }


    ~FriendsDAO() {
        if(db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }
        std::vector<std::string> getFriends(int user_id) {
            std::vector<std::string> usernames;
            
            // Check if the database is opened
            if (db == nullptr) {
                std::cout << "Error: Database is not opened! fdao 2" << std::endl;
                return usernames;
            }

            // SQL query to select usernames of friends
            std::string query = "SELECT u2.userName FROM FRIENDS F JOIN USERS u1 ON F.UserId1 = u1.userId JOIN USERS u2 ON F.UserId2 = u2.userId WHERE u1.userId = ?";

            sqlite3_stmt* stmt = nullptr;

            // Prepare the SQL statement
            if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {

                // Bind the user_id parameter to the statement
                sqlite3_bind_int(stmt, 1, user_id);

                // Execute the query
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    // Retrieve the username from the result set
                    const char* retrievedName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                    usernames.push_back(retrievedName);
                }

                // Finalize the statement
                sqlite3_finalize(stmt);

            } else {
                // Print an error message if preparation fails
                std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
                return usernames;
            }

            return usernames;
        }



        std::vector<int> getFriendIds(int user_id) {
            std::vector<int> userids;
            
            // Check if the database is opened
            if (db == nullptr) {
                std::cout << "Error: Database is not opened! fdao 3" << std::endl;
                return userids;
            }

            // SQL query to select usernames of friends
            std::string query = "SELECT u2.userId FROM FRIENDS F JOIN USERS u1 ON F.UserId1 = u1.userId JOIN USERS u2 ON F.UserId2 = u2.userId WHERE u1.userId = ?";

            sqlite3_stmt* stmt = nullptr;

            // Prepare the SQL statement
            if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {

                // Bind the user_id parameter to the statement
                sqlite3_bind_int(stmt, 1, user_id);

                // Execute the query
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    // Retrieve the username from the result set
                    int retrievedId = sqlite3_column_int(stmt, 0);
                    userids.push_back(retrievedId);
                }

                // Finalize the statement
                sqlite3_finalize(stmt);

            } else {
                // Print an error message if preparation fails
                std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
                return userids;
            }

            return userids;
        }

};

#endif