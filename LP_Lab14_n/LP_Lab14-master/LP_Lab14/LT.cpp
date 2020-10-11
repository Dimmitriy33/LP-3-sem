#include "pch.h"

LT::LexTable LT::Create(int size) {
	if (size > LT_MAXSIZE) {
		throw ERROR_THROW(120);
	}

	LexTable lextable;
	lextable.maxsize = size;
	lextable.size = 0;
	lextable.table = new Entry[size];
	return lextable;
}

void LT::Add(LexTable& lextable, Entry entry) {
	if (lextable.size + 1 > lextable.maxsize) {
		throw ERROR_THROW(121);
	}

	lextable.table[lextable.size] = entry;
	lextable.size++;
}

LT::Entry LT::GetEntry(LexTable& lextable, int n) {
	if (n < 0 || n > lextable.size - 1) {
		throw ERROR_THROW(122);
	}

	return lextable.table[n];
}

void LT::Delete(LexTable& lextable) {
	if (!lextable.table) {
		return;
	}

	delete[] lextable.table;
	lextable.table = nullptr;
}

LT::Entry::Entry(char lexema, int sn, int idxTI)
	:sn(sn), idxTI(idxTI)
{
	this->lexema[0] = lexema;
}

LT::Entry::Entry(const char* lexema, int sn, int idxTI)
	: sn(sn), idxTI(idxTI)
{
	memcpy_s(this->lexema, LEXEMA_FIXSIZE * sizeof(char), lexema, LEXEMA_FIXSIZE * sizeof(char));
}