#include <QApplication>

#include "menu.h"
#include "game.h"
#include "settings.h"

namespace AED {
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

		vLayout->setSpacing(10);
		setLayout(vLayout);

		connect(playButton, &QPushButton::clicked, this, &Menu::onPlayButtonClicked);
		connect(settingsButton, &QPushButton::clicked, this, &Menu::onSettingsButtonClicked);
		connect(exitButton, &QPushButton::clicked, this, &Menu::onExitButtonClicked);
	}

	void Menu::onPlayButtonClicked() {
		Game *gameWindow = new Game();
		gameWindow->resize(gameWindow->getColumns() * 16, gameWindow->getRows() * 16);
		gameWindow->setWindowIcon(QIcon(":/images/minesweeper_icon.png"));
		gameWindow->setWindowTitle("Minesweeper");
		gameWindow->show();

		this->close();
	}

	void Menu::onSettingsButtonClicked() {
		Settings *settingsWindow = new Settings();
		settingsWindow->setWindowIcon(QIcon(":/images/minesweeper_icon.png"));
		settingsWindow->setWindowTitle("Minesweeper");
		settingsWindow->show();

		this->close();
	}

	void Menu::onExitButtonClicked() {
		QApplication::quit();
	}
}
