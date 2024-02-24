#pragma once

#include "menu.hpp"

namespace EAbrakhin {

	const MenuItem* show_menu(const MenuItem*);

	const MenuItem* exit(const MenuItem* current);
	const MenuItem* go_back(const MenuItem* current);

	const MenuItem* go_to_altai(const MenuItem* current);
	const MenuItem* go_to_golden_ring_of_russia(const MenuItem* current);

	const MenuItem* go_to_vladivostok(const MenuItem* current);
	const MenuItem* go_to_sakhalin(const MenuItem* current);
	const MenuItem* go_to_khabarovsk(const MenuItem* current);
}
