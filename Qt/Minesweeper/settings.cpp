#include <QFontDatabase>
#include <QApplication>

#include "menu.h"
#include "settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent) {
	font_combo_box = new QComboBox(this);

	font_combo_box->addItem("Sans");
	font_combo_box->addItem("Arial");
	font_combo_box->addItem("Unitology");

	apply_button = new QPushButton("Apply", this);
	apply_button->setMinimumSize(80, 30);

	QVBoxLayout *vLayout = new QVBoxLayout(this);
	vLayout->addWidget(font_combo_box);
	vLayout->addStretch();
	vLayout->addWidget(apply_button);

	setLayout(vLayout);
	setWindowTitle("Settings");
	setMinimumSize(200, 150);

	connect(apply_button, &QPushButton::clicked, this, &Settings::onApplyClicked);
}

void Settings::onApplyClicked() {
	QString selected_font = font_combo_box->currentText();

	QFont custom_font;
	if (selected_font == "Arial") {
		custom_font = QFont("Arial", 12);
	}
	else if (selected_font == "Sans") {
		custom_font = QFont("Sans", 12);
	}
	else if (selected_font == "Unitology") {
		int app_font = QFontDatabase::addApplicationFont("assets/fonts/unitology.ttf");
		QString font_family = QFontDatabase::applicationFontFamilies(app_font).at(0);
		custom_font = QFont(font_family, 12);
	}

	QApplication::setFont(custom_font);

	Menu* menu = new Menu();
	menu->resize(300, 400);
	menu->setWindowIcon(QIcon("assets\\images\\minesweeper_icon.png"));
	menu->setWindowTitle("Minesweeper");
	menu->show();

	this->close();
}
