//#include <iostream>
#include <fstream>
#include <conio.h>
#include "Huffman.h"

#define UNDERLINE "\x1B[4m"
#define RESET "\x1B[0m" 

uint8_t number = 1;
std::string file_check_name = "0";

void helloMessage()
{
	system("cls");
	std::cout << "Сжатие текстовых файлов алгоритмом Хаффмана. " << std::endl;
}

void encode(bool check)
{
	std::cout << "Введите путь и имя файла (C:/test/file.cpp или file_name.txt): ";
	std::string input_file;
	getline(std::cin, input_file);
	if (check) file_check_name = input_file;
	std::cout << "Введите имя выходного файла: ";
	std::string out_file;
	getline(std::cin, out_file);
	algorithms::Huffman algo_encode;
	algo_encode.encode(input_file, out_file);
	std::cout << "Готово. " << std::endl;
}

void decode(bool check)
{
	std::cout << "Введите путь и имя файла (C:/test/file.cpp или file_name.txt): ";
	std::string input_file;
	getline(std::cin, input_file);
	std::cout << "Введите имя выходного файла: ";
	std::string out_file;
	getline(std::cin, out_file);
	algorithms::Huffman algo_encode;
	std::string key = "key.txt";
	algo_encode.decode(input_file, out_file, key);
	std::cout << "Готово. " << std::endl;
	if (check)
	{
		std::string check_command = "fc /N " + file_check_name + " " + out_file;
		system(check_command.c_str());
	}
	std::cout << "Готово. Нажмите любую клавишу для продолжения. " << std::endl;
	_getch();
}

void encodeDecode()
{
	encode(false);
	decode(false);
}

void encodeDecodeCheck()
{
	encode(true);
	decode(true);
}

void menuHandler()
{
	helloMessage();
	if (number == 1) std::cout << UNDERLINE;
	std::cout << "1. Сжать" << RESET << std::endl;
	if (number == 2) std::cout << UNDERLINE;
	std::cout << "2. Распаковать" << RESET << std::endl;
	if (number == 3) std::cout << UNDERLINE;
	std::cout << "3. Сжать и сразу распаковать" << RESET << std::endl;
	if (number == 4) std::cout << UNDERLINE;
	std::cout << "4. Сжать, сразу распаковать и проверить правильность расшифровки" << RESET << std::endl;
	if (number == 5) std::cout << UNDERLINE;
	std::cout << "5. Выход" << RESET << std::endl;
	char choise = _getch();
	if (choise == static_cast<char>(13))
	{
		switch (number)
		{
		case 1:
			encode(false);
			break;
		case 2:
			decode(false);
			break;
		case 3:
			encodeDecode();
			break;
		case 4:
			encodeDecodeCheck();
			break;
		case 5:
			return;
		default:
			break;
		}
	}
	if (static_cast<int>(choise) == -32)
	{
		choise = _getch();
		if ((choise == 0x50) && number < 5) number++;
		if ((choise == 0x48) && number > 1) number--;
	}
	menuHandler();
}

int main()
{
	setlocale(0, "");
	menuHandler();
	return 0;
}
