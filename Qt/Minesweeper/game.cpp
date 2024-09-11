#include <QRandomGenerator>

#include "game.h"
#include "menu.h"
#include "cell.h"

Game::Game(QWidget *parent): QMainWindow(parent){
	central_widget = new QWidget(this);
	grid_layout = new QGridLayout(central_widget);

	grid_layout->setContentsMargins(0, 0, 0, 0);

	setCentralWidget(central_widget);

	createField();
	createMenu();
	grid_layout->setSpacing(0);
}

Game::~Game() {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			delete cells[row][col];
		}
	}

	delete grid_layout;
	delete central_widget;
}

void Game::createField() {
	cells.resize(rows, std::vector<Cell*>(columns, nullptr));

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			Cell* cell = new Cell(this);
			grid_layout->addWidget(cell, row, col);
			cells[row][col] = cell;
		}
	}

	int placedMines = 0;
	while (placedMines < mine_сount) {
		int randomRow = QRandomGenerator::global()->bounded(rows);
		int randomCol = QRandomGenerator::global()->bounded(columns);

		Cell* cell = cells[randomRow][randomCol];

		if (!cell->hasMine()) {
			cell->setMine();
			++placedMines;
		}
	}
}

void Game::createMenu() {
	QMenuBar* menu_bar = new QMenuBar(this);
	setMenuBar(menu_bar);

	QMenu* game_menu = new QMenu("Game", this);
	menu_bar->addMenu(game_menu);

	QAction* menu_action = new QAction("Menu", this);
	connect(menu_action, &QAction::triggered, this, &Game::returnToStartMenu);
	game_menu->addAction(menu_action);

	QAction* quit_action = new QAction("Quit", this);
	connect(quit_action, &QAction::triggered, this, &Game::close);
	game_menu->addAction(quit_action);
}

void Game::returnToStartMenu() {
	Menu *start_menu = new Menu();
	start_menu->show();

	this->close();
}

const int Game::getRows() const {return rows;}
const int Game::getColumns() const {return columns;};
