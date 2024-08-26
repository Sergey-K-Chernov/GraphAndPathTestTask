#include "FindPath.h"
#include <memory>
#include <set>
#include <iostream>

#include "Graph.h"


struct NodeHelper{
	size_t id = UINT_MAX;
	unsigned int distance = UINT_MAX;
	size_t iPrev = UINT_MAX;
	//bool visited;
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
		node_helpers = std::unique_ptr<NodeHelper[]>(new NodeHelper[nodes.size()]);
		for (size_t i=0; i<nodes.size(); ++i)
		{
			node_helpers[i].id = i;
			by_id.insert(&node_helpers[i]);
			by_distance.insert(&node_helpers[i]);
		}
	}

	const NodeHelper* get(size_t id)
	{
		return &node_helpers[id];
	}

	bool is_visited(size_t id)
	{
		return by_id.find(&node_helpers[id]) == by_id.end();
	}

	void unvisited_pop()
	{
		auto to_pop = *(by_distance.begin());
		by_distance.erase(by_distance.begin());
		by_id.erase(to_pop);

		// std::cout << by_id.size() << '\n';
		// Из массива не удаляется by design;
	}

	NodeHelper* unvisited_top()
	{
		return *(by_distance.begin());
	}
	
	bool unvisited_empty() const
	{
		return by_id.empty();
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
		by_distance.erase(&node_helpers[id]);
		node_helpers[id].distance = distance;
		by_distance.insert(&node_helpers[id]);
	}
	
private:
	std::unique_ptr<NodeHelper[]> node_helpers;
	std::set<NodeHelper*, LessById> by_id;
	std::set<NodeHelper*, LessByDistance> by_distance;
};


std::vector<size_t> FindPath(const Graph& graph, const size_t iFrom, const size_t iTo)
{
	std::vector<size_t> path;
	
	HelperSet helper(graph);
	helper.set_distance(iFrom, 0);

	while (!helper.unvisited_empty())
	{
		const NodeHelper* current = helper.unvisited_top();
		if (current->id == iTo)
			break;
		helper.unvisited_pop();

		auto& iEdges = graph.GetNode(current->id).edges;
		for (auto& iEdge : iEdges)
		{
			auto& edge = graph.GetEdge(iEdge);
			if (helper.is_visited(edge.iTo))
				continue;

			unsigned int new_distance = current->distance + edge.weight;
			if (new_distance < helper.get_distance(edge.iTo))
			{
				helper.set_distance(edge.iTo, new_distance);
				helper.set_prev(edge.iTo, current->id);
			}
		}
	}

	auto path_node = helper.get(iTo);
	if (path_node->distance != UINT_MAX)
	{
		path.push_back(path_node->id);
		do {
			path.push_back(path_node->iPrev);
			path_node = helper.get(path_node->iPrev);
		} while (path_node->iPrev != UINT_MAX);
	}

	for (size_t i = 0, j = path.size()-1;  path.size() > 0 && i < j; ++i, --j)
	{
		std::swap(path[i], path[j]);
	}

	return path;
}