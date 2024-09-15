#pragma once

#include <QPushButton>

namespace AED {
	class Game;

	class Cell : public QPushButton {
		Q_OBJECT

		private:
			friend class Game;

			const int row;
			const int column;
			int surroundingMinesCount;

			QPixmap hidenIcon;
			QPixmap openedIcon;
			QPixmap pressedIcon;


			bool hasMine;
			bool isBlocked;
			bool isFlagged;
			bool isOpened;

		public:
			Cell(int row, int column, QWidget *parent = nullptr);
			void openCell();
			void setMine();
			void showCell();

		protected:
			void mousePressEvent(QMouseEvent* event) override;
			void resizeEvent(QResizeEvent *event) override;

		signals:
			void checkForWin();
			void emptyCellOpened(int row, int column);
			void flagAdded();
			void flagRemoved();
			void mineClicked();
			void openedCellClicked(int row, int column);

		private slots:
			void onCellPressed();
			void onCellReleased();
	};
}
