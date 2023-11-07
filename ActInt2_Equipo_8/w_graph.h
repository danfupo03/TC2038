#include <sstream>
#include <string>
#include <vector>

using std::vector;

class WGraph
{
public:
    WGraph(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    int getWeight(int u, int v) const;
    void setWeight(int u, int v, int w);
    int getNumEdges() const;
    int getNumVertices() const;
    vector<int> getNeighbours(int) const;
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
    matrix = vector<vector<int>>(n, vector<int>(n, -1));
}

void WGraph::addEdge(int u, int v, int w)
{
    if (matrix[u][v] == -1)
    {
        numEdges++;
    }
    matrix[u][v] = w;
}

void WGraph::removeEdge(int u, int v)
{
    if (matrix[u][v] != -1)
    {
        numEdges--;
    }
    matrix[u][v] = -1;
}

bool WGraph::hasEdge(int u, int v) const
{
    return matrix[u][v] != -1;
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

std::vector<int> WGraph::getNeighbours(int i) const
{
    std::vector<int> neighnours;
    for (int j = 0; j < numVertices; j++)
    {
        if (matrix[i][j] != -1)
        {
            neighnours.push_back(j);
        }
    }
    return neighnours;

}

std::string WGraph::toString() const
{
    std::stringstream ss;
    ss << "WGraph: " << numVertices << " vertices, " << numEdges << " edges\n";

    for (int i = 0; i < numVertices; i++)
    {
        ss << "\t" << i + 1;
    }
    for (int i = 0; i < numVertices; i++)
    {
        ss << "\n" << i + 1;
        for (int j = 0; j < numVertices; j++)
        {
            ss << "\t" << matrix[i][j];
        }
    }
    return ss.str();
}
