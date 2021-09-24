/**
* @file
* @brief Реализация алгоритма Хаффмана
* @author Wallxxx
* @date Сентябрь 2021 года
* @warning Только для Windows! Класс тестировался поверхностно, используйте на свой страх и риск
* 
* Класс имеет два публичных метода:
* - encode(string, string)
* - deconde(string, string, string)
* В качестве первого параметра для "encode" передаётся имя файла или путь к файлу, который нужно 
* сжать, вместе с его именем, например: test.txt или C:\Projects\githubUpdate\test.txt
* Второй параметр для "encode" - название выходного файла. Задаётся аналогично первому параметру.
* 
* Для "decode" нужно три параметра, которые задаются так же, как в "encode":
* - Сжатый файл
* - Название нового файла, в котором будет исходный текст после выполнения алгоритма
* - Файл с таблицой, изначально создаётся при сжатии в папке программы и имеет название "key.txt"
* 
* За основу взято видео FamTrinli'a: https://www.youtube.com/watch?v=KNVPFVG49Oc
*/


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

namespace algorithms
{
	class Huffman
	{
	public:

		/**
		* @brief Конструктор класса
		* 
		* Инициализирует объявленные поля класса значениями по умолчанию
		*/
		Huffman();

		/**
		* @brief Деструктор класса
		* 
		* Очищает поля класса
		*/
		~Huffman();

		/**
		* @brief Функция сжатия файла
		* @param in_file имя исходного файла
		* @param out_file имя сжатого файла
		* 
		* В качестве первого параметра для "encode" передаётся имя файла или путь к файлу, который нужно 
		* сжать, вместе с его именем, например: test.txt или C:\Projects\githubUpdate\test.txt
		* Второй параметр для "encode" - название выходного файла. Задаётся аналогично первому параметру
		*/
		void encode(std::string& in_file, std::string& out_file);

		/**
		* @brief Функция восстановления сжатого файла
		* @param in_file имя сжатого файла
		* @param out_file имя восстановленного файла
		* @param key_file имя файла с таблицей шифрования
		* 
		* Для "decode" нужно три параметра, которые задаются так же, как в "encode":
		* - Сжатый файл
		* - Название нового файла, в котором будет исходный текст после выполнения алгоритма
		* - Файл с таблицой, изначально создаётся при сжатии в папке программы и имеет название "key.txt"
		*/
		void decode(std::string& in_file, std::string& out_file, std::string& key_file);
	private:

		/**
		* @brief Структура узла
		*
		* Содержит поля, отвечающие за узлы
		*/
		struct unit
		{
			unit(); /// Конструктор по умолчанию
			unit(char symbol, uint32_t symbol_frequency); /// Быстрое заполнение полей
			unit(unit* left, unit* right); /// Соединение узлов
			~unit(); /// Деструктор по умолчанию
			uint32_t _symbol_frequency; // Частота встречаемости символа
			char _symbol; // Символ
			unit* _left, * _right; // Указатели на левый и правый узлы
		};

		/**
		* @brief Структура для сортировки узлов
		* 
		* Содержит перегрузку оператора () для контейнера list
		*/
		struct compare
		{
			bool operator()(const unit* left, const unit* right) const /// Перегрузка оператора
			{
				return left->_symbol_frequency < right->_symbol_frequency;
			}
		};

		std::map<char, uint32_t> _frequency; /// Таблица в два столба. Первый столб - символ, второй - кол-во этих символов в исходном файле
		std::map<char, std::vector<bool>> _summary_table; /// Таблица в два столба. Первый - символ, второй - его новый двоичный код
		std::list<unit*> _frequency_table; /// Дерево, на основе которого составляются двоичные коды символов и записывается в "_summary_table"
		std::vector<bool> _way; /// Вектор в новым кодом символа. В коде используется как буффер
		unit* _root; /// Указатель на "голову" дерева "_frequency_table"
		unit* _iterator; /// Итератор, который используется в коде для прохождения по узлам дерева
		uint32_t _all_symbols; /// Сумма всех символов в исходном файле
		uint32_t _write_symbols; /// Сумма уже расшифрованных символов. Не превышает "_all_symbols"
		uint32_t _various_symbols; /// Количество различных символов в исходном файле
		uint16_t _key_symbols; /// Количество символов, которые были зашифрованы. Всегда равно "_various_symbols"
		uint8_t _encode_value; /// Новый двоичный код символа, переведённый из std::vector в 1 байт. Зачастую содержит сразу несколько символов с короткими кодами
		uint8_t _bits; /// Переменная, которая используется в коде как буффер. Нужна для подсчёта битов в коде
		uint8_t _degree; /// Степень. Нужна для восстановления чисел из таблицы (key-файла)
		char _letter; /// В это поле считывается символ из файла; используется как буффер

		/**
		* @brief Открытие потока чтения
		* @param in_file имя исходного файла
		* 
		* Открытие потока в бинарном режиме. Для исходного файла
		*/
		void encodeOpenStreamRead(std::string& in_file);

		/**
		* @brief Чтение символов из исходного файла
		* @param in_stream поток исходного файла
		*/
		void encodeReader(std::ifstream& in_stream);

		/**
		* @brief Заполнение таблицы частот
		* @param in_stream поток исходного файла
		* 
		* Данная функция заполняет таблицу частот встречаемых символов в файле
		*/
		void encodeFilling(std::ifstream& in_stream);

		/**
		* @brief Открытие потоков записи и чтения для кодировки
		* @param in_file имя исходного файла
		* @param out_file имя результирующего сжатого файла
		* 
		* Открывает потоки чтения и записи в бинарных режимах. Если файл для записи не найден, создаёт его
		*/
		void encodeOpenStreamWrite(std::string& in_file, std::string& out_file);

		/**
		* @brief Чтение исходного файла для сжатия
		* @param in_file имя исходного файла
		* @param out_file имя результирующего сжатого файла
		* 
		* Читает все символы из исходного файла
		*/
		void encodeReader(std::ifstream& in_file, std::ofstream& out_file);

		/**
		* @brief составление кода для каждого символа
		* @param out_file имя результирующего сжатого файла
		* @param letter символ из исходного файла
		* 
		* Получает символ из исходного файла, смотрит его код в _summary_table и записывает биты в _encode_value
		*/
		void encodeReaderEncode(std::ofstream& out_file, const char letter);

		/**
		* @brief Запись байтов в файл
		* @param out_file имя результирующего сжатого файла
		* 
		* Записывает один байт двоичного кода в результирующий файл
		*/
		void encodeReaderEncodeWrite(std::ofstream& out_file);

		/**
		* @brief Добавляет все узлы в _frequency_table
		* 
		* Все имеющиеся узлы добавляются в _frequency_table. Сортировка происходит по возрастанию _frequency
		*/
		void makeTable();

		/**
		* @brief Создание дерева на основе _frequency_table
		* 
		* Дерево создаётся по алгоритму, описанному в первых пяти минутах видео. Видео
		* можно найти в описании файла
		*/
		void makeTableTree();

		/**
		* @brief Объединение узлов
		* 
		* Функция объединяет два узла в маленькое дерево, затем повещает голову обратно в _frequency_table
		* 
		* @return указатель на голову нового маленького дерева
		*/
		unit* makeTableTreeNodes();

		/**
		* @brief Рекурсивное составление кода для каждого символа
		* @param start Указатель на голову дерева, откуда следует начинать проход
		* 
		* Функция рекурсивно проходит по каждому узлу и заполняет вектор кодов для каждого символа
		*/
		void makeWay(unit* start);

		/**
		* @brief Открытие потока для записи таблицы шифрования в файл
		* 
		* Файл шифрования по умолчанию: key.txt
		*/
		void saveKey();

		/**
		* @brief Запись количества символов в файл ключа
		* @param key_file поток с файлом ключа
		* @param amount число, которое нужно записать в файл
		* 
		* Записывает число в зеркальном виде
		*/
		void saveKeyAllSymbolsAmount(std::ofstream& key_file, uint32_t amount);

		/**
		* @brief Запись кодов символов
		* @param key_file поток с файлом ключа
		* 
		* Записывает коды каждого символа в файл, разделяя символы и их коды символом 127
		*/
		void saveKeyAllSymbols(std::ofstream& key_file);

		/**
		* @brief Открывает поток для чтения и будующего восстановления исходного файла
		* @param in_file имя сжатого файла
		* @param key_file имя файла ключа
		*/
		void decodeOpenStreamRead(std::string& in_file, std::string& key_file);

		/**
		* @brief Чтение кол-ва всех символов в исходном тексте из файла ключа
		* @param key_stream
		*/
		void decodeOpenStreamReadAllSymbols(std::ifstream& key_stream);

		/**
		* @brief Чтение кол-ва различных символов в исходном тексте из файла ключа
		* @param key_stream
		*/
		void decodeOpenStreamReadVariousSymbols(std::ifstream& key_stream);

		/**
		* @brief Начало прохождения по всем символам из сжатого файла
		* @param key_stream
		*/
		void decodeOpenStreamReadCodes(std::ifstream& key_stream);

		/**
		* @brief Составление дерева на основе шифра символов из файла ключа
		* @param key_stream поток с файлом ключа
		* 
		* Для каждого символа читает его двоичный код и на основе бита (0 или 1) переходит влево или вправо соответственно
		*/
		void makeTree(std::ifstream& key_stream);

		/**
		* @brief Добавляет узел влево
		*/
		void makeTreeLeft();

		/**
		* @brief Добавляет узел вправо
		*/
		void makeTreeRight();

		/**
		* @brief Открытие потоков для расшифровки
		* @param in_file имя сжатого файла
		* @param out_file имя результирующего файла
		*/
		void decodeFile(std::string& in_file, std::string& out_file);

		/**
		* @brief Декодирование текста
		* @param encode_file поток со сжатым файлом
		* @param original_file поток с файлом для записи расшифрованного текста
		* 
		* Чтение одного байта из сжатого файла и расшифровка его битов в соответствии с 
		* таблицой кодов символов
		* 
		* @return истина, если ещё не все символы декодированы и записаны в результирующий файл
		*/
		bool decodeFileRead(std::ifstream& encode_file, std::ofstream& original_file);

		/**
		* @brief Запись декодированного символа в результирующий файл
		* @param original_file
		*/
		void decodeFileWrite(std::ofstream& original_file);

		/**
		* @brief Отчистка всех полей, в том числе контейнеров
		*/
		void cleanAll();

		/**
		* @brief Отчистка только контенеров
		*/
		void cleanData();

		/**
		* @brief Отчистка только переменных
		*/
		void cleanVars();
	};
}
