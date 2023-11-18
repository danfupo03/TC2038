#ifndef TSP_H
#define TSP_H

#include <limits.h>
#include "w_graph.h"
#include <algorithm>

using std::vector;

/**
 * @brief TSP algorithm that finds the shortest path that visits all the nodes.
 * 
 * @param graph 
 * @param s 
 * @return pair<int, vector<char>> 
 * 
 * @complexity O(n!)
 */
pair<int, vector<char>> tsp(WGraph graph, int s)
{
    vector<int> vertex;
    for (int i = 0; i < graph.getNumVertices(); i++)
        if (i != s)
            vertex.push_back(i);

    int minCost = INT_MAX;
    vector<char> minPath;

    do
    {
        int currentCost = 0;
        vector<char> path = {static_cast<char>('A' + s)};
        int k = s;

        for (int i = 0; i < vertex.size(); i++)
        {
            currentCost += graph.getWeight(k, vertex[i] - 1);
            k = vertex[i];
            path.push_back(static_cast<char>('A' + vertex[i]));
        }
        currentCost += graph.getWeight(k, s - 1);

        if (currentCost < minCost)
        {
            minCost = currentCost;
            minPath = path;
        }

    } while (next_permutation(vertex.begin(), vertex.end()));

    return {minCost, minPath};
}

#endif