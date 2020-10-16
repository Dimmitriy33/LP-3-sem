#include "pch.h"
#include <stack>
#include <queue>
//#include "PolishNotation.h"
//#include "Lexer.h"


using namespace std;

bool PolishNotation(int i, LT::LexTable& lextable, IT::IdTable& idtable)
{
	stack<LT::Entry> stack;														// стек для операций
	queue<LT::Entry> queue;														// очередь для операндов
	int countLex = 0;															// количество преобразованных лексем
	int countParm = 0;															// количество параметров функции
	int posLex = i;																// запоминаем номер лексемы перед преобразованием
	bool findFunc = false;														// флаг для функции
	bool findComma = false;														// флаг для запятой (кол-во параметров +2 сразу)
	char* buf = new char[2];													// буфер для countParm в строковом представлении

	for (i; lextable.table[i].lexema[0] != LEX_SEMICOLON; i++, countLex++)  // ------------
	{
		switch (lextable.table[i].lexema[0])
		{
		case LEX_ID:															// если идентификатор
		{
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				findFunc = true;
			queue.push(lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:															// если литерал
		{
			queue.push(lextable.table[i]);										// помещаем в очередь
			continue;
		}
		case LEX_LEFTHESIS:														// если (
		{
			stack.push(lextable.table[i]);										// помещаем ее в стек
			continue;
		}
		case LEX_RIGHTHESIS:														// если )
		{
			if (findFunc)															// если это вызов функции, то лексемы () заменяются на @ и кол-во параметров
			{
				if (findComma)
				{
					countParm++;
				}
				lextable.table[i].lexema[0] = '#';									// запрещенная лексема
				queue.push(lextable.table[i]);									// добавляем в очередь лексему вызова функции
				_itoa_s(countParm, buf, 2, 10);										// преобразование числа countParm в строку
				stack.top().lexema[0] = buf[0];
				stack.top().idxTI = -1; stack.top().sn = -1;						// заполняем лексему, указывающую количество параметров функции
				queue.push(stack.top());											// добавляем в очередь эту лексему
				findFunc = false;
			}
			else if (!stack.empty()) {
				while (stack.top().lexema[0] != LEX_LEFTHESIS)						// пока не встретим (
				{
					queue.push(stack.top());										// выталкиваем со стека в очередь
					if (!stack.empty())
						stack.pop();

					if (stack.empty())
						return false;
				}
			}
			if(!stack.empty())
				stack.pop();															// уничтожаем ( или лексему, указывающую количество параметров функции
			continue;
		}
		case 'v':															// если знак оператора
		{
			int priority, id;
			if (!stack.empty())
			{
				if (stack.top().lexema[0] == LEX_LEFTHESIS || stack.top().lexema[0] == LEX_RIGHTHESIS)
					priority = 1;
				else {
					id = stack.top().idxTI;
					priority = Priority(idtable.table[id].id[0]);
				}
			}
			if (Priority(lextable.table[i].lexema[0]) > priority)																		//если приоритет добавляемой операции больше операции на вершине стека
				stack.push(lextable.table[i]);																		//добавляем операции в стек
			else
			{
				while (stack.size() && Priority(lextable.table[i].lexema[0]) <= Priority(idtable.table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
				{
					queue.push(stack.top());											// выталкиваем со стека в выходную строку
					if (!stack.empty())
						stack.pop();
				}
				stack.push(lextable.table[i]);
				continue;
			}
			continue;
		}
		case 'w':															// если знак оператора
		{
			int priority, id;
			if (stack.top().lexema[0] == LEX_LEFTHESIS || stack.top().lexema[0] == LEX_RIGHTHESIS)
				priority = 1;
			else {
				id = stack.top().idxTI;
				priority = Priority(idtable.table[id].id[0]);
			}
			if (Priority(lextable.table[i].lexema[0]) > priority)																		//если приоритет добавляемой операции больше операции на вершине стека
				stack.push(lextable.table[i]);																		//добавляем операции в стек
			else
			{
				while (stack.size() && Priority(lextable.table[i].lexema[0]) <= Priority(idtable.table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
				{
					queue.push(stack.top());											// выталкиваем со стека в выходную строку
					if (!stack.empty())
						stack.pop();
				}
				stack.push(lextable.table[i]);
				continue;
			}
			continue;
		}
		case LEX_COMMA:																// если запятая
		{
			findComma = true;
			countParm++;
			continue;
		}
		}
	}

	while (!stack.empty())															// если стек не пустой
	{
		if (stack.top().lexema[0] == LEX_LEFTHESIS || stack.top().lexema[0] == LEX_RIGHTHESIS)
			return false;
		queue.push(stack.top());													// выталкиваем все в очередь
		if (!stack.empty())
			stack.pop();
	}
	while (countLex != 0)															// замена текущего выражения в таблице лексем на польскую запись
	{
		if (!queue.empty()) {
			lextable.table[posLex++] = queue.front();
			cout << idtable.table[queue.front().idxTI].id << " ";				// вывод в консоль
			queue.pop();
		}
		else
		{
			lextable.table[posLex++].lexema[0] = '#';
		}
		countLex--;
	}
	for (int i = 0; i < posLex; i++)												// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
	{
		if (lextable.table[i].lexema[0] == 'v' || lextable.table[i].lexema[0] == LEX_LITERAL)
			idtable.table[lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}

	int Priority(char l)
	{
		if (l == LEX_LEFTHESIS || l == LEX_RIGHTHESIS) return 1;
		else if (l == LEX_PLUS || l == LEX_MINUS) return 2;
		else if (l == LEX_STAR) return 3;
	}
