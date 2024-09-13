#pragma once

#include <QPushButton>

class Cell : public QPushButton {
	Q_OBJECT

	private:
		const int row;
		const int column;

		int surrounding_mines_count;

		QPixmap hiden_icon;
		QPixmap opened_icon;
		QPixmap pressed_icon;

		bool is_opened;
		bool has_mine;
		bool is_flagged;
		bool is_blocked;

	public:
		Cell(int row, int column, QWidget *parent = nullptr);
		bool isOpened() const {return is_opened; }
		bool hasMine() const { return has_mine; }
		bool isFlagged() const { return is_flagged; }
		void setMine();
		int getSurroundingMinesCount() const { return surrounding_mines_count; }
		void setSurroundingMinesCount(int count) { surrounding_mines_count = count; }
		void setOpenedIcon(const QPixmap& icon);
		void setHidenIcon(const QPixmap& icon);
		QPixmap getHidenIcon(){ return hiden_icon; }
		void openCell();
		void showCell();
		void setBlock(bool block);

	protected:
		void resizeEvent(QResizeEvent *event) override;
		void mousePressEvent(QMouseEvent* event) override;

	signals:
		void openAdjacentCells(int row, int col);
		void mineClicked();
		void flagAdded();
		void flagRemoved();

	private slots:
		void onCellPressed();
		void onCellReleased();
};
