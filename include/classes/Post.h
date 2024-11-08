#ifndef POST_H
#define POST_H

#include <string>
#include <chrono>
#include <ctime>
using namespace std;

class Post {
    public:
    Post(string text, int id, string author) : m_text(text), m_id(id), m_author(author) {
        //initializing today's date as m_date.

        auto now = std::chrono::system_clock::now();

        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        m_date = std::ctime(&currentTime);
        m_date.pop_back(); // removing \n from string
    }

    Post(string text, int id, string author, string date) : m_text(text), m_id(id), m_author(author), m_date(date) {}


    string m_text;
    int m_id;
    string m_author;
    string m_date;
};

#endif