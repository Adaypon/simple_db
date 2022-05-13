#include "database.hpp"

DataBase::DataBase(std::string path) :
	_fileName(path)
{
	if (std::filesystem::exists(_fileName)) {
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
				throw std::invalid_argument("Unable to load the file");
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
}

DataBase::~DataBase() {
	this->save();
}

void DataBase::save() {
	std::ofstream fout;
	fout.open(_fileName);
	if (fout.is_open()) {
		for (const auto& elem : _data) {
			fout << elem.first << "=" << elem.second << std::endl;
		}
	}
	else {
		std::cerr << "Can't open file for saving" << std::endl;
	}
	fout.close();
}

std::vector<std::string> DataBase::keys(std::string pattern) const {
	// parse pattern to regex format
	std::string regStr = "^" + pattern + "$";
	regStr = std::regex_replace(regStr, std::regex("\\*"), ".*");
	regStr = std::regex_replace(regStr, std::regex("\\?"), ".?");
	const std::regex regular(regStr);
	
	std::vector<std::string> keys;
	for (const auto& elem : _data) {
		std::smatch result;
		if (std::regex_search(elem.first, result, regular)) {
			keys.push_back(elem.first);
		}
	}
	return keys;
}

bool DataBase::exists(std::string key) const {
	auto it = _data.find(key);
	return it != _data.end();
}

void DataBase::set(std::string key, std::string value) {
	if (exists(key)) {
		_data.at(key) = value;
	}
	else {
		_data.emplace(key, value);
	}
}

std::string DataBase::get(std::string key) const {
	if (exists(key) && !(_data.at(key).empty())) {
		return _data.at(key);
	}
	return "null";
}

bool DataBase::del(std::string key) {
	if (exists(key)) {
		auto it = _data.find(key);
		if (!(it->second.empty())) {
			_data.erase(key);
			return true;
		}
	}
	return false;
}

void DataBase::flushAll() {
	_data.clear();
}

void DataBase::printMap() {
	for (const auto& [key, value] : _data) {
		std::cout << '[' << key << "] = " << value << "; ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}