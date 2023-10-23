#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "w_graph.h"

using namespace std;

/**
 * @brief Stuct que representa uma visita a um nodo
 */
typedef struct Visit
{
    int previousNode;
    int distance;
};

/**
 * @brief Sobrecarga do operador < para o struct Visit
 */
bool operator<(const Visit &lhs, const Visit &rhs)
{
    return lhs.distance < rhs.distance;
}

/**
 * @brief Sobrecarga do operador == para o struct Visit
 */
bool operator==(const Visit &lhs, const Visit &rhs)
{
    return lhs.distance == rhs.distance && lhs.previousNode == rhs.previousNode;
}

map<int, Visit> dijkstra(const int, const WGraph);

int main()
{

    cout << "Numero de vertices: ";
    int n;
    cin >> n;

    WGraph g(n);

    cout << "\nMatriz de adjacencias: " << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int w;
            cin >> w;
            if (w != -1)
            {
                g.addEdge(i, j, w);
            }
        }
    }

    cout << g.toString() << endl;
    map<int, Visit> res;
    cout << "Dijkstra: " << endl;
    for (int i = 0; i < n; i++)
    {
        res = dijkstra(i, g);
        cout << "From " << i + 1 << ":" << endl;
        for (auto node : res)
        {
            int numberAux = node.first + 1;

            if (node.second.distance == 0)
                continue;

            if (node.second.distance == INT_MAX)
            {
                cout << numberAux << ": "
                     << "infinito" << endl;
                continue;
            }

            cout << numberAux << ": " << node.second.distance << endl;
        }
    }

    cout << "FIN" << endl;
    return 0;
}

map<int, Visit> dijkstra(const int start, const WGraph graph)
{
    map<int, Visit> visits;
    const int n_vertex = graph.getNumVertices();
    set<int> unvisited;
    for (int i = 0; i < n_vertex; i++)
    {
        if (i == start)
        {
            visits[i] = {i, 0};
            continue;
        }

        visits[i] = {-1, INT_MAX};
        unvisited.insert(i);
    }

    int current = start;
    while (unvisited.size() > 0)
    {
        unvisited.erase(current);
        auto neighbours = graph.getNeighbours(current);
        for (auto neighbour : neighbours)
        {
            int currentDistance = visits[current].distance;
            if (currentDistance == INT_MAX)
                continue;

            int prevDistance = visits[neighbour].distance;
            int newDistance = graph.getWeight(current, neighbour) + currentDistance;

            if (newDistance < prevDistance)
                visits[neighbour] = {current, newDistance};
        }
        current = *unvisited.begin();
        for (auto node : unvisited)
        {
            if (visits[node].distance < visits[current].distance)
            {
                current = node;
            }
        }
    }
    return visits;
}
