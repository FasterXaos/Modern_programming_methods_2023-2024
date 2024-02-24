#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"

namespace EAbrakhin {
	const EAbrakhin::MenuItem* show_menu(const EAbrakhin::MenuItem* current) {
		for (int i = 1; i < current->children_count; ++i) {
			std::cout << current->children[i]->title << std::endl;
		}
		std::cout << current->children[0]->title << std::endl;
		std::cout << "Путешествие > ";

		int user_input;
		std::cin >> user_input;
		std::cout << std::endl;

		return current->children[user_input];
	}

	const EAbrakhin::MenuItem* exit(const EAbrakhin::MenuItem* current) {
		std::exit(0);
	}

	const EAbrakhin::MenuItem* go_back(const EAbrakhin::MenuItem* current) {
		return current->parent->parent;
	}

	const EAbrakhin::MenuItem* go_to_altai(const EAbrakhin::MenuItem* current) {
		std::cout << current->title << std::endl << std::endl;
		return current->parent;
	}
	const EAbrakhin::MenuItem* go_to_golden_ring_of_russia(const EAbrakhin::MenuItem* current) {
		std::cout << current->title << std::endl << std::endl;
		return current->parent;
	}

	const EAbrakhin::MenuItem* go_to_vladivostok(const EAbrakhin::MenuItem* current) {
		std::cout << current->title << std::endl << std::endl;
		return current->parent;
	}
	const EAbrakhin::MenuItem* go_to_sakhalin(const EAbrakhin::MenuItem* current) {
		std::cout << current->title << std::endl << std::endl;
		return current->parent;
	}
	const EAbrakhin::MenuItem* go_to_khabarovsk(const EAbrakhin::MenuItem* current) {
		std::cout << current->title << std::endl << std::endl;
		return current->parent;
	}
}
