#include "database/friendsDao.h"
#include "database/userDao.h"

#include "classes/Graph.h"

sqlite3* FriendsDAO::db = nullptr;
sqlite3* UserDAO::db = nullptr;


using namespace std;
int main() {

    Graph graph;

    graph.setVals();
    vector<int> ids = graph.bfsRecommendation(0, 15, graph.getGraphMember());

    for(int id : ids) {
        cout << id << endl;
    } 


    system("pause");
    return 0;
}