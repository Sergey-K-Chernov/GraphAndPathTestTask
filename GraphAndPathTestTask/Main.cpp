﻿

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