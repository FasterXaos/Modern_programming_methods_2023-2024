#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QMenuBar>

#include "cell.h"
#include "timer.h"

namespace AED {
	class Game : public QMainWindow{
			Q_OBJECT

		private:
			const int rows = 6;
			const int columns = 6;
			const int mineCount = 5;
			Cell*** cells;

			QWidget* centralWidget;

			QVBoxLayout* mainVLayout;
			QHBoxLayout* topHLayout;
			QGridLayout* fieldGLayout;

			QLabel* minesCounter;
			QPushButton* resetButton;
			QLabel* timerLabel;
			Timer* gameTimer;

			void createField();
			void createMenu();
			void openAdjacentCells(int row, int column);
			void restartGame();
			void showMines();

		public:
			Game(QWidget *parent = nullptr);
			~Game();

			const int getRows() const {return rows;}
			const int getColumns() const {return columns;};

		signals:
			void gameLost();

		private slots:
			void onCheckForWin();
			void onFlagAdded();
			void onFlagRemoved();
			void onGameLost();
			void onResetButtonPressed();
			void onResetButtonReleased();
			void onReturnToStartMenu();
	};
}
