#pragma once
#define LEXEMA_FIXSIZE			1
#define LT_MAXSIZE				4096
#define LT_TI_NULLIDX			((int)0xffffffff)
#define LEX_INTEGER				'n'
#define LEX_STRING				's'
#define LEX_DATATYPE			't'
#define LEX_ID					'i'
#define LEX_INTEGER_LITERAL		'1'
#define LEX_STRING_LITERAL		'2'
#define LEX_LITERAL				'l'
#define LEX_FUNCTION			'f'
#define LEX_DECLARE				'd'
#define LEX_RETURN				'r'
#define LEX_PRINT				'p'
#define LEX_MAIN				'm'
#define LEX_SEMICOLON			';'
#define LEX_COMMA				','
#define LEX_LEFTBRACE			'{'
#define LEX_BRACELET			'}'
#define LEX_LEFTHESIS			'('
#define LEX_RIGHTHESIS			')'
#define LEX_PLUS				'v'
#define LEX_MINUS				'v'
#define LEX_STAR				'w'
#define LEX_DIRSLASH			'w'
#define LEX_EQUALS				'='

namespace LT {
	struct Entry {
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int idxTI;

		Entry() = default;
		Entry(char lexema, int sn, int idxTI);
		Entry(const char* lexema, int sn, int idxTI);
	};

	struct LexTable {
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
}