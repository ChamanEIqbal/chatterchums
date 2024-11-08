#ifndef POSTDAO_H
#define POSTDAO_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include "Classes/Post.h"
class PostDAO{
private:
    static sqlite3* db;
public:
    PostDAO() {
        if (db == nullptr) {
            int rc = sqlite3_open("D:\\dsa_PROJ\\resources\\database.db", &db);
            if(rc != SQLITE_OK) {
                cout << "Error: Cannot open the database." << endl;
                sqlite3_close(db);
                db = nullptr;
            }
        }
    }

    ~PostDAO() {
        if(db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    void insert(Post post) {
         if (db == nullptr) {
        std::cout << "Error: Database is currently not opened. p1" << std::endl;
        return;
    }

    try {
        std::string count_query = "SELECT COUNT(*) FROM POSTS";
        sqlite3_stmt* count_statement;

        int rc = sqlite3_prepare_v2(db, count_query.c_str(), -1, &count_statement, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Error: cannot prepare count statement.");
        }

        int count;
        rc = sqlite3_step(count_statement);
        if (rc == SQLITE_ROW) {
            count = sqlite3_column_int(count_statement, 0);
        } else if (rc != SQLITE_DONE) {
            throw std::runtime_error("Error: cannot execute count statement.");
        }

        sqlite3_finalize(count_statement);

        std::string insert_query;
        sqlite3_stmt* insert_statement;
        if (count == 0) {
            insert_query = "INSERT INTO POSTS (ID, Author, Text, Date) VALUES (0, ?, ?, ?)";
        } else {
            insert_query = "INSERT INTO POSTS (ID, Author, Text, Date) VALUES ((SELECT COALESCE(MAX(ID), 0) + 1 FROM POSTS), ?, ?, ?)";
        }

        rc = sqlite3_prepare_v2(db, insert_query.c_str(), -1, &insert_statement, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Error: cannot prepare the insert query statement.");
        }

        // Bind parameters
        rc = sqlite3_bind_text(insert_statement, 1, post.m_author.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_bind_text(insert_statement, 2, post.m_text.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_bind_text(insert_statement, 3, post.m_date.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(insert_statement);
        if (rc != SQLITE_DONE) {
            std::cout << "Error executing insert statement: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Post inserted successfully." << std::endl;
        }

        sqlite3_finalize(insert_statement);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

    vector<Post> selectPostByAuthor(std::string username) {
        vector<Post> posts;
        if(db == nullptr) {
            cout << "Error: Database is not openend. p2" << endl;
            sqlite3_close(db);
            return posts; // return null
        }

        try {
            string query = "SELECT * FROM POSTS WHERE Author = ' " + username + " ' ";
            sqlite3_stmt* statement;
            if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) == SQLITE_OK) {
                
                while(sqlite3_step(statement) == SQLITE_ROW) {
                int retrievedPostID = sqlite3_column_int(statement, 0);
                string retrievedAuthor = username; // as it is
                string retrievedText = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
                string retrievedDate = reinterpret_cast<const char*>(sqlite3_column_text(statement,3));

                Post post(retrievedText, retrievedPostID, retrievedAuthor, retrievedDate);
                posts.push_back(post);

                }
                sqlite3_finalize(statement);
                return posts;
            } else {
                cout << "Error: could not prepare the statement for getting post by author." << endl;
                sqlite3_close(db);
                return posts;
            }

        } catch(const std::exception &e) {
            cout << "Exception: " << e.what() << endl;
        }

        return posts;
    }
    
    vector<Post> selectAllFromDatabase(void) {
        vector<Post> posts;
        if(db == nullptr) {
            cout << "Error: Database is not opened. p3" << endl;
            sqlite3_close(db);
            db = nullptr;
            return posts;
        }

        try {

        string query = "SELECT * FROM POSTS";
        sqlite3_stmt* statement;

        if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr) == SQLITE_OK) {
            while(sqlite3_step(statement) == SQLITE_ROW) {
                int retrievedPostID = sqlite3_column_int(statement, 0);
                string retrievedAuthor = reinterpret_cast<const char*>(sqlite3_column_text(statement,1));
                string retrievedText = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
                string retrievedDate = reinterpret_cast<const char*>(sqlite3_column_text(statement,3));

                Post post(retrievedText, retrievedPostID, retrievedAuthor, retrievedDate);
                posts.push_back(post);
            }

            sqlite3_finalize(statement);

        } else {
            cout << "Error in preparing the select all post from database query." << endl;
            sqlite3_close(db);
            db = nullptr;
            return posts;
        }


    } catch (const std::exception &e) {
        cout << "Exception: " << e.what() << endl; 
        }

        return posts;
    }
};
#endif