#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

#include "cell.h"
#include "timer.h"

class Game : public QMainWindow{
		Q_OBJECT

	private:
		const int rows = 10;
		const int columns = 10;
		const int mine_сount = 5;
		std::vector<std::vector<Cell*>> cells;

		QWidget* central_widget;

		QVBoxLayout* main_layout;
		QHBoxLayout* top_layout;
		QGridLayout* field_layout;

		QLabel* mines_counter;
		QPushButton* reset_button;
		QLabel* timer_label;
		Timer* game_timer;

		void createField();
		void createMenu();
		void openAdjacentCells(int row, int column);
		void showAllMines();
		void restartGame();

	public:
		Game(QWidget *parent = nullptr);
		~Game();

		const int getRows() const {return rows;}
		const int getColumns() const {return columns;};

	signals:
		void gameLost();

	private slots:
		void returnToStartMenu();
		void onGameLost();
		void onResetButtonPressed();
		void onResetButtonReleased();
		void onFlagAdded();
		void onFlagRemoved();
		void checkForWin();
};
