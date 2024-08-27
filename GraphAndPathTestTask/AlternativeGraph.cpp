#include "AlternativeGraph.h"

#include <iostream>
#include <fstream>
#include <queue>
#include <cassert>


GraphAdj::GraphAdj(const Graph& my_graph)
{
    for (unsigned int i=0; i < MIN_NODES; ++i)
    {
        for (unsigned int j = 0; j < MIN_NODES; ++j)
        {
            graph[i][j] = 0;
        }
    }

	for (auto& edge : my_graph.edges)
	{
        assert(graph[edge.iFrom][edge.iTo] == 0);
		graph[edge.iFrom][edge.iTo] = edge.weight;
	}
}


unsigned int minDistanceNode(unsigned int dist[], bool Q[])
{
    unsigned int u = UINT_MAX;
    unsigned int min_dist = UINT_MAX;

    for (size_t i = 0; i < MIN_NODES; i++)
    {
        if (Q[i] && dist[i] < min_dist)
        {
            min_dist = dist[i];
            u = i;
        }
    }
    return u;
}


void printSolution(unsigned int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < MIN_NODES; i++)
        printf("\t%d \t\t\t\t %d\n", i, dist[i]);
}


static void PrintPath(std::deque<unsigned int> path)
{
    std::cout << "Path length = " << path.size() << ":\n";
    for (auto id : path)
    {
        std::cout << id << " ";
    }
    std::cout << '\n';
}


std::deque<unsigned int> GraphAdj::dijkstra(unsigned int src, unsigned int tgt)
{
    unsigned int dist[MIN_NODES];
    unsigned int prev[MIN_NODES];
    bool unvisited[MIN_NODES];


    for (unsigned int i = 0; i < MIN_NODES; ++i)
    {
        dist[i] = UINT_MAX;
        prev[i] = UINT_MAX;
        unvisited[i] = true;
    }

    dist[src] = 0;

    for(unsigned int u = src ; u != UINT_MAX ; u = minDistanceNode(dist, unvisited))
    {
        unvisited[u] = false;
        if (u == tgt)
            break;

        for (unsigned int v = 0; v < MIN_NODES; v++)
        {
            if (graph[u][v] == 0)
                continue;

            unsigned int alt = dist[u] + graph[u][v];

            if (unvisited[v] && alt < dist[v])
            {
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }

    std::deque<unsigned int> answer;
    unsigned int u = tgt;
        
    if (prev[u] != UINT_MAX || u == src)
    {
        while (u != UINT_MAX)
        {
            answer.push_front(u);
            u = prev[u];
        }
    }

    return answer;
}


void GraphAdj::print()
{
    std::ofstream f("AltGraph.txt");

    for (int i=0; i<MIN_NODES; i++)
    {
        f << "{";
        for (int j = 0; j < MIN_NODES; j++)
        {
            f << graph[i][j] << ' ';
        }
        f << "}\n";
    }
    f << '\n';
}