#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMenuBar>

#include "cell.h"

class MainWindow : public QMainWindow{
		Q_OBJECT

	private:
		const int rows = 16;
		const int cols = 16;
		const int mine_сount = 40;
		std::vector<std::vector<Cell*>> cells;

		QWidget* central_widget;
		QGridLayout* grid_layout;

		void createField();
		void createMenu();

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
