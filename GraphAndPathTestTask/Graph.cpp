#include "Graph.h"
#include <fstream>
#include <iomanip>
#include <random>
#include <deque>


Graph::Graph()
{
    std::random_device rd;
    std::mt19937 random_generator(rd());
    std::uniform_int_distribution<> nodes_qty_d100(0, 100);
    std::uniform_int_distribution<> edges_qty_d230(0, 230);
    std::uniform_int_distribution<> edge_or_arc(0, 1);

    size_t nNodes = MIN_NODES + nodes_qty_d100(random_generator);
    size_t nEdges = MIN_EDGES + edges_qty_d230(random_generator);

    std::uniform_int_distribution<> d_nodes(0, static_cast<int>(nNodes - 1));
    std::uniform_int_distribution<> d_weights(1, MAX_WEIGHT);

    for (size_t i = 0; i < nNodes; i++)
    {
        nodes.push_back(Node());
    }

    for (size_t i = 0; i < nEdges; i++)
    {
        bool arc = edge_or_arc(random_generator);

        size_t iNode1 = d_nodes(random_generator);
        size_t iNode2;
        bool bad = false;
        do
        {
            bad = false;

            iNode2 = d_nodes(random_generator);
            if (EdgeExists(iNode1, iNode2))
            {
                bad = true;
            }
            if (arc && EdgeExists(iNode2, iNode1))
            {
                bad = true;
            }
            if (iNode1 == iNode2)
            {
                bad = true;
            }
        } while (bad);
        
        unsigned int weight = d_weights(random_generator);

        edges.push_back({ iNode1 , iNode2, weight });

        if (arc)
        {
            edges.push_back({ iNode2 , iNode1, weight });
        }
    }

    for (size_t i=0; i< edges.size(); ++i)
    {
        nodes[edges[i].iFrom].iEdges.push_back(i);
    }
    
}


Graph::Graph(const std::vector<std::vector<unsigned int>> adjacency_matrix)
{
    for (size_t i = 0; i < adjacency_matrix.size(); i++)
    {
        nodes.push_back(Node());
    }

    for (size_t y = 0; y < adjacency_matrix.size(); y++)
    {
        for (size_t x = 0; x < adjacency_matrix.size(); x++)
        {
            if (adjacency_matrix[y][x] == 0)
                continue;

            edges.push_back({y, x, adjacency_matrix[y][x] });
            nodes[y].iEdges.push_back(edges.size() - 1);
        }
    }
}


size_t Graph::GetNodesSize() const
{
    return nodes.size();
}


const Node& Graph::GetNode(size_t id) const
{
    return nodes[id];
}


const Nodes& Graph::GetNodes() const
{
    return nodes;
}


const Edge& Graph::GetEdge(size_t id) const
{
    return edges[id];
}


const Edges& Graph::GetEdges() const
{
    return edges;
}


bool Graph::EdgeExists(size_t iNode1, size_t iNode2)
{
    for (auto& e : edges)
    {
        if (e.iFrom == iNode1 && e.iTo == iNode2)
            return true;
    }
    return false;
}


void PrintGraph(const Graph& g)
{
    std::ofstream f("Graph.txt");

    std::vector<std::vector<unsigned int>> am;

    am.resize(g.GetNodesSize());
    for (auto& row : am)
    {
        row.resize(g.GetNodesSize(), 0);
    }

    for (auto& e : g.GetEdges())
    {
        am[e.iFrom][e.iTo] = e.weight;
    }

    size_t iRow = 0;

    f << ' ';
    for (size_t i = 0; i < g.GetNodesSize(); i++)
    {
        f << std::setfill(' ') << std::setw(3) << i << ' ';
    }
    f << '\n';

    for (auto& row : am)
    {
        f << "{";
        for (auto w : row)
        {
            f << "  " << w << ',';
        }
        f << "}, // " << iRow++ << '\n';
    }
    f << '\n';
}