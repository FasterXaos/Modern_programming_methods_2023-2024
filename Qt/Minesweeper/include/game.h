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
			int rows = 9;
			int columns = 12;
			int mineCount = 14;
			Cell*** cells;

			QWidget* centralWidget;

			QVBoxLayout* mainVLayout;
			QHBoxLayout* topHLayout;
			QGridLayout* fieldGLayout;

			QLabel* minesCounter;
			QPushButton* resetButton;
			QLabel* timerLabel;
			Timer* gameTimer;

		public:
			Game(QWidget *parent = nullptr);
			~Game();

			const int getRows() const {return rows;}
			const int getColumns() const {return columns;};

		private:
			void createField();
			void createMenu();
			void openAdjacentCells(int row, int column);
			void restartGame(int newRows, int newColumns, int newMineCount);
			void showMines();

		signals:
			void gameLost();

		private slots:
			void onBeginnerSelected();
			void onCheckForWin();
			void onCustomSelected();
			void onExpertSelected();
			void onFlagAdded();
			void onFlagRemoved();
			void onGameLost();
			void onIntermediateSelected();
			void onOpenedCellClicked(int row, int column);
			void onRecordsSelected();
			void onResetButtonPressed();
			void onResetButtonReleased();
			void onRestartGame();
			void onReturnToStartMenu();
	};
}
