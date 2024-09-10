#include <QRandomGenerator>

#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
	central_widget = new QWidget(this);
	grid_layout = new QGridLayout(central_widget);

	setCentralWidget(central_widget);

	createField();
	createMenu();
	grid_layout->setSpacing(0);
}

MainWindow::~MainWindow() {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			delete cells[row][col];
		}
	}

	delete grid_layout;
	delete central_widget;
}

void MainWindow::createField() {
	cells.resize(rows, std::vector<Cell*>(cols, nullptr));

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			Cell* cell = new Cell(this);
			grid_layout->addWidget(cell, row, col);
			cells[row][col] = cell;
		}
	}

	int placedMines = 0;
	while (placedMines < mine_сount) {
		int randomRow = QRandomGenerator::global()->bounded(rows);
		int randomCol = QRandomGenerator::global()->bounded(cols);

		Cell* cell = cells[randomRow][randomCol];

		if (!cell->hasMine()) {
			cell->setMine();
			++placedMines;
		}
	}
}

void MainWindow::createMenu() {
	QMenuBar* menu_bar = new QMenuBar(this);
	setMenuBar(menu_bar);

	QMenu* game_menu = new QMenu("Game", this);
	menu_bar->addMenu(game_menu);

	QAction* quit_action = new QAction("Quit", this);
	connect(quit_action, &QAction::triggered, this, &MainWindow::close);
	game_menu->addAction(quit_action);
}
