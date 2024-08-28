#include "FindPath.h"
#include <memory>
#include <set>
#include <iostream>

#include "Graph.h"


struct NodeHelper{
	size_t id = UINT_MAX;
	unsigned int distance = UINT_MAX;
	size_t iPrev = UINT_MAX;
	bool visited = false;
};

struct LessByDistance
{
	bool operator () (const NodeHelper* n1, const NodeHelper* n2) const
	{
		if (n1->distance == n2->distance)
			return n1->id < n2->id;

		return n1->distance < n2->distance;
	}
};

struct LessById
{
	bool operator () (const NodeHelper* n1, const NodeHelper* n2) const
	{
		return n1->id < n2->id;
	}
};

class HelperSet {
public:
	HelperSet() = delete;
	HelperSet(const Graph& graph)
	{
		auto& nodes = graph.GetNodes();
		node_helpers.resize(nodes.size());
		size = nodes.size();
		for (size_t i=0; i< size; ++i)
		{
			node_helpers[i].id = i;
		}
	}

	const NodeHelper* get(size_t id)
	{
		return &node_helpers[id];
	}

	bool is_visited(size_t id)
	{
		return node_helpers[id].visited;
	}

	void visit(size_t id)
	{
		node_helpers[id].visited = true;
	}

	const NodeHelper* unvisited_top()
	{
		unsigned int id = UINT_MAX;
		unsigned int min_dist = UINT_MAX;

		for (const NodeHelper& node : node_helpers)
		{
			if (!node.visited && node.distance < min_dist)
			{
				min_dist = node.distance;
				id = node.id;
			}
		}

		if (id >= size)
			return nullptr;

		return &node_helpers[id];
	}

	void set_prev(size_t id, size_t iPrev)
	{
		node_helpers[id].iPrev = iPrev;
	}

	unsigned int get_distance(size_t id)
	{
		return node_helpers[id].distance;
	}

	void set_distance(size_t id, unsigned int distance)
	{		
		node_helpers[id].distance = distance;
	}
	
private:
	size_t size;
	std::vector<NodeHelper> node_helpers;
};


std::deque<size_t> FindPath(const Graph& graph, const size_t iFrom, const size_t iTo)
{
	std::deque<size_t> path;
	
	if (graph.GetNode(iFrom).iEdges.empty())
		return path;

	HelperSet helper(graph);
	helper.set_distance(iFrom, 0);

	for(const NodeHelper* current = helper.get(iFrom); current != nullptr; current = helper.unvisited_top())
	{
		helper.visit(current->id);
		if (current->id == iTo)
			break;

		auto& iEdges = graph.GetNode(current->id).iEdges;
		for (auto& iEdge : iEdges)
		{
			auto& edge = graph.GetEdge(iEdge);

			unsigned int new_distance = current->distance + edge.weight;

			if (!helper.is_visited(edge.iTo) && new_distance < helper.get_distance(edge.iTo))
			{
				helper.set_distance(edge.iTo, new_distance);
				helper.set_prev(edge.iTo, current->id);
			}
		}
	}

	auto path_node = helper.get(iTo);
	if (path_node->distance != UINT_MAX)
	{
		path.push_front(path_node->id);
		do {
			path.push_front(path_node->iPrev);
			path_node = helper.get(path_node->iPrev);
		} while (path_node->iPrev != UINT_MAX);
	}

	return path;
}