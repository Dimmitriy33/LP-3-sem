#include "In.h"
#include "Error.h"
//#include "FST.h"
#include <fstream>
#include <iostream>
#include <string>

namespace In
{
	IN getin(Parm::PARM parm)
	{
		std::ofstream fout;
		fout.open(parm.out);
		std::ifstream file(parm.in);
		if (!file.is_open())
			throw ERROR_THROW(110);
		if (!fout.is_open())
			throw ERROR_THROW(110);

		IN input;
		input.size = input.lines = input.ignor = 0;
		input.text = new unsigned char[IN_MAX_LEN_TEXT];

		//char table[] = IN_CODE_TABLE;

		int l = IN::T, posstr = 0;
		/*std::string str;*/

		//IN input;
		//input.size = input.lines = input.ignor = 0;
		//input.text = new unsigned char[IN_MAX_LEN_TEXT];
		//unsigned char* ptext = input.text; // указатель на начало текста

		//char table[] = IN_CODE_TABLE;

		/*int posstr = 0, posline = 0, SpacePos = 0, f = 0;
		std::string str;

		std::string FullText;
		std::string temp;*/

		/*while (!file.eof())
		{
			input.lines++;
			std::getline(file, temp);
			temp += "\n";
			FullText += temp;
		}*/

		//for (int i = 0; i < FullText.size(); i++)
		//{
		//	if (input.code[FullText[i]] == IN::F)
		//	{
		//		throw ERROR_THROW_IN(111, posline, posstr);
		//	}
		//	else if (input.code[FullText[i]] == IN::I)
		//	{
		//		input.ignor++;
		//		continue;
		//	}
		//	else if (input.code[FullText[i]] == IN::T)
		//	{
		//		*ptext = FullText[i];
		//		input.size++;
		//		ptext++;
		//	}
		//	else if (input.code[FullText[i]] == IN::S)
		//	{
		//		if (input.size - SpacePos > 1) // если до ближайшего предыдущего пробела более одной позиции
		//		{
		//			SpacePos = input.size;
		//			input.size++;
		//		}
		//		else {
		//			input.ignor++;
		//			continue;
		//		}
		//	}
		//	else
		//	{
		//		*ptext = input.code[FullText[i]];
		//		ptext++;
		//		input.size++;
		//	}

		//	if (FullText[i] == '\n')
		//	{
		//		posline++;
		//		posstr = 0;
		//	}
		//	else
		//		posstr++;
		//}

		//*ptext = IN_CODE_ENDL;

		do
		{
			l = file.get(); 
			if (l != EOF)
			{
				if (l == IN_CODE_ENDL)
				{
					posstr = 0;
					input.lines++;
					input.text[input.size] = IN_CODE_DELIMITER;
					input.size++;
					/*const char* c = str.c_str();*/
					/*if(str != "")
						FST::NewLine(c, input.lines, parm);*/
					/*str = "";*/
				}
				//else {
				//	str += l;
				//}
			}
			else {
				/*const char* c = str.c_str();*/
				/*if (str != "")
					FST::NewLine(c, input.lines, parm);*/
				/*str = "";*/
			}

			if (input.code[l] == IN::F)
			{
				throw ERROR_THROW_IN(111, input.lines, posstr);
			}
			else if (input.code[l] == IN::I)
			{
				input.ignor++;
				continue;
			}
			else if (input.code[l] == IN::T)
			{
				input.text[input.size] = (char)l;
				input.size++;
			}
			else if (input.code[l] == IN::N)
			{
				if (input.size != 0 && input.code[input.text[input.size - 1]] == IN::S) // 1 усл, чтобы не выйти за границы
				{
					input.text[input.size - 1] = (char)l;
					input.ignor++;
				}
				else
				{
					input.text[input.size] = (char)l;
					input.size++;
				}
			}
			else if (input.code[l] == IN::S)
			{
				if (input.text[input.size - 1] == ' ' || input.code[input.text[input.size - 1]] == IN::N /*|| input.text[input.size - 1] == IN_CODE_DELIMITER*/) // если предыдущий символ -- разделитель
				{
					input.ignor++;
				}
				else
				{
					input.text[input.size] = (char)l;
					input.size++;
				}
			}
			//else
			//{
			//	input.text[input.size] = input.code[l];
			//	input.size++;

			//	posstr++;
			//}
		} while (l != EOF);

		input.text[input.size] = '\0';
		file.close();
		fout.close();
		return input;
	}
}
