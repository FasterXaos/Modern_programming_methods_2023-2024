#include <QApplication>

#include "menu.h"
#include "game.h"
#include "settings.h"

Menu::Menu(QWidget *parent) : QWidget(parent) {
	QPushButton *playButton = new QPushButton("Play", this);
	QPushButton *settingsButton = new QPushButton("Settings", this);
	QPushButton *recordsButton = new QPushButton("Records", this);
	QPushButton *exitButton = new QPushButton("Quit", this);

	playButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	settingsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	recordsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout *vLayout = new QVBoxLayout(this);
	vLayout->addWidget(playButton);
	vLayout->addWidget(settingsButton);
	vLayout->addWidget(recordsButton);
	vLayout->addWidget(exitButton);

	vLayout->setContentsMargins(10, 10, 10, 10);
	vLayout->setSpacing(10);
	setMinimumSize(150, 200);

	setLayout(vLayout);

	connect(playButton, &QPushButton::clicked, this, &Menu::onPlayButtonClicked);
	connect(settingsButton, &QPushButton::clicked, this, &Menu::onSettingsButtonClicked);
	connect(exitButton, &QPushButton::clicked, this, &Menu::onExitButtonClicked);
}

void Menu::onPlayButtonClicked() {
	Game *game_mindow = new Game();
	game_mindow->resize(game_mindow->getColumns() * 32, game_mindow->getRows() * 32);
	game_mindow->setWindowIcon(QIcon("assets/images/minesweeper_icon.png"));
	game_mindow->setWindowTitle("Minesweeper");
	game_mindow->show();

	this->close();
}

void Menu::onSettingsButtonClicked() {
	Settings *settings_window = new Settings();
	settings_window->setWindowIcon(QIcon("assets/images/minesweeper_icon.png"));
	settings_window->setWindowTitle("Minesweeper");
	settings_window->show();

	this->close();
}

void Menu::onExitButtonClicked() {
	QApplication::quit();
}
