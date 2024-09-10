#include <QIcon>
#include <QResizeEvent>
#include <QPixmap>

#include "cell.h"

Cell::Cell(QWidget *parent) : QPushButton(parent) {
	setMinimumSize(32, 32);

	icon = QPixmap("assets/images/cell_10.png");
	setIcon(icon);
	setIconSize(QSize(128, 128));

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Cell::resizeEvent(QResizeEvent *event) {
	QSize newSize = event->size();
	QPixmap scaled_ixmap = icon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	setIcon(QIcon(scaled_ixmap));

	QPushButton::resizeEvent(event);
}
