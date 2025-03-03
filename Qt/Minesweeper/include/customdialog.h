#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QWidget>

namespace AED {
	class CustomDialog : public QDialog {
		Q_OBJECT

		private:
			QLineEdit *rowsInput;
			QLineEdit *columnsInput;
			QLineEdit *minesInput;

		public:
			explicit CustomDialog(QWidget *parent = nullptr);

			int getRows() const;
			int getColumns() const;
			int getMines() const;
	};
}
