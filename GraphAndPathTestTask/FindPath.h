#pragma once
#include <deque>

class Graph;

std::deque<size_t> FindPath(const Graph& graph, const size_t iFrom, const size_t iTo);