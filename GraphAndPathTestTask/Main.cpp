﻿#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "Graph.h"
#include "AlternativeGraph.h"
#include "FindPath.h"
#include "Test.h"

template <typename T, typename G>
static void PrintPath(T path, G graph)
{
	std::cout << "Path length = " << path.size() << ", path distance = " << graph.GetDistance(path) << ":\n";
	for (auto id : path)
	{
		std::cout << id << " ";
	}
	std::cout << '\n';
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

/*
#define TEST
//*/

int main()
{
#ifdef TEST
	test();
#else
	//for (int i=0; i<1000; i++)
	{
		Graph graph;
		auto path = FindPath(graph, 0, graph.GetNodesSize() - 1);
		PrintPath(path, graph);

		GraphAdj alt_graph(graph);
		auto path2 = alt_graph.dijkstra(0, MIN_NODES - 1);
		PrintPath(path2, alt_graph);

		PrintGraph(graph);
		alt_graph.print();

		if (path.size() != path2.size())
		{
			path = FindPath(graph, 0, graph.GetNodesSize() - 1);
			GraphAdj alt_graph2(graph);
		}

		auto start = std::chrono::high_resolution_clock::now();
		for (int i=0; i< 10000; i++)
		{
			FindPath(graph, 0, graph.GetNodesSize() - 1);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed{ end - start };

		std::cout << "\nMy: " << elapsed.count() << '\n';

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++)
		{
			alt_graph.dijkstra(0, MIN_NODES - 1);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed = { end - start };

		std::cout << "\nWiki: " << elapsed.count() << '\n';

	}
#endif
	
	return 0;
}


/*

Варианты хранения графа

1. Узлы и ребра - объекты соотвествтующих классов, переход между ними по указателям.
≈ объектно-ориетрированный список смежности

Память: Узлы + ребра. ~ >330.
Поиск пути: Легко. Перебираем имеющиеся указатели.
Выдача результатов: список указателей, нехорошо.
Доступ: Неудобно. Прямой доступ отсуствует.

2. Матрица смежности

Память: Узлы². ~ >10000, разреженная.
Поиск пути: Надо пройти по всей строке в поиске двух-трех ребер. Не оч. 
Выдача результатов: Индексы узлов. Хорошо. Если есть кратные ребра, плохо.
Доступ: Есть прямой доступ к узлам, нет прямого доступа к ребрам

3. Матрица инцидентности

Память: Узлы х Ребра. ~ >23000, разреженная.
Поиск пути: Надо пройти по всей строке в поиске двух-трех ребер. Не оч. 
Выдача результатов: Индексы узлов и если надо, индексы ребер. Хорошо.
Доступ: Есть прямой доступ к узлам и ребрам.

4. Список смежности "в лоб", массивом списков

Память: Узлы + ребра. ~ >330.
Поиск пути: Хорошо, но надо отдельно хранить веса ребер. 
Выдача результатов: Индексы узлов. Хорошо. Если есть кратные ребра, плохо.
Доступ: Прямой к узлам.


5. Список ребер

Память: Ребра. ~ >230.
Поиск пути: Плохо. Чтобы найти вершину, надо просмотреть ребра по порядку.
Выдача результатов: индексы ребер. Норм.
Доступ: Прямой к ребрам.

-----------------------------

Думаю, стоит использовать комбинированный способ.

Узлы и ребра - объекты. Хранятся в массивах (векторах), внутри себя узлы ссылаются на ребра, а ребра на узлы по индексу
В этом случае имеем дорогое удаление узла/ребра (надо перенумеровать все оставишиеся справа, которые будут сдвинуты на -1),
дорогая вставка в середину массива.
Но нам надо создать граф один раз и найти в нем путь один раз. Для этой хадачи - хорошо, при этом упрощается отладка за
счет прямого доступа и ко всем узлам, и ко всем ребрам.

*/