#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
	central_widget = new QWidget(this);
	grid_layout = new QGridLayout(central_widget);

	setCentralWidget(central_widget);

	for (int row = 0; row < 16; ++row) {
			for (int col = 0; col < 16; ++col) {
				Cell* cell = new Cell(this);
				grid_layout->addWidget(cell, row, col);
			}
		}

	grid_layout->setSpacing(0);
}

MainWindow::~MainWindow() {
	delete grid_layout;
	delete central_widget;
}
