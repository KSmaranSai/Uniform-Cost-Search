#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string>> romaniaMap;
static int id;

class Node
{
public:
    int node_id;
    string current_city;
    int priority_value;

    Node(string current_city, int priority_value)
    {
        this->current_city = current_city;
        this->priority_value = priority_value;
        this->node_id = id++;
    }

    bool operator<(const Node &p) const
    {
        return this->priority_value > p.priority_value;
    }
};

void bfs(string startingNode, string destinationNode)
{
    unordered_map<string, bool> visited;
    unordered_map<string, string> reached;

    priority_queue<Node> frontier;

    for (const auto &entry : romaniaMap)
    {
        const string &city = entry.first;
        visited[city] = false;
        reached[city] = "";
    }

    const string &startingCity = startingNode;
    visited[startingCity] = true;
    frontier.push(Node(startingNode, 0));

    while (!frontier.empty())
    {
        Node u = frontier.top();
        frontier.pop();

        for (string v : romaniaMap[u.current_city])
        {
            if (!visited[v])
            {
                visited[v] = true;
                reached[v] = u.current_city;
                if (v == destinationNode)
                {
                    break;
                }

                frontier.push(Node(v, u.priority_value + 1));
            }
        }
    }

    string g = destinationNode;
    vector<string> path;
    while (!g.empty())
    {
        path.push_back(g);
        g = reached[g];
    }

    reverse(path.begin(), path.end());

    for (string city : path)
    {
        if (city == destinationNode)
        {
            cout << city;
        }
        else{
            cout << city << "-> ";
        }
    }
    cout << endl;
}

int main()
{
    romaniaMap = {
        {"Arad", {"Sibiu", "Zerind", "Timisoara"}},
        {"Zerind", {"Arad", "Oradea"}},
        {"Oradea", {"Zerind", "Sibiu"}},
        {"Sibiu", {"Arad", "Oradea", "Fagaras", "Rimnicu"}},
        {"Timisoara", {"Arad", "Lugoj"}},
        {"Lugoj", {"Timisoara", "Mehadia"}},
        {"Mehadia", {"Lugoj", "Drobeta"}},
        {"Drobeta", {"Mehadia", "Craiova"}},
        {"Craiova", {"Drobeta", "Rimnicu", "Pitesti"}},
        {"Rimnicu", {"Sibiu", "Craiova", "Pitesti"}},
        {"Fagaras", {"Sibiu", "Bucharest"}},
        {"Pitesti", {"Rimnicu", "Craiova", "Bucharest"}},
        {"Bucharest", {"Fagaras", "Pitesti", "Giurgiu", "Urziceni"}},
        {"Giurgiu", {"Bucharest"}},
        {"Urziceni", {"Bucharest", "Vaslui", "Hirsova"}},
        {"Hirsova", {"Urziceni", "Eforie"}},
        {"Eforie", {"Hirsova"}},
        {"Vaslui", {"Iasi", "Urziceni"}},
        {"Iasi", {"Vaslui", "Neamt"}},
        {"Neamt", {"Iasi"}}};

    bfs("Arad", "Bucharest");
    return 0;
}
