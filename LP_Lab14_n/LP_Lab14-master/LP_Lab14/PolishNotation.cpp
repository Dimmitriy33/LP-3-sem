#include "pch.h"
#include <stack>
#include <queue>
//#include "PolishNotation.h"
//#include "Lexer.h"


using namespace std;

bool PolishNotation(int i, LT::LexTable& lextable, IT::IdTable& idtable)
{
	stack<LT::Entry> stack;														// ���� ��� ��������
	queue<LT::Entry> queue;														// ������� ��� ���������
	int countLex = 0;															// ���������� ��������������� ������
	int countParm = 0;															// ���������� ���������� �������
	int posLex = i;																// ���������� ����� ������� ����� ���������������
	bool findFunc = false;														// ���� ��� �������
	bool findComma = false;														// ���� ��� ������� (���-�� ���������� +2 �����)
	char* buf = new char[2];													// ����� ��� countParm � ��������� �������������

	for (i; lextable.table[i].lexema[0] != LEX_SEMICOLON; i++, countLex++)  // ------------
	{
		switch (lextable.table[i].lexema[0])
		{
		case LEX_ID:															// ���� �������������
		{
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				findFunc = true;
			queue.push(lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:															// ���� �������
		{
			queue.push(lextable.table[i]);										// �������� � �������
			continue;
		}
		case LEX_LEFTHESIS:														// ���� (
		{
			stack.push(lextable.table[i]);										// �������� �� � ����
			continue;
		}
		case LEX_RIGHTHESIS:														// ���� )
		{
			if (findFunc)															// ���� ��� ����� �������, �� ������� () ���������� �� @ � ���-�� ����������
			{
				if (findComma)
				{
					countParm++;
				}
				lextable.table[i].lexema[0] = '#';									// ����������� �������
				queue.push(lextable.table[i]);									// ��������� � ������� ������� ������ �������
				_itoa_s(countParm, buf, 2, 10);										// �������������� ����� countParm � ������
				stack.top().lexema[0] = buf[0];
				stack.top().idxTI = -1; stack.top().sn = -1;						// ��������� �������, ����������� ���������� ���������� �������
				queue.push(stack.top());											// ��������� � ������� ��� �������
				findFunc = false;
			}
			else if (!stack.empty()) {
				while (stack.top().lexema[0] != LEX_LEFTHESIS)						// ���� �� �������� (
				{
					queue.push(stack.top());										// ����������� �� ����� � �������
					if (!stack.empty())
						stack.pop();

					if (stack.empty())
						return false;
				}
			}
			if(!stack.empty())
				stack.pop();															// ���������� ( ��� �������, ����������� ���������� ���������� �������
			continue;
		}
		case 'v':															// ���� ���� ���������
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
			if (Priority(lextable.table[i].lexema[0]) > priority)																		//���� ��������� ����������� �������� ������ �������� �� ������� �����
				stack.push(lextable.table[i]);																		//��������� �������� � ����
			else
			{
				while (stack.size() && Priority(lextable.table[i].lexema[0]) <= Priority(idtable.table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
				{
					queue.push(stack.top());											// ����������� �� ����� � �������� ������
					if (!stack.empty())
						stack.pop();
				}
				stack.push(lextable.table[i]);
				continue;
			}
			continue;
		}
		case 'w':															// ���� ���� ���������
		{
			int priority, id;
			if (stack.top().lexema[0] == LEX_LEFTHESIS || stack.top().lexema[0] == LEX_RIGHTHESIS)
				priority = 1;
			else {
				id = stack.top().idxTI;
				priority = Priority(idtable.table[id].id[0]);
			}
			if (Priority(lextable.table[i].lexema[0]) > priority)																		//���� ��������� ����������� �������� ������ �������� �� ������� �����
				stack.push(lextable.table[i]);																		//��������� �������� � ����
			else
			{
				while (stack.size() && Priority(lextable.table[i].lexema[0]) <= Priority(idtable.table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
				{
					queue.push(stack.top());											// ����������� �� ����� � �������� ������
					if (!stack.empty())
						stack.pop();
				}
				stack.push(lextable.table[i]);
				continue;
			}
			continue;
		}
		case LEX_COMMA:																// ���� �������
		{
			findComma = true;
			countParm++;
			continue;
		}
		}
	}

	while (!stack.empty())															// ���� ���� �� ������
	{
		if (stack.top().lexema[0] == LEX_LEFTHESIS || stack.top().lexema[0] == LEX_RIGHTHESIS)
			return false;
		queue.push(stack.top());													// ����������� ��� � �������
		if (!stack.empty())
			stack.pop();
	}
	while (countLex != 0)															// ������ �������� ��������� � ������� ������ �� �������� ������
	{
		if (!queue.empty()) {
			lextable.table[posLex++] = queue.front();
			cout << idtable.table[queue.front().idxTI].id << " ";				// ����� � �������
			queue.pop();
		}
		else
		{
			lextable.table[posLex++].lexema[0] = '#';
		}
		countLex--;
	}
	for (int i = 0; i < posLex; i++)												// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
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
