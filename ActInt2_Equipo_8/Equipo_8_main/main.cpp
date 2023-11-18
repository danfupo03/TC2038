#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "mst.h"
#include "tsp.h"
#include "max_flow.h"
#include "nearest_neighbour.h"

using namespace std;

int main()
{
    cout << "Number of vertices: ";
    int nVertexes;
    cin >> nVertexes;

    WGraph graph(nVertexes);

    cout << "\nAdjacency Matrix of Distances: " << endl;

    for (int i = 0; i < nVertexes; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < nVertexes; j++)
        {
            int weight;
            cin >> weight;
            if (weight != -1)
            {
                graph.addEdge(i, j, weight);
            }
        }
    }

    cout << "Input Graph of Distances:\n"
         << graph.toString() << endl;

    auto mstGraph = mst(graph);

    cout << "\nMST:\n"
         << mstGraph.toString() << endl;

    auto tspAns = tsp(graph, 0);

    cout << "\nCosto mínimo: " << tspAns.first << endl;
    cout << "Recorrido más eficiente: ";
    for (auto i : tspAns.second)
        cout << i << " ";
    cout << endl;

    WGraph graph2(nVertexes);
    cout << "\nAdjacency Matrix of Max throughput: " << endl;

    for (int i = 0; i < nVertexes; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < nVertexes; j++)
        {
            int weight;
            cin >> weight;
            if (weight != -1)
            {
                graph2.addEdge(i, j, weight);
            }
        }
    }

    cout << "Input Graph of Max throughput:\n"
         << graph2.toString() << endl;

    auto ans = fordFulkerson(graph2, 0, nVertexes - 1);
    cout << "Max Flow: " << ans.first << endl;

    cout << "Residual Graph: " << endl;
    cout << ans.second.toString() << endl;

    cout << "Nearset Neighbour: " << endl;
    vector<pair<int, int>> points(nVertexes);

    for (int i = 0; i < nVertexes; i++)
    {
        cout << "Point " << i + 1 << ": ";
        string buffer;
        // parse (###, ###) into numbers
        cin >> buffer;
        buffer = buffer.substr(1, buffer.size() - 2);
        int comma = buffer.find(',');
        points[i].first = stoi(buffer.substr(0, comma));
        points[i].second = stoi(buffer.substr(comma + 1, buffer.size() - comma - 1));
    }    

    cout << "Targuet: ";
    string buffer;
    // parse (###, ###) into numbers
    cin >> buffer;
    buffer = buffer.substr(1, buffer.size() - 2);
    int comma = buffer.find(',');
    pair<int, int> targuet;
    targuet.first = stoi(buffer.substr(0, comma));
    targuet.second = stoi(buffer.substr(comma + 1, buffer.size() - comma - 1));

    auto ans2 = nearest_neighbour(points, targuet);

    cout << "Nearest Neighbour: " << ans2.first << ", " << ans2.second << endl;

    return 0;
}