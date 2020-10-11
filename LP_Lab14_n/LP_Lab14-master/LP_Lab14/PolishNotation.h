#pragma once
#include "pch.h"
#include "Lexer.h"

bool PolishNotation(int i, LT::LexTable& lextable, IT::IdTable& idtable);
int Priority(char l);