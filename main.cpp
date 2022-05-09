#include "database.hpp"

int main() {
	DataBase db("storage.txt");
	db.printMap();
	return 0;
}