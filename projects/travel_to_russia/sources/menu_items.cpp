#include "menu_func.hpp"
#include "menu_items.hpp"

const EAbrakhin::MenuItem EAbrakhin::FAR_EAST_VLADIVOSTOK{
	"1 - Владивосток", EAbrakhin::go_to_vladivostok,&EAbrakhin::RUTRAVEL_FAR_EAST
};

const EAbrakhin::MenuItem EAbrakhin::FAR_EAST_SAKHALIN{
	"2 - Сахалин", EAbrakhin::go_to_sakhalin,&EAbrakhin::RUTRAVEL_FAR_EAST
};

const EAbrakhin::MenuItem EAbrakhin::FAR_EAST_KHABAROVSK{
	"3 - Хабаровск", EAbrakhin::go_to_khabarovsk,&EAbrakhin::RUTRAVEL_FAR_EAST
};

const EAbrakhin::MenuItem EAbrakhin::FAR_EAST_GO_BACK{
	"0 - Выйти в предыдущее меню", EAbrakhin::go_back,&EAbrakhin::RUTRAVEL_FAR_EAST
};

namespace {
	const EAbrakhin::MenuItem* fas_east_children[] = {
		&EAbrakhin::FAR_EAST_GO_BACK,
		&EAbrakhin::FAR_EAST_VLADIVOSTOK,
		&EAbrakhin::FAR_EAST_SAKHALIN,
		&EAbrakhin::FAR_EAST_KHABAROVSK,
	};
	const int fas_east_size = sizeof(fas_east_children) / sizeof(fas_east_children[0]);
}

const EAbrakhin::MenuItem EAbrakhin::RUTRAVEL_FAR_EAST{
	"1 - Дальний Восток", EAbrakhin::show_menu , &EAbrakhin::RUTRAVEL, fas_east_children, fas_east_size
};

const EAbrakhin::MenuItem EAbrakhin::RUTRAVEL_ALTAI{
	"2 - Алтай",  EAbrakhin::go_to_altai , &EAbrakhin::RUTRAVEL
};

const EAbrakhin::MenuItem EAbrakhin::RUTRAVEL_GOLDEN_RING_OF_RUSSIA{
	"3 - Золотое Кольцо России",  EAbrakhin::go_to_golden_ring_of_russia ,&EAbrakhin::RUTRAVEL
};

const EAbrakhin::MenuItem EAbrakhin::RUTRAVEL_TRAVEL_GO_BACK{
	"0 - Выйти в главное меню", EAbrakhin::go_back ,&EAbrakhin::RUTRAVEL
};

namespace {
	const EAbrakhin::MenuItem* travel_children[] = {
		&EAbrakhin::RUTRAVEL_TRAVEL_GO_BACK,
		&EAbrakhin::RUTRAVEL_FAR_EAST,
		&EAbrakhin::RUTRAVEL_ALTAI,
		&EAbrakhin::RUTRAVEL_GOLDEN_RING_OF_RUSSIA
	};
	const int travel_size = sizeof(travel_children) / sizeof(travel_children[0]);
}

const EAbrakhin::MenuItem EAbrakhin::RUTRAVEL{
	"1- Путешествовать по России", EAbrakhin::show_menu, &EAbrakhin::MAIN, travel_children, travel_size
};

const EAbrakhin::MenuItem EAbrakhin::END{
	"0 - Закончить путешествие", EAbrakhin::exit, &EAbrakhin::MAIN
};

namespace {
	const EAbrakhin::MenuItem* main_children[] = {
		&EAbrakhin::END,
		&EAbrakhin::RUTRAVEL
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}


const EAbrakhin::MenuItem EAbrakhin::MAIN{
	nullptr, EAbrakhin::show_menu, nullptr, main_children, main_size
};
