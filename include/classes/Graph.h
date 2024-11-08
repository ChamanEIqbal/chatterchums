#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "database/friendsDao.h"
#include "database/userDao.h"
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph
{
private:
    unordered_map<int, vector<int>> m_graph;

public:
    Graph() {}

    unordered_map<int, vector<int>>& getGraphMember() { return m_graph; }

    void setVals() {
        FriendsDAO dao_friends;
        UserDAO dao_user;
        int count = dao_user.count();

        for(int i = 0; i < count; i++) {
            vector<int> connectedids = dao_friends.getFriendIds(i);
            m_graph[i] = connectedids;
        }
    }

       vector<int> bfsRecommendation(int startUserId, int numRecommendations, const unordered_map<int, vector<int>>& graph)
    {
        vector<int> recommendedIds;
        unordered_set<int> visited;

        queue<int> q;
        q.push(startUserId);
        visited.insert(startUserId);

        while (!q.empty() && recommendedIds.size() < numRecommendations)
        {
            int currentUserId = q.front();
            q.pop();

            for (int connectedUserId : graph.at(currentUserId))  // Use the provided graph parameter
            {
                if (visited.find(connectedUserId) == visited.end())
                {
                    q.push(connectedUserId);
                    visited.insert(connectedUserId);

                    recommendedIds.push_back(connectedUserId);
                    if (recommendedIds.size() == numRecommendations)
                    {
                        break;
                    }
                }
            }
        }

        return recommendedIds;
    }

    
    vector<int> dfsRecommendation(int startUserId, int numRecommendations)
    {
        vector<int> recommendedIds;
        unordered_set<int> visited;

        stack<int> s;
        s.push(startUserId);
        visited.insert(startUserId);

        while (!s.empty() && recommendedIds.size() < numRecommendations)
        {
            int currentUserId = s.top();
            s.pop();

            for (int connectedUserId : m_graph[currentUserId])
            {
                if (visited.find(connectedUserId) == visited.end())
                {
                    s.push(connectedUserId);
                    visited.insert(connectedUserId);

                    recommendedIds.push_back(connectedUserId);
                    if (recommendedIds.size() == numRecommendations)
                    {
                        break;
                    }
                }
            }
        }

        return recommendedIds;
    }
};

#endif
