#include <QFontDatabase>
#include <QApplication>

#include "menu.h"
#include "settings.h"

namespace AED {
	Settings::Settings(QWidget *parent) : QWidget(parent) {
		fontComboBox = new QComboBox(this);

		fontComboBox->addItem("Sans");
		fontComboBox->addItem("Arial");
		fontComboBox->addItem("Unitology");

		applyButton = new QPushButton("Apply", this);
		applyButton->setMinimumSize(220, 30);

		QVBoxLayout *vLayout = new QVBoxLayout(this);
		vLayout->addWidget(fontComboBox);
		vLayout->addStretch();
		vLayout->addWidget(applyButton);

		setLayout(vLayout);

		connect(applyButton, &QPushButton::clicked, this, &Settings::onApplyClicked);
	}

	void Settings::onApplyClicked() {
		QString selectedFont = fontComboBox->currentText();

		QFont customFont;
		if (selectedFont == "Arial") {
			customFont = QFont("Arial", 12);
		}
		else if (selectedFont == "Sans") {
			customFont = QFont("Sans", 12);
		}
		else if (selectedFont == "Unitology") {
			int appFontId = QFontDatabase::addApplicationFont(":/fonts/unitology.ttf");
			QString fontFamily = QFontDatabase::applicationFontFamilies(appFontId).at(0);
			customFont = QFont(fontFamily, 12);
		}
		QApplication::setFont(customFont);

		Menu* menu = new Menu();
		menu->resize(150, 200);
		menu->setWindowIcon(QIcon(":images/minesweeper_icon.png"));
		menu->setWindowTitle("Minesweeper");
		menu->show();

		this->close();
	}
}
