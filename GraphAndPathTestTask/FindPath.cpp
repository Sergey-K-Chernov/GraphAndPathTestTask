#include "FindPath.h"
#include "Graph.h"


std::deque<size_t> FindPath(const Graph& graph, const size_t iFrom, const size_t iTo)
{
	std::deque<size_t> path;
	
	if (graph.GetNode(iFrom).iEdges.empty())
		return path;

	HelperSet helper(graph);
	helper.SetDistance(iFrom, 0);

	for(const NodeHelper* current = helper.get(iFrom); current != nullptr; current = helper.UnvisitedTop())
	{
		helper.Visit(current->id);
		if (current->id == iTo)
			break;

		auto& iEdges = graph.GetNode(current->id).iEdges;
		for (auto& iEdge : iEdges)
		{
			auto& edge = graph.GetEdge(iEdge);

			unsigned int new_distance = current->distance + edge.weight;

			if (!helper.IsVisited(edge.iTo) && new_distance < helper.GetDistance(edge.iTo))
			{
				helper.SetDistance(edge.iTo, new_distance);
				helper.SetPrevious(edge.iTo, current->id);
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


HelperSet::HelperSet(const Graph& graph)
{
	auto& nodes = graph.GetNodes();
	node_helpers.resize(nodes.size());
	for (size_t i = 0; i < node_helpers.size(); ++i)
	{
		node_helpers[i].id = i;
	}
}


const NodeHelper* HelperSet::get(size_t id) const
{
	return &node_helpers[id];
}


bool HelperSet::IsVisited(size_t id) const
{
	return node_helpers[id].visited;
}


void HelperSet::Visit(size_t id)
{
	node_helpers[id].visited = true;
}


const NodeHelper* HelperSet::UnvisitedTop() const
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

	if (id >= node_helpers.size())
		return nullptr;

	return &node_helpers[id];
}


void HelperSet::SetPrevious(size_t id, size_t iPrev)
{
	node_helpers[id].iPrev = iPrev;
}


unsigned int HelperSet::GetDistance(size_t id) const
{
	return node_helpers[id].distance;
}


void HelperSet::SetDistance(size_t id, unsigned int distance)
{
	node_helpers[id].distance = distance;
}