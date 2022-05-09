#include <iostream>
#include <sstream>
#include <algorithm>
#include "database.hpp"

std::string startText = "=== Simple key-value database ===\n\n";
std::string help = "Type HELP command for more info.\n";
std::string helpPrint = "PRINT - Print all keys and values.\n";
std::string helpKeys = "KEYS pattern - Returns all keys matching pattern.\n";
std::string helpSet = "SET key value - Set key to hold the string value. If key already holds a value, it is overwritten.\n";
std::string helpGet = "GET key - Get the value of key. If the key does not exist, returns string null.\n";
std::string helpDel = "DEL key - Delete key and the value of the key.\n";
std::string helpFlush = "FLUSHALL - Remove all keys from database.\n";
std::string helpQuit = "QUIT - close the database.\n";

void clearScreen() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

std::vector<std::string> parseCommand(std::string str) {
	std::stringstream ss(str);
	std::string tmp;
	std::vector<std::string> parsedString;
	while(std::getline(ss, tmp, ' ')) {
		parsedString.push_back(tmp);
	}
	if (!parsedString.empty())
		std::transform(parsedString[0].begin(), parsedString[0].end(), parsedString[0].begin(), [](unsigned char c){ return std::tolower(c); });
	return parsedString;
}

// TODO make handler class
int main() {
	try {
		DataBase db;
		bool quitFlag = false;
		clearScreen();
		std::cout << startText;
		std::cout << help << std::endl;
		
		std::string input = "";
		while (!quitFlag) {
			std::cout << "> ";
			std::getline(std::cin, input);
			if (!input.empty()) {
				std::vector<std::string> commands = parseCommand(input);
				if (commands[0] == "help") {
					clearScreen();
					std::cout << helpPrint << helpKeys << helpSet << helpGet << helpDel << helpFlush << helpQuit << std::endl;
				}
				else if (commands[0] == "keys" && commands.size() == 2) {
					std::vector<std::string> keys = db.keys(commands[1]);
					if (!keys.empty()) {
						std::cout << "KEYS: ";
						for (const auto& key : keys) {
							std::cout << key << " ";
						}
						std::cout << std::endl;
					}
				}
				else if (commands[0] == "exists" && commands.size() == 2) {
					std::cout << std::boolalpha << db.exists(commands[1]) << std::endl;
				}
				else if (commands[0] == "set" && commands.size() == 3) {
					db.set(commands[1], commands[2]);
					db.save();
					std::cout << "OK" << std::endl;
				}
				else if (commands[0] == "get" && commands.size() == 2) {
					std::cout << db.get(commands[1]) << std::endl;
				}
				else if (commands[0] == "del" && commands.size() == 2) {
					std::cout << std::boolalpha << db.del(commands[1]) << std::endl;
					db.save();
				}
				else if (commands[0] == "flushall" && commands.size() == 1) {
					db.flushAll();
					db.save();
					std::cout << "FLUSH" << std::endl;
				}
				else if (commands[0] == "print" && commands.size() == 1) {
					db.printMap();
				}
				else if (commands[0] == "quit" && commands.size() == 1) {
					quitFlag = true;
				}
				else {
					std::cout << "UNKNOWN COMMAND OR WRONG PARAMETERS" << std::endl;
				}
			}
		}
		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}