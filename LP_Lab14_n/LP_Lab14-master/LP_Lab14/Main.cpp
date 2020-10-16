#include "pch.h"

//#define lab2
//#define main
//#define test1
//#define test2
//#define test3
//#define test4
//#define test5
//#define test6
#define testPolish

#ifdef testPolish
	#define EXP1 28
	#define EXP2 50
	#define EXP3 59
#endif

int _tmain(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "rus");

	Log::LOG log = Log::INITLOG;

#ifdef lab2
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(LT_MAXSIZE);

		LA::Scan(lextable, idtable, in, parm, log);

		std::cout << "---- lextable ----\n";
		for (int i = 0; i < lextable.size; ++i) {
			std::cout << lextable.table[i].lexema[0] << "\t" << lextable.table[i].sn << "\t";
			if (lextable.table[i].idxTI != TI_NULLIDX) {
				std::cout << lextable.table[i].idxTI;
			}
			std::cout << std::endl;
		}

		std::cout << "\n---- idtable ----\n";
		for (int i = 0; i < idtable.size; ++i) {
			std::cout << idtable.table[i].idxfirstLE << "\t";
			for (int j = 0; j < SCOPE_MAXSIZE && idtable.table[i].scope[j]; ++j) {
				std::cout << idtable.table[i].scope[j];
			}
			std::cout << "\t";
			for (int j = 0; j < ID_MAXSIZE && idtable.table[i].id[j]; ++j) {
				std::cout << idtable.table[i].id[j];
			}
			std::cout << "\t" << (int)idtable.table[i].iddatatype << "\t" << (int)idtable.table[i].idtype << "\t";
			std::cout << std::endl;
		}

		LT::Delete(lextable);
		IT::Delete(idtable);
		Log::Close(log);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif
#ifdef main
	// несколько main, множественное объявление, нет объявления
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);

		LA::Scan(lextable, idtable, in, parm, log);

#pragma region "print tables"
		std::cout << "---- lextable ----\n";
		for (int i = 0; i < lextable.size; ++i) {
			std::cout << lextable.table[i].lexema[0] << "\t" << lextable.table[i].sn << "\t";
			if (lextable.table[i].idxTI != TI_NULLIDX) {
				std::cout << lextable.table[i].idxTI;
			}
			std::cout << std::endl;
		}

		std::cout << "\n---- idtable ----\n";
		for (int i = 0; i < idtable.size; ++i) {
			std::cout << idtable.table[i].idxfirstLE << "\t";
			for (int j = 0; j < SCOPE_MAXSIZE && idtable.table[i].scope[j]; ++j) {
				std::cout << idtable.table[i].scope[j];
			}
			std::cout << "\t";
			for (int j = 0; j < ID_MAXSIZE && idtable.table[i].id[j]; ++j) {
				std::cout << idtable.table[i].id[j];
			}
			std::cout << "\t" << ((idtable.table[i].iddatatype == IT::IDDATATYPE::INT) ? "INT" : "STR") << "\t";

			switch (idtable.table[i].idtype)
			{
			case IT::IDTYPE::V:
				std::cout << "V"; break;
			case IT::IDTYPE::F:
				std::cout << "F"; break;
			case IT::IDTYPE::P:
				std::cout << "P"; break;
			case IT::IDTYPE::L:
				std::cout << "L"; break;
			}
			std::cout << "\t";
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
				std::cout << idtable.table[i].value.vint;
			}
			else if (idtable.table[i].value.vstr.len) {
				std::cout << (int)idtable.table[i].value.vstr.len << "\t" << idtable.table[i].value.vstr.str;
			}
			else {
				std::cout << (int)idtable.table[i].value.vstr.len;
			}

			std::cout << std::endl;
		}
#pragma endregion

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // main

#ifdef test1
	// тест размера таблицы лексем max
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(LT_MAXSIZE + 1);
		IT::IdTable idtable = IT::Create(228);

		LA::Scan(lextable, idtable, in, parm, log);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test1

#ifdef test2
	// тест размера таблицы идентификаторов max
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(228);
		IT::IdTable idtable = IT::Create(LT_MAXSIZE + 1);

		LA::Scan(lextable, idtable, in, parm, log);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test2

#ifdef test3
	// тест размера таблицы лексем min
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(1);
		IT::IdTable idtable = IT::Create(228);

		LA::Scan(lextable, idtable, in, parm, log);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test3

#ifdef test4
	// тест размера таблицы идентификаторов min
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(1);

		LA::Scan(lextable, idtable, in, parm, log);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test4

#ifdef test5
	// поиск лексемы за предлами таблицы лексем
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(LT_MAXSIZE);

		LA::Scan(lextable, idtable, in, parm, log);

		LT::GetEntry(lextable, LT_MAXSIZE + 1);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test5

#ifdef test6
	// поиск лексемы за предлами таблицы идентификаторов
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(LT_MAXSIZE);

		LA::Scan(lextable, idtable, in, parm, log);

		IT::GetEntry(idtable, -1);

		LT::Delete(lextable);
		IT::Delete(idtable);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
#endif // test6

#ifdef testPolish
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::Write(log, L"Тест:", L" без ошибок ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::Close(log);
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);

		LA::Scan(lextable, idtable, in, parm, log);


		bool rc = PolishNotation(EXP1, lextable, idtable);
		if (rc)
		std::cout << "Польская запись построена" << std::endl;
		else
		std::cout << "Польская запись не построена" << std::endl;
#endif

	return 0;
}