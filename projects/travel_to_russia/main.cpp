#include <iostream>

#include "menu_func.hpp"
#include "menu_items.hpp"

int main() {
	std::cout << "Здравствуй!" << std::endl;
	const EAbrakhin::MenuItem* current = &EAbrakhin::MAIN;
	do {
		current = current->func(current);
	} while (true);

	return 0;
}
