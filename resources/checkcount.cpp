#include "database/userDao.h"

sqlite3* UserDAO::db = nullptr;

#include <iostream>
using namespace std;

int main() {

    UserDAO dao;
    vector<int> ids = {0,1,2,3,4};
    vector<string> names = dao.getUsernamesFromIds(ids);

    int count = dao.count();


    for(string name : names) {
        cout << name << endl;
    }

    cout << count << endl;

    system("pause");
    return 0;
}