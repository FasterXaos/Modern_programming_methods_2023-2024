#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMenuBar>

#include "cell.h"

class Game : public QMainWindow{
		Q_OBJECT

	private:
		const int rows = 6;
		const int columns = 12;
		const int mine_сount = 40;
		std::vector<std::vector<Cell*>> cells;

		QWidget* central_widget;
		QGridLayout* grid_layout;

		void createField();
		void createMenu();

	public:
		Game(QWidget *parent = nullptr);
		~Game();

		const int getRows() const;
		const int getColumns() const;

	private slots:
		void returnToStartMenu();
};
