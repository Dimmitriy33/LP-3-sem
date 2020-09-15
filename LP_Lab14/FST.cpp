#include "stdafx.h"
using namespace std;
using namespace Error;

//namespace FST
//{
//	//Конструктор структуры RELATION
//	RELATION::RELATION(unsigned char c, short nn)
//	{
//		symbol = c;
//		nnode = nn;
//	}
//
//	NODE::NODE() // по умолчанию
//	{
//		n_relation = 0;
//		relations = nullptr;
//	}
//
//	NODE::NODE(short n, RELATION rel, ...) // с параметрами
//	{
//		n_relation = n;
//		RELATION *p = &rel;
//		relations = new RELATION[n];
//		for (size_t i = 0; i < n; i++)
//		{
//			relations[i] = p[i];
//		}
//	}
//
//	int col = 0;
//
//	//Конструктор структуры FST
//	FST::FST(unsigned char* s, short ns, NODE n, ...)
//	{
//		string = s;
//		nstates = ns;
//		nodes = new NODE[ns];
//		NODE* p = &n;
//		for (int k = 0; k < ns; k++)
//			nodes[k] = p[k];
//		rstates = new short[nstates];
//		memset(rstates, 0xff, sizeof(short) * nstates); // заполняет nstates байтов блока памяти, через указатель rstates.
//		rstates[0] = 0;
//		position = -1;
//	}
//
//	bool step(FST& fst, short* &rstates) // один шаг автомата
//	{
//		bool rc = false;
//		std::swap(rstates, fst.rstates); // смена массивов
//		for (short i = 0; i < fst.nstates; i++)
//		{
//			if (rstates[i] == fst.position)
//				for (short j = 0; j < fst.nodes[i].n_relation; j++)
//				{
//					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
//						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
//						rc = true;
//					};		
//				};
//		};
//		return rc;
//	};
//
//	bool execute(FST& fst)
//	{
//		short* rstates = new short[fst.nstates];
//		memset(rstates, 0xff, sizeof(short) * fst.nstates);
//		short lstring = _mbslen(fst.string);
//		bool rc = true;
//		for (short i = 0; i < lstring && rc; i++)
//		{
//			fst.position++;
//			rc = step(fst, rstates);
//			/*	std::cout << "smth : "<< fst.string[fst.position] << std::endl;
//				for (int ant = 0; ant < 7; ant++)
//				{
//					std::cout << rstates[ant] << " ";
//				}
//				std::cout << std::endl;*/
//
//		};
//		delete[] rstates;
//		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
//	}
//
//}

FST::RELATION::RELATION(unsigned char c, short ns)
	: symbol(c), nnode(ns)
{ }

FST::NODE::NODE()
	: n_relation(0), relations(NULL)
{ }

FST::NODE::NODE(short n, RELATION rel, ...)
	: n_relation(n)
{
	RELATION* p = &rel;
	relations = new RELATION[n];

	for (short i = 0; i < n; ++i)
		relations[i] = p[i];
}

FST::FST::FST(unsigned char* s, short ns, NODE n, ...)
	: string(s), position(-1), nstates(ns)
{
	nodes = new NODE[ns];
	NODE* p = &n;

	for (int i = 0; i < ns; ++i)
		nodes[i] = p[i];

	rstates = new short[nstates];
	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
}

bool step(FST::FST& fst, short*& rstates) {
	bool rc = false;

	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; ++i)
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; ++j)
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}

	return rc;
}

bool FST::execute(FST& fst) {
	short* rstates = new short[fst.nstates];
	short lstring = (short)strlen((const char*)fst.string);
	bool rc = true;

	memset(rstates, 0xff, sizeof(short) * fst.nstates);

	for (short i = 0; i < lstring && rc; ++i) {
		fst.position++;
		rc = step(fst, rstates);
	}
	delete[] rstates;

	return rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc;
}
