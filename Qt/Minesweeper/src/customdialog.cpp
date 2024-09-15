#include <QFormLayout>
#include <QIntValidator>
#include <QPushButton>

#include "customdialog.h"

namespace AED {
	CustomDialog::CustomDialog(QWidget *parent)
		: QDialog(parent)
	{
		setWindowTitle("Custom");
		setFixedSize(200, 150);

		rowsInput = new QLineEdit(this);
		columnsInput = new QLineEdit(this);
		minesInput = new QLineEdit(this);

		rowsInput->setValidator(new QIntValidator(this));
		columnsInput->setValidator(new QIntValidator(this));
		minesInput->setValidator(new QIntValidator(this));

		QPushButton *okButton = new QPushButton("OK", this);
		QPushButton *cancelButton = new QPushButton("Cancel", this);

		QFormLayout *formLayout = new QFormLayout();
		formLayout->addRow("Rows:", rowsInput);
		formLayout->addRow("Columns:", columnsInput);
		formLayout->addRow("Mines:", minesInput);

		QHBoxLayout *buttonLayout = new QHBoxLayout();
		buttonLayout->addWidget(okButton);
		buttonLayout->addWidget(cancelButton);

		QVBoxLayout *dialogLayout = new QVBoxLayout(this);
		dialogLayout->addLayout(formLayout);
		dialogLayout->addLayout(buttonLayout);

		connect(okButton, &QPushButton::clicked, this, &CustomDialog::accept);
		connect(cancelButton, &QPushButton::clicked, this, &CustomDialog::reject);
	}


	int CustomDialog::getRows() const {
		return rowsInput->text().toInt();
	}

	int CustomDialog::getColumns() const {
		return columnsInput->text().toInt();
	}

	int CustomDialog::getMines() const {
		return minesInput->text().toInt();
	}
}
