#include <QMouseEvent>

#include "cell.h"

namespace AED {
	Cell::Cell(int row, int column, QWidget *parent) :
		row(row), column(column), QPushButton(parent),
		hasMine(false), isBlocked(false), isFlagged(false), isOpened(false)
	{
		hidenIcon = QPixmap(":/images/cell_10.png");
		openedIcon = QPixmap(":/images/cell_0.png");
		pressedIcon = QPixmap(":/images/cell_0.png");

		setMinimumSize(24, 24);
		setIcon(hidenIcon);
		setIconSize(QSize(128, 128));
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		connect(this, &QPushButton::clicked, this, &Cell::openCell);
		connect(this, &QPushButton::pressed, this, &Cell::onCellPressed);
		connect(this, &QPushButton::released, this, &Cell::onCellReleased);
	}

	void Cell::openCell() {
		if (!isOpened && !isFlagged) {
			isOpened = true;

			if (hasMine) {
				emit mineClicked();
				openedIcon = QPixmap(":/images/cell_13.png");
				QPixmap scaledPixmap = openedIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
				setIcon(QIcon(scaledPixmap));
				return;
			}
			QPixmap scaledPixmap = openedIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			setIcon(QIcon(scaledPixmap));

			if (surroundingMinesCount == 0) {
				emit emptyCellOpened(row, column);
			}
		}
	}

	void Cell::setMine() {
		hasMine = true;
		openedIcon = QPixmap(":/images/cell_9.png");
	}

	void Cell::showCell(){
		isOpened = true;
		QPixmap scaledPixmap = openedIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		setIcon(QIcon(scaledPixmap));
	}

	void Cell::mousePressEvent(QMouseEvent* event) {
		if (isBlocked) {
			return;
		}

		if (event->button() == Qt::RightButton && !isOpened) {
			isFlagged = !isFlagged;
			isFlagged ? emit flagAdded() : emit flagRemoved();

			QPixmap scaledPixmap;
			if (isFlagged) {
				hidenIcon = QPixmap(":/images/cell_11.png");
				scaledPixmap = hidenIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			} else {
				hidenIcon = QPixmap(":/images/cell_10.png");
				scaledPixmap = hidenIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			}
			setIcon(QIcon(scaledPixmap));
		} else {
			QPushButton::mousePressEvent(event);
		}
		emit checkForWin();
	}

	void Cell::resizeEvent(QResizeEvent *event) {
		QSize newSize = event->size();
		QPixmap scaledPixmap;

		if (isFlagged) {
			scaledPixmap = hidenIcon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		}
		else if (isOpened) {
			scaledPixmap = openedIcon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		}
		else {
			scaledPixmap = hidenIcon.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		}
		setIcon(QIcon(scaledPixmap));

		QPushButton::resizeEvent(event);
	}

	void Cell::onCellPressed() {
		if (!isOpened && !isFlagged) {
			QPixmap scaledPixmap = pressedIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			setIcon(QIcon(scaledPixmap));
		}
	}

	void Cell::onCellReleased() {
		if (!isOpened && !isFlagged) {
			QPixmap scaledPixmap = hidenIcon.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			setIcon(QIcon(scaledPixmap));
		}
	}
}
