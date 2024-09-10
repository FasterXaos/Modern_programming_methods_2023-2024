#pragma once

#include <QPushButton>

class Cell : public QPushButton {
	Q_OBJECT

	private:
		QPixmap hiden_icon;
		QPixmap opened_icon;
		bool is_opened;
		bool has_mine;

	public:
		Cell(QWidget *parent = nullptr);
		bool hasMine() const { return has_mine; }
		void setMine();

	protected:
		void resizeEvent(QResizeEvent *event) override;

	private slots:
			void openCell();
};
