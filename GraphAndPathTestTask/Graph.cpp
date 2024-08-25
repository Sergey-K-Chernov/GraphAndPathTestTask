#include "Graph.h"

#include <random>

const size_t MIN_NODES = 100;
const size_t MIN_EDGES = 230;
const size_t MAX_WEIGHT = 10;

Graph::Graph()
{
    std::random_device rd;
    std::mt19937 random_generator(rd());
    std::uniform_int_distribution<> nodes_qty_d100(0, 100);
    std::uniform_int_distribution<> edges_qty_d230(0, 230);
    std::uniform_int_distribution<> edge_or_arc(0, 1);

    size_t nNodes = MIN_NODES;// +nodes_qty_d100(random_generator);
    size_t nEdges = MIN_EDGES;// +edges_qty_d230(random_generator);

    std::uniform_int_distribution<> d_nodes(0, static_cast<int>(nNodes - 1));
    std::uniform_int_distribution<> d_weights(0, MAX_WEIGHT);

    for (size_t i = 0; i < nNodes; i++)
    {
        nodes.push_back(Node());
    }

    for (size_t i = 0; i < nEdges; i++)
    {
        size_t iNode1 = d_nodes(random_generator);
        size_t iNode2 = d_nodes(random_generator);
        int weight = d_weights(random_generator);

        edges.push_back({ iNode1 , iNode2, weight });
        if(edge_or_arc(random_generator))
            edges.push_back({ iNode2 , iNode1, weight });

        nodes[iNode1].edges.push_back(edges.size() - 1);
    }
}


Graph::Graph(const std::vector<std::vector<int>> adjacency_matrix)
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
            nodes[y].edges.push_back(edges.size() - 1);
        }
    }
}