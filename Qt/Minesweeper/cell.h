#pragma once

#include <QPushButton>

class Cell : public QPushButton {
	Q_OBJECT

	private:
		QPixmap icon;

	public:
		Cell(QWidget *parent = nullptr);

	protected:
		void resizeEvent(QResizeEvent *event) override;
};
