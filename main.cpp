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

	std::cout << "\"" << db.get("key") << "\"" << std::endl;
	
	std::cout << "\"" << db.get("name") << "\"" << std::endl;

	std::cout << "\"" << db.get("empty") << "\"" << std::endl;

	db.set("space", " ");
	std::cout << "\"" << db.get("space") << "\"" << std::endl;
	
	return 0;
}