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

	return 0;
}