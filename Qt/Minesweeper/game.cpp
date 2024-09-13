#include <QRandomGenerator>
#include <QFontDatabase>
#include <QResizeEvent>

#include "game.h"
#include "menu.h"
#include "cell.h"

Game::Game(QWidget *parent): QMainWindow(parent){
	central_widget = new QWidget(this);
	main_layout = new QVBoxLayout(central_widget);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);


	int numbers_font_id = QFontDatabase::addApplicationFont("assets/fonts/digital_numbers.ttf");
	QString font_family = QFontDatabase::applicationFontFamilies(numbers_font_id).at(0);
	QFont numbers_font = QFont(font_family, 14);


	QWidget* top_panel = new QWidget(this);
	top_layout = new QHBoxLayout(top_panel);
	top_panel->setContentsMargins(0, 0, 0, 0);
	top_panel->setStyleSheet("background-color: #c0c0c0;");

	mines_counter = new QLabel("Mines:" + QString::number(mine_сount), this);
	mines_counter->setFont(numbers_font);
	mines_counter->setStyleSheet("color: red;");
	top_layout->addWidget(mines_counter);

	reset_button = new QPushButton(this);
	reset_button->setFixedSize(48, 48);
	reset_button->setIcon(QIcon("assets/images/minesweeper_button.png"));
	reset_button->setIconSize(QSize(48, 48));
	top_layout->addStretch(0);
	top_layout->addWidget(reset_button);
	top_layout->addStretch(0);

	timer_label = new QLabel("Time:000", this);
	timer_label->setFont(numbers_font);
	timer_label->setStyleSheet("color: red;");
	game_timer = new Timer(timer_label, this);
	game_timer->start();
	top_layout->addWidget(timer_label);


	QWidget* field_widget = new QWidget(this);
	field_layout = new QGridLayout(field_widget);
	field_layout->setContentsMargins(0, 0, 0, 0);
	field_layout->setSpacing(0);


	main_layout->addWidget(top_panel);
	main_layout->addWidget(field_widget);

	setCentralWidget(central_widget);

	createField();
	createMenu();


	connect(reset_button, &QPushButton::pressed, this, &Game::onResetButtonPressed);
	connect(reset_button, &QPushButton::released, this, &Game::onResetButtonReleased);
	connect(game_timer, &Timer::timeIsUp, this, &Game::onGameLost);
	connect(this, &Game::gameLost, this, &Game::onGameLost);
}

Game::~Game() {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			delete cells[row][col];
		}
	}

	cells.clear();

	delete central_widget;
	delete main_layout;
	delete top_layout;
	delete field_layout;

	delete mines_counter;
	delete reset_button;
	delete timer_label;
	delete game_timer;
}

void Game::createField() {
	cells.resize(rows, std::vector<Cell*>(columns, nullptr));

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			Cell* cell = new Cell(row, col, this);
			field_layout->addWidget(cell, row, col);
			cells[row][col] = cell;

			connect(cell, &Cell::openAdjacentCells, this, &Game::openAdjacentCells);
			connect(cell, &Cell::mineClicked, this, &Game::onGameLost);
			connect(cell, &Cell::flagAdded, this, &Game::onFlagAdded);
			connect(cell, &Cell::flagRemoved, this, &Game::onFlagRemoved);
		}
	}

	int placed_mines = 0;
	while (placed_mines < mine_сount) {
		int random_row = QRandomGenerator::global()->bounded(rows);
		int random_col = QRandomGenerator::global()->bounded(columns);

		Cell* cell = cells[random_row][random_col];

		if (!cell->hasMine()) {
			cell->setMine();
			++placed_mines;
		}
	}

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			if (cells[row][col]->hasMine()) {
				continue;
			}

			int surrounding_mines = 0;
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					int new_row = row + i;
					int new_col = col + j;

					if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < columns) {
						if (cells[new_row][new_col]->hasMine()) {
							++surrounding_mines;
						}
					}
				}
			}

			cells[row][col]->setSurroundingMinesCount(surrounding_mines);
			QString icon_path = "assets/images/cell_" + QString::number(surrounding_mines) + ".png";
			cells[row][col]->setOpenedIcon(QPixmap(icon_path));
		}
	}
}

void Game::createMenu() {
	QMenuBar* menu_bar = new QMenuBar(this);
	menu_bar->setStyleSheet("QMenuBar {spacing: 0px;}");
	setMenuBar(menu_bar);

	QMenu* game_menu = new QMenu("Game", this);
	game_menu->setStyleSheet("QMenu::item {padding: 5px 5px;}");
	menu_bar->addMenu(game_menu);

	QAction* menu_action = new QAction("Menu", this);
	connect(menu_action, &QAction::triggered, this, &Game::returnToStartMenu);
	game_menu->addAction(menu_action);

	QAction* quit_action = new QAction("Quit", this);
	connect(quit_action, &QAction::triggered, this, &Game::close);
	game_menu->addAction(quit_action);
}

void Game::openAdjacentCells(int row, int col) {
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			int new_row = row + i;
			int new_col = col + j;

			if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < columns) {
				cells[new_row][new_col]->openCell();
			}
		}
	}
}

void Game::showAllMines() {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			Cell* cell = cells[row][col];
			if (cell->hasMine()) {
				if (cell->isFlagged()) {
					continue;
				}
				cell->showCell();
			} else if (cell->isFlagged()) {
				cell->setHidenIcon(QPixmap("assets/images/cell_12.png"));
				QPixmap scaled_pixmap = cell->getHidenIcon().scaled(cell->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
				cell->setIcon(QIcon(scaled_pixmap));
			}
		}
	}
}

void Game::restartGame() {

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			delete cells[row][col];
		}
	}
	cells.clear();

	mines_counter->setText("Mines:" + QString::number(mine_сount));
	mines_counter->setStyleSheet("color: red;");

	reset_button->setIcon(QIcon("assets/images/minesweeper_button.png"));

	timer_label->setStyleSheet("color: red;");
	game_timer->reset();

	createField();

	game_timer->start();
}

void Game::returnToStartMenu() {
	Menu *start_menu = new Menu();
	start_menu->show();

	this->close();
}

void Game::onResetButtonPressed() {
	reset_button->setIcon(QIcon("assets/images/minesweeper_button_pressed.png"));
}

void Game::onResetButtonReleased() {
	reset_button->setIcon(QIcon("assets/images/minesweeper_button.png"));
	restartGame();
}

void Game::onGameLost(){
	showAllMines();
	reset_button->setIcon(QIcon("assets/images/minesweeper_game_over.png"));
	game_timer->stop();

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			cells[row][col]->setBlock(true);
		}
	}
};

void Game::onFlagAdded() {
	int remaining_mines = mines_counter->text().mid(6).toInt();
	remaining_mines--;
	mines_counter->setText("Mines:" + QString::number(remaining_mines));

	if (remaining_mines == 0) {
		checkForWin();
	}
}

void Game::onFlagRemoved() {
	int remaining_mines = mines_counter->text().mid(6).toInt();
	mines_counter->setText("Mines:" + QString::number(++remaining_mines));

	if (remaining_mines == 0) {
		checkForWin();
	}
}

void Game::checkForWin() {
	bool won = true;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			Cell* cell = cells[row][col];
			if ((cell->hasMine() && !cell->isFlagged()) || (!cell->hasMine() && cell->isFlagged())) {
				won = false;
				break;
			}
		}
		if (!won) break;
	}

	if (won) {
		game_timer->stop();
		mines_counter->setStyleSheet("color: green;");
		timer_label->setStyleSheet("color: green;");

		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				cells[row][col]->setBlock(true);
			}
		}
	}
}
