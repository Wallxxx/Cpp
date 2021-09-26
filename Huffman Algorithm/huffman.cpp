#include "Huffman.h"

namespace algorithms
{

	Huffman::Huffman() // Конструктор по умолчанию
	{
		_root = _iterator = nullptr;
		_all_symbols = _various_symbols = _write_symbols = 0;
		_key_symbols = 0;
		_encode_value = _bits = _degree = 0;
		_letter = '\0';
	}

	Huffman::~Huffman() // Деструктор по умолчанию
	{
		_frequency.clear();
		_summary_table.clear();
		_frequency_table.clear();
		_way.clear();
	}

	Huffman::unit::unit() // Конструктор для узлов по умолчанию
	{
		_symbol_frequency = 0;
		_symbol = '\0';
		_left = _right = nullptr;
	}

	Huffman::unit::unit(char symbol, uint32_t symbol_frequency) // Конструктор копирования для узла
	{
		_symbol_frequency = symbol_frequency;
		_symbol = symbol;
		_left = _right = nullptr;
	}

	Huffman::unit::unit(unit* left, unit* right) // Конструктор, соединяющий два узла в мини-дерево
	{
		_left = left;
		_right = right;
		_symbol_frequency = left->_symbol_frequency + right->_symbol_frequency;
		_symbol = '\0';
	}

	Huffman::unit::~unit() // Деструктор узла по умолчанию
	{
		delete _left;
		delete _right;
	}

	void Huffman::encode(std::string& in_file, std::string& out_file) // Сжатие
	{
		encodeOpenStreamRead(in_file); // Чтение символов файла
		makeTable(); // Составление таблицы шифрования
		saveKey(); // Сохранение таблицы шифрования
		encodeOpenStreamWrite(in_file, out_file); // Шифрование текста и запись его в новый файл
		cleanAll(); // Отчистка полей
	}

	void Huffman::decode(std::string& in_file, std::string& out_file, std::string& key_file) // Расшифровка
	{
		decodeOpenStreamRead(in_file, key_file); // Чтение сжатого файла и ключа
		decodeFile(in_file, out_file); // Запись расшифрованного текст в новый файл
		cleanAll(); // Отчистка полей
	}

	void Huffman::encodeOpenStreamRead(std::string& in_file) // Открытие потока чтения кодирования текста
	{
		std::ifstream stream(in_file, std::ios::binary); // Открытие потока в бинарном режиме
		encodeReader(stream); // Чтение из файла
		stream.close(); 
	}

	void Huffman::encodeReader(std::ifstream& in_stream) // Чтение до конца файла
	{
		while (!in_stream.eof())
		{
			encodeFilling(in_stream); // Заполнение таблиц данными
		}
	}

	void Huffman::encodeFilling(std::ifstream& in_stream) // Заполнение таблиц данными
	{
		char letter = in_stream.get(); // Чтение одного символа из файла
		_frequency[letter] += 1; // Подсчёт частоты
		_all_symbols += 1; // Счёт общего кол-ва символов
		if (_frequency[letter] == 1) _various_symbols += 1; // Счёт кол-ва различных символов
	}

	void Huffman::encodeOpenStreamWrite(std::string& in_file, std::string& out_file) // Открытие потоков для записи сжатого текста
	{
		std::ofstream out(out_file, std::ios::binary); // Поток для повторного чтения исходного текста
		std::ifstream in(in_file, std::ios::binary); // Поток для записи сжатого текста
		encodeReader(in, out); // Чтение исходного текста
		out.close();
		in.close();
	}

	void Huffman::encodeReader(std::ifstream& in_stream, std::ofstream& out_stream) // Повторное чтение исходного текста
	{
		while (!in_stream.eof()) 
		{
			encodeReaderEncode(out_stream, in_stream.get()); // Взятие сомвола и составление нового кода
		}
	}

	void Huffman::encodeReaderEncode(std::ofstream& out_file, const char letter) // Составление нового кода
	{
		for (const auto code : _summary_table[letter]) // Проход по вектору с новым кодом для символа
		{
			_encode_value |= code << (7 - _bits++); // Запись каждого бита в байтовую переменную
			if (_bits == 8) encodeReaderEncodeWrite(out_file); // После записи каждых 8-ми байтов символ добавляется в файл
		}
	}

	void Huffman::encodeReaderEncodeWrite(std::ofstream& out_file) // Запись сжатого кода в файл
	{
		out_file << _encode_value; // Запись кода в файл
		_bits = _encode_value = 0; // Обнуление значений
	}

	void Huffman::makeTable() // Создание таблицы кодов
	{
		for (const auto& i : _frequency) // Проход по каждом символу
		{
			unit* temp = new unit(i.first, i.second); // Создание узла
			_frequency_table.push_back(temp); // Добавление узла таблицу
		}
		makeTableTree(); // Создание дерева на основе таблицы
	}

	void Huffman::makeTableTree() // Создание дерева на основе таблицы
	{
		while (_frequency_table.size() > 1) // В таблице не остался только один узел (верхущка дерева)
		{
			_frequency_table.sort(compare()); // Таблица сортируется по возрастанию весов
			unit* head = new unit(makeTableTreeNodes(), makeTableTreeNodes()); // Два первых узла объединяются в поддерево
			_frequency_table.push_back(head); // Верхушка поддерева добавляется в лист
		}
		_root = _frequency_table.front(); // Теперь корень указывает на голову дерева
		makeWay(_root); // На основе дерева создаётся путь (код) для каждого символа
	}

	Huffman::unit* Huffman::makeTableTreeNodes() // Взятие первого узла из таблицы
	{
		unit* node = new unit();
		node = _frequency_table.front(); // Из таблицы берётся первый узел
		_frequency_table.pop_front(); // Удаляется из таблицы
		return node; // Сам узел возвращается
	}

	void Huffman::makeWay(unit* start) // Рекурсивный обход дерева для составления пути
	{
		if (start->_left != nullptr) { _way.push_back(false); makeWay(start->_left); } // Если символ левее - в его бинарный код добавляется 0
		if (start->_right != nullptr) { _way.push_back(true); makeWay(start->_right); } // Если символ правее - в код добавляется 1
		if (start->_left == nullptr && start->_right == nullptr) // Если найден сам символ...
			_summary_table[start->_symbol] = _way; // ...его код сохраняется в таблице
		if (_way.size() == 0) return; // Если нашли все символы: выход из рекурсии
		_way.pop_back(); // При раскручивании назад удаляется последний бит из пути
	}

	void Huffman::saveKey() // Сохранение ключа в файл
	{
		std::ofstream key_file("key.txt", std::ios::binary); // Открытие бинарного потока для ключа
		saveKeyAllSymbolsAmount(key_file, _all_symbols); // Запись кол-ва всех символов
		saveKeyAllSymbolsAmount(key_file, _various_symbols); // Запись кол-ва различных символов
		saveKeyAllSymbols(key_file); // Запись всех кодов букв
		key_file.close();
	}

	void Huffman::saveKeyAllSymbolsAmount(std::ofstream& key_file, uint32_t amount) // Запись числа в файл ключа
	{
		while (amount > 0) // Запись числа в развёрнутом виде. 823 = (r)328
		{
			key_file << amount % 10;
			amount /= 10;
		}
		key_file << static_cast<char>(127); // Запись разделителя
	}

	void Huffman::saveKeyAllSymbols(std::ofstream& key_file) // Запись всех кодов букв
	{
		for (const auto& symbol : _summary_table) // Проход по всем символам и их новым кодам
		{
			key_file << symbol.first; // Запись символа
			for (const auto& code : symbol.second) key_file << code; // Запись его кода
			key_file << static_cast<char>(127); // Запись разделителя
		}
	}

	void Huffman::decodeOpenStreamRead(std::string& in_file, std::string& key_file) // Открытие потока для чтения ключа
	{
		std::ifstream key(key_file);
		decodeOpenStreamReadAllSymbols(key); // Чтения кол-ва всех символов исходного текста
		decodeOpenStreamReadVariousSymbols(key); // Чтение кол-ва различных символов исходного текста
		decodeOpenStreamReadCodes(key); // Чтение всех кодов с последующем восстановлением исходной таблицы шифрования
		key.close();
	}

	void Huffman::decodeOpenStreamReadAllSymbols(std::ifstream& key_stream) // Чтения кол-ва всех символов исходного текста
	{
		char temp = key_stream.get();
		while (temp != static_cast<char>(127)) // Чтение цифр до разделителя и преобразование в развёрнутое число
		{
			_all_symbols += (static_cast<uint32_t>(temp) - 48) * static_cast<uint32_t>(pow(10, _degree++)); // (r)328 = 3 + (2 * 10) + (8 * 100) = 823
			temp = key_stream.get();
		}
	}

	void Huffman::decodeOpenStreamReadVariousSymbols(std::ifstream& key_stream) // Чтение кол-ва различных символов исходного текста
	{
		_degree = 0;
		char temp = key_stream.get();
		while (temp != static_cast<char>(127)) // Чтение числа аналогичным способом из decodeOpenStreamReadAllSymbols()
		{
			_various_symbols += (static_cast<uint32_t>(temp) - 48) * static_cast<uint32_t>(pow(10, _degree++));
			temp = key_stream.get();
		}
		_key_symbols = _various_symbols;
	}

	void Huffman::decodeOpenStreamReadCodes(std::ifstream& key_stream) // Чтение всех кодов с последующем восстановлением исходной таблицы шифрования
	{
		_iterator = new unit; // Итератора и...
		_root = _iterator; // ...новой головы
		while (_key_symbols-- > 0) makeTree(key_stream); // Пока не все различные символы добавлены в дерево
	}

	void Huffman::makeTree(std::ifstream& key_stream) // Добавление символа в дерево
	{
		char letter = key_stream.get(), code = key_stream.get(); // Чтение символа и его первого кода
		while (code != static_cast<char>(127)) // Пока не найден разделитель
		{
			if (code == '0') makeTreeLeft(); // Если код == 0, нужно идти влево
			else makeTreeRight(); // Иначе вправо
			code = key_stream.get(); // Взятие следующего кода
			if (code == static_cast<char>(127)) { _iterator->_symbol = letter; _iterator = _root; } // Если найден разделитель, то сохранение символа в дерево
		}
	}

	void Huffman::makeTreeLeft() // Переход влево
	{
		if (_iterator->_left == nullptr) // Если слева пусто
		{
			unit* left = new unit; // Создание узла влево
			_iterator->_left = left;
		}
		_iterator = _iterator->_left; // Если слева не пусто, то переход влево
	}

	void Huffman::makeTreeRight() // Переход вправо. Аналогично функции makeTreeLeft()
	{
		if (_iterator->_right == nullptr)
		{
			unit* left = new unit;
			_iterator->_right = left;
		}
		_iterator = _iterator->_right;
	}

	void Huffman::decodeFile(std::string& in_file, std::string& out_file) // Открытие поток для чтения сжатого файла и его декодирования
	{
		std::ifstream encode_file(in_file, std::ios::binary); // Поток со сжатым файлом
		std::ofstream original_file(out_file, std::ios::binary); // Поток для восстановления исходного файла на основе файла ключа
		_iterator = _root; // Начало прохода по дереву будет с головы
		_letter = encode_file.get(); // Чтение первого байта из сжатого файла
		while (decodeFileRead(encode_file, original_file)) {} // Пока не считаны все байты, обрабатывается каждый байт
	}

	bool Huffman::decodeFileRead(std::ifstream& encode_file, std::ofstream& original_file) // Обработка байта: восстановление исходного текста
	{
		if (!(_letter & (1 << (7 - _bits++)))) _iterator = _iterator->_left; // В зависимости от бита байта проход либо влево, либо враво по дереву
		else _iterator = _iterator->_right;
		if ((_iterator->_left == nullptr) && (_iterator->_right == nullptr)) // Если встретили символ...
		{
			if ((_write_symbols + 1) == _all_symbols) return false; // ...проверяется, все ли декодированы. Если не все, то...
			decodeFileWrite(original_file); // ...запись символа в результирующий файл
		}
		if (_bits == 8) { _letter = encode_file.get(); _bits = 0; } // Елли весь байт просмотрен, чтение нового байта из сжатого файла
		return true;
	}

	void Huffman::decodeFileWrite(std::ofstream& original_file) // Запись символа в резултирующий файл
	{
		original_file << _iterator->_symbol;
		_iterator = _root; // Возврат на верхушку дерева
		_write_symbols++; // Увеличения кол-ва декодированных символов
	}

	void Huffman::cleanAll() // Отчистка всех полей и контейнеров
	{
		cleanData(); // Отчистка только контейнеров
		cleanVars(); // Отчистка только полей
	}

	void Huffman::cleanData() // Отчистка только контейнеров
	{
		_frequency.clear();
		_summary_table.clear();
		_frequency_table.clear();
		_way.clear();
	}

	void Huffman::cleanVars() // Отчистка только полей
	{
		_root = _iterator = nullptr;
		_all_symbols = _various_symbols = _write_symbols = 0;
		_key_symbols = 0;
		_encode_value = _bits = _degree = 0;
		_letter = '\0';
	}
}
