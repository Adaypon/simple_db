#include "database.hpp"
#include <cassert>

int main() {
	DataBase db("storage.txt");
	db.printMap();
	
	std::cout << "KEYS: ";
	auto k = db.keys();
    for (size_t i = 0; i < k.size(); ++i) {
        std::cout << k[i] << " ";
    }
    std::cout << std::endl;
	
	assert(db.exists("test") == true);
	assert(db.exists("test2") == false);

	db.set("test", "new");
	db.printMap();
	db.set("name", "Vasya");
	db.printMap();

	std::cout << db.del("name") << std::endl;
	db.printMap();

	std::cout << db.del("empty") << std::endl;
	db.printMap();

	db.flushAll();
	db.printMap();
	
	return 0;
}