#ifndef TSP_H
#define TSP_H

#include <limits.h>
#include "w_graph.h"

using std::vector;

pair<int, vector<char>> tsp(WGraph graph, int start)
{
    int nVertexes = graph.getNumVertices();
    int parent[nVertexes];
    int min_cost = 0;
    WGraph mst(graph);
    int current = start;
    int next = start;
    int count = 0;

    vector<char> visited;

    char vertexToLetter[26];
    for (int i = 0; i < 26; ++i)
    {
        vertexToLetter[i] = static_cast<char>('A' + i);
    }

    while (count < nVertexes)
    {
        int min = INT_MAX;
        auto neighbours = mst.getNeighboursWithWeight(current);
        for (auto neighbour : neighbours)
        {
            if (neighbour.second < min)
            {
                min = neighbour.second;
                next = neighbour.first;
            }
        }
        min_cost += min;
        mst.setWeight(current, next, INT_MAX);
        mst.setWeight(next, current, INT_MAX);
        current = next;
        visited.push_back(vertexToLetter[current]);
        count++;
    }
    visited.push_back(vertexToLetter[start]);
    return {min_cost, visited};
}

#endif