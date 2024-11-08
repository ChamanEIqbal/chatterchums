#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include "Post.h"
using namespace std;


class User {

public:
    User(int userId, string userName, string Password) : id(userId), name(userName), m_password(Password) {} // constructor
    int id;
    string name;
    string m_password;

    User() {} // default constructor
};

#endif