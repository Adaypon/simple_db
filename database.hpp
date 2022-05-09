#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <regex>

class DataBase {
private:
	std::map<std::string, std::string> _data;
	std::string _fileName;
	const std::vector<std::string> _validBoolTrueNames = {"true", "on", "yes", "y", "1"};
public:
	explicit DataBase(std::string path);
	~DataBase() = default;

	/**
	 * Сохранение данных на диск
	 */
	void save();

	/**
	 * Получить список всех ключей по шаблону
	 * 
	 * @return вектор ключей 
	 */	
	std::vector<std::string> keys() const;

	/**
	 * Установить значение по ключу.
	 * Если ключ <key> существует, перезаписывает значение
	 * 
	 * @param key ключ
	 * @param value значение
	 */
	void set(std::string key, std::string value);

	/**
	 * Получить значение по ключу.
	 * Если значения не существует, возвращает строку "null"
	 * 
	 * @param key ключ
	 */
	std::string get(std::string key, std::string defaultValue = "null") const;


	/**
	 * Удалить ключ и значение по ключу
	 * 
	 * @param key ключ
	 * @return false в случае если значения нет, true в случае успешного выполнения
	 */
	bool del(std::string key);
	
	/**
	 * Удалить все ключи и значения
	 */
	void flushAll();

	/**
	 * Вывести все ключи и значения
	 */ 
	void printMap();
};

DataBase::DataBase(std::string path) :
	_fileName(path)
{
	std::string str;
	std::vector<std::string> fileCache;

	std::ifstream fin;
	fin.open(_fileName);
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (getline(fin, str) && !(str.length() == 1 && isspace(str[0]))) {
				fileCache.push_back(str);
			}
		}
	}
	else {
		std::cerr << "Can't open file " << _fileName << std::endl;
		// TODO throw exception
	}
	fin.close();

	std::string keyStr;
	std::string valueStr;

	for (const auto& elem : fileCache) {
		// inserting key
		size_t first = 0;
		size_t last = elem.find('=');
		keyStr = elem.substr(first, last);

		// inserting value
		std::swap(first, last);
		++first;
		last = elem.size() - 1;

		valueStr = elem.substr(first, last);
		if (!valueStr.empty() && valueStr[valueStr.size() - 1] == '\r') {
			valueStr.erase(valueStr.size() - 1);
		}

		_data.emplace(keyStr, valueStr);
	}

}

void DataBase::printMap() {
	for (const auto& [key, value] : _data) {
		std::cout << '[' << key << "] = " << value << "; ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}