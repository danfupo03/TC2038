#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>
#include <numeric>
#include "w_graph.h"

using namespace std;
class Kruskal
{
public:
    vector<pair<int, pair<int, int>>> kruskalMST(const WGraph &graph);
    vector<pair<int, pair<int, int>>> MST(const WGraph &graph);
};

vector<pair<int, pair<int, int>>> Kruskal::kruskalMST(const WGraph &graph)
{
    int numVertices = graph.getNumVertices();
    vector<pair<int, pair<int, int>>> result;

    // Helper function to find the root of a set
    auto find = [&](int i, vector<int> &parent)
    {
        while (parent[i] != i)
            i = parent[i];
        return i;
    };

    // Helper function to perform union of two sets
    auto Union = [&](int i, int j, vector<int> &parent, vector<int> &rank)
    {
        int rootI = find(i, parent);
        int rootJ = find(j, parent);

        if (rootI != rootJ)
        {
            if (rank[rootI] < rank[rootJ])
                parent[rootI] = rootJ;
            else if (rank[rootI] > rank[rootJ])
                parent[rootJ] = rootI;
            else
            {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
        }
    };

    // Initialize parent and rank arrays
    vector<int> parent(numVertices);
    iota(parent.begin(), parent.end(), 0);

    vector<int> rank(numVertices, 0);

    // Priority queue to store edges sorted by weight
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // Add all edges to the priority queue
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j : graph.getNeighbours(i))
        {
            int weight = graph.getWeight(i, j);
            pq.push({weight, {i, j}});
        }
    }

    // Process edges from the priority queue
    while (!pq.empty())
    {
        int weight = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();

        // Check for a cycle
        if (find(u, parent) != find(v, parent))
        {
            result.push_back({weight, {u, v}});
            Union(u, v, parent, rank);
        }
    }

    return result;
}

vector<pair<int, pair<int, int>>> Kruskal::MST(const WGraph &graph)
{
    return kruskalMST(graph);
}

