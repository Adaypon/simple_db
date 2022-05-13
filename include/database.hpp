#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <regex>
#include <filesystem>

class DataBase {
private:
	std::map<std::string, std::string> _data;
	std::string _fileName;
public:
	explicit DataBase(std::string path = "storage.txt");
	~DataBase();

	/**
	 * Сохранение данных на диск
	 */
	void save();

	/**
	 * Получить список всех ключей по шаблону
	 * 
	 * @return вектор ключей 
	 */	
	std::vector<std::string> keys(std::string pattern) const;

	/**
	 * Проверить сущестование ключа
	 */
	bool exists(std::string key) const;

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
	std::string get(std::string key) const;


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