#ifndef MST_H
#define MST_H

#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include "w_graph.h"

using namespace std;

struct Edge
{
    int weight;
    int u;
    int v;
};

bool operator>(const Edge &lhs, const Edge &rhs)
{
    return lhs.weight > rhs.weight;
}

template <class T>
using i_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int find(int i, vector<int> &parent)
{
    if (parent[i] == -1)
        return i;

    return parent[i] = find(parent[i], parent);
}

void Union(int rootI, int rootJ, vector<int> &parent, vector<int> &rank)
{
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
}

/**
 * @brief MST algorithm that finds the minimum spanning tree of a graph.
 * 
 * @param graph 
 * @return WGraph
 * 
 * @complexity O(E log V)
 */
WGraph mst(const WGraph &graph)
{
    int numVertices = graph.getNumVertices();
    vector<Edge> result;
    WGraph mst(numVertices);

    // Initialize parent and rank arrays
    vector<int> parent(numVertices, -1);
    vector<int> rank(numVertices, 1);

    // Priority queue to store edges sorted by weight
    i_priority_queue<Edge> pq;

    // Add all edges to the priority queue
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j : graph.getNeighbours(i))
        {
            int weight = graph.getWeight(i, j);
            pq.push({weight, i, j});
        }
    }

    // Process edges from the priority queue
    while (!pq.empty())
    {
        Edge edge = pq.top();
        pq.pop();

        // Check for a cycle
        int rootI = find(edge.u, parent);
        int rootJ = find(edge.v, parent);
        if (rootI != rootJ)
        {
            mst.addEdge(edge.u, edge.v, edge.weight);
            Union(rootI, rootJ, parent, rank);
        }
    }
    return mst;
}

#endif
