#include <QIcon>
#include <QResizeEvent>
#include <QPixmap>

#include "cell.h"

Cell::Cell(QWidget *parent) : QPushButton(parent), is_opened(false) {
	setMinimumSize(32, 32);

	hiden_icon = QPixmap("assets/images/cell_10.png");
	opened_icon = QPixmap("assets/images/cell_0.png");

	setIcon(hiden_icon);
	setIconSize(QSize(128, 128));

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(this, &QPushButton::clicked, this, &Cell::openCell);
}

void Cell::setMine() {
	has_mine = true;
	opened_icon = QPixmap("assets/images/cell_9.png");
}

void Cell::resizeEvent(QResizeEvent *event) {
	QSize newSize = event->size();
	QPixmap scaled_pixmap;

	if (is_opened) {
		scaled_pixmap = opened_icon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	} else {
		scaled_pixmap = hiden_icon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	setIcon(QIcon(scaled_pixmap));

	QPushButton::resizeEvent(event);
}

void Cell::openCell() {
	if (!is_opened) {
		is_opened = true;
		QPixmap scaledPixmap = opened_icon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		setIcon(QIcon(scaledPixmap));

		setEnabled(false);
	}
}
