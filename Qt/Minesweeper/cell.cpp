#include <QIcon>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPixmap>

#include "cell.h"

Cell::Cell(int row, int column, QWidget *parent) :
	row(row), column(column), QPushButton(parent),
	is_opened(false), has_mine(false), is_flagged(false), is_blocked(false){
	setMinimumSize(32, 32);

	hiden_icon = QPixmap("assets/images/cell_10.png");
	opened_icon = QPixmap("assets/images/cell_0.png");
	pressed_icon = QPixmap("assets/images/cell_0.png");

	setIcon(hiden_icon);
	setIconSize(QSize(128, 128));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(this, &QPushButton::clicked, this, &Cell::openCell);
	connect(this, &QPushButton::pressed, this, &Cell::onCellPressed);
	connect(this, &QPushButton::released, this, &Cell::onCellReleased);
}

void Cell::setMine() {
	has_mine = true;
	opened_icon = QPixmap("assets/images/cell_9.png");
}

void Cell::setOpenedIcon(const QPixmap& icon) {
	opened_icon = icon;
}

void Cell::setHidenIcon(const QPixmap& icon) {
	hiden_icon = icon;
}

void Cell::resizeEvent(QResizeEvent *event) {
	QSize new_size = event->size();
	QPixmap scaled_pixmap;

	if (is_flagged) {
		scaled_pixmap = hiden_icon.scaled(new_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	} else if (is_opened) {
		scaled_pixmap = opened_icon.scaled(new_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}   else {
		scaled_pixmap = hiden_icon.scaled(new_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	setIcon(QIcon(scaled_pixmap));

	QPushButton::resizeEvent(event);
}

void Cell::mousePressEvent(QMouseEvent* event) {
	if (is_blocked) {
		return;
	}

	if (event->button() == Qt::RightButton && !is_opened) {
		is_flagged = !is_flagged;
		is_flagged ? emit flagAdded() : emit flagRemoved();

		QPixmap scaled_pixmap;
		if (is_flagged) {
			hiden_icon = QPixmap("assets/images/cell_11.png");
			scaled_pixmap = hiden_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		} else {
			hiden_icon = QPixmap("assets/images/cell_10.png");
			scaled_pixmap = hiden_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		}
		setIcon(QIcon(scaled_pixmap));
	} else {
		QPushButton::mousePressEvent(event);
	}
}

void Cell::openCell() {
	if (!is_opened && !is_flagged) {
		is_opened = true;
		if (has_mine) {
			emit mineClicked();
			opened_icon = QPixmap("assets/images/cell_13.png");
			QPixmap scaled_pixmap = opened_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			setIcon(QIcon(scaled_pixmap));
			return;
		}

		QPixmap scaled_pixmap = opened_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		setIcon(QIcon(scaled_pixmap));

		if (surrounding_mines_count == 0) {
			emit openAdjacentCells(row, column);
		}
	}
}

void Cell::showCell(){
	is_opened = true;
	QPixmap scaled_pixmap = opened_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	setIcon(QIcon(scaled_pixmap));
}

void Cell::setBlock(bool block){
	is_blocked = block;
}

void Cell::onCellPressed() {
	if (!is_opened && !is_flagged) {
		QPixmap scaled_pixmap = pressed_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		setIcon(QIcon(scaled_pixmap));
	}
}

void Cell::onCellReleased() {
	if (!is_opened && !is_flagged) {
		QPixmap scaled_pixmap = hiden_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		setIcon(QIcon(scaled_pixmap));
	}
}
