#include "Test.h"

#include <cassert>
#include "Graph.h"
#include "FindPath.h"


void test()
{
	test1();
}


void test1()
{
	std::vector<std::vector<int>> adjacency_matrix = {
			{0, 5, 9, 2, 0, 0, 0, 0},
			{0, 0, 3, 0, 4, 0, 0, 0},
			{9, 0, 0, 0, 0, 0, 0, 0},
			{2, 0, 0, 0, 0, 0, 0, 0},
			{0, 4, 0, 9, 0, 7, 0, 1},
			{0, 0, 4, 0, 7, 0, 6, 0},
			{0, 0, 0, 0, 0, 6, 0, 0},
			{0, 0, 0, 0, 1, 0, 0, 0},
	};


	Graph graph(adjacency_matrix);

	struct Problem {
		size_t iFrom;
		size_t iTo;
	};
	std::vector<Problem> problems = {
		{ 0, 3 },
		{ 0, 4 },
		{ 0, 6 },
		{ 4, 2 },
		{ 5, 2 },
		{ 6, 1 },
		{ 6, 2 },
		{ 6, 3 },
		{ 7, 2 },
		{ 7, 0 },
	};

	std::vector<std::vector<size_t>> real_answers = {
		{0, 1, 2}, // 5+3=8 < 9
		{0, 1, 4},
		{0, 1, 4, 5, 6 },
		{4, 1, 2},
		{5, 2},
		{6, 5, 4, 1},
		{6, 5, 2},
		{6, 5, 2, 0, 3},
		{7, 4, 1, 2 },
		{7, 4, 3, 0},
	};

	assert(problems.size() == real_answers.size());

	for (size_t i = 0; i < real_answers.size(); ++i)
	{
		std::vector<size_t> answer = FindPath(graph, problems[i].iFrom, problems[i].iTo);
		assert(answer == real_answers[i]);
	}
	
};

