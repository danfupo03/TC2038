#ifndef W_GRAPH_H
#define W_GRAPH_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class WGraph
{
public:
    WGraph(int n);
    WGraph(const WGraph &other);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    int getWeight(int u, int v) const;
    void setWeight(int u, int v, int w);
    int getNumEdges() const;
    int getNumVertices() const;
    vector<int> getNeighbours(int) const;
    vector<pair<int, int>> getNeighboursWithWeight(int) const;
    std::string toString() const;

private:
    int numVertices;
    int numEdges;
    vector<vector<int>> matrix;
};

WGraph::WGraph(int n)
{
    numVertices = n;
    numEdges = 0;
    matrix = vector<vector<int>>(n, vector<int>(n, 0));
}

WGraph::WGraph(const WGraph &other)
{
    numVertices = other.numVertices;
    numEdges = other.numEdges;
    matrix = vector<vector<int>>(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            matrix[i][j] = other.matrix[i][j];
}

void WGraph::addEdge(int u, int v, int w)
{
    if (matrix[u][v] == 0)
    {
        numEdges++;
    }
    matrix[u][v] = w;
}

void WGraph::removeEdge(int u, int v)
{
    if (matrix[u][v] != 0)
    {
        numEdges--;
    }
    matrix[u][v] = 0;
}

bool WGraph::hasEdge(int u, int v) const
{
    return matrix[u][v] != 0;
}

int WGraph::getWeight(int u, int v) const
{
    return matrix[u][v];
}

void WGraph::setWeight(int u, int v, int w)
{
    matrix[u][v] = w;
}

int WGraph::getNumEdges() const
{
    return numEdges;
}

int WGraph::getNumVertices() const
{
    return numVertices;
}

vector<int> WGraph::getNeighbours(int i) const
{
    std::vector<int> neighbours;
    for (int j = 0; j < numVertices; j++)
        if (matrix[i][j] != 0)
            neighbours.push_back(j);

    return neighbours;
}

vector<pair<int, int>> WGraph::getNeighboursWithWeight(int i) const
{
    vector<pair<int, int>> neighbours;

    for (int j = 0; j < numVertices; j++)
        if (matrix[i][j] != 0)
            neighbours.push_back({j, matrix[i][j]});

    return neighbours;
}

string WGraph::toString() const
{
    std::stringstream ss;
    ss << "WGraph: " << numVertices << " vertices, " << numEdges << " edges\n";

    for (int i = 0; i < numVertices; i++)
    {
        ss << "\t" << i + 1;
    }
    for (int i = 0; i < numVertices; i++)
    {
        ss << "\n"
           << i + 1;
        for (int j = 0; j < numVertices; j++)
        {
            ss << "\t" << matrix[i][j];
        }
    }
    return ss.str();
}

#endif
