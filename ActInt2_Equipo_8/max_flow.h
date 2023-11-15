#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include <limits.h>
#include <queue>
#include <iostream>
#include "w_graph.h"

using namespace std;

bool bfs(WGraph rGraph, int start, int end, int parent[])
{
    int nVertexes = rGraph.getNumVertices();
    bool visited[nVertexes];
    for (int i = 0; i < rGraph.getNumVertices(); ++i)
        visited[i] = false;

    queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        auto neighbours = rGraph.getNeighboursWithWeight(current);
        for (auto neighbour : neighbours)
        {
            if (visited[neighbour.first] == false && neighbour.second > 0)
            {
                if (neighbour.first == end)
                {
                    parent[neighbour.first] = current;
                    return true;
                }
                q.push(neighbour.first);
                parent[neighbour.first] = current;
                visited[neighbour.first] = true;
            }
        }
    }
    return false;
}

pair<int, WGraph> fordFulkerson(WGraph graph, int start, int end)
{
    int nVertexes = graph.getNumVertices();
    WGraph rGraph(graph);
    int parent[nVertexes];
    int max_flow = 0;

    while (bfs(rGraph, start, end, parent))
    {
        int path_flow = INT_MAX;
        int current = end;
        while (current != start)
        {
            int u = parent[current];
            path_flow = min(path_flow, rGraph.getWeight(u, current));
            current = parent[current];
        }

        current = end;
        while (current != start)
        {
            int u = parent[current];
            rGraph.setWeight(u, current, rGraph.getWeight(u, current) - path_flow);
            rGraph.setWeight(current, u, rGraph.getWeight(current, u) + path_flow);
            current = parent[current];
        }

        max_flow += path_flow;
    }
    return {max_flow, rGraph};
}

#endif