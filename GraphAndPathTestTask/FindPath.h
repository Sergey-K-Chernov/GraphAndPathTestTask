#pragma once
#include <deque>
#include <vector>

class Graph;

std::deque<size_t> FindPath(const Graph& graph, const size_t iFrom, const size_t iTo);

struct NodeHelper {
	size_t id = UINT_MAX;
	unsigned int distance = UINT_MAX;
	size_t iPrev = UINT_MAX;
	bool visited = false;
};


class HelperSet {
public:
	HelperSet() = delete;
	HelperSet(const Graph& graph);

	const NodeHelper* get(size_t id) const;

	bool IsVisited(size_t id) const;
	void Visit(size_t id);

	const NodeHelper* UnvisitedTop() const;

	void SetPrevious(size_t id, size_t iPrev);

	unsigned int GetDistance(size_t id) const;
	void SetDistance(size_t id, unsigned int distance);

private:
	std::vector<NodeHelper> node_helpers;
};
