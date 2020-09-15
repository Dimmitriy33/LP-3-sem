#pragma once
#include "stdafx.h"
#define max_word 1000
#define size_word 20


namespace Lex
{
	bool checkBrace(unsigned char** word, int k);
	struct LEX
	{
		IT::IdTable idtable;;
		LT::LexTable lextable;
	};

	LEX lexAnaliz(Log::LOG log, In::IN in);
}