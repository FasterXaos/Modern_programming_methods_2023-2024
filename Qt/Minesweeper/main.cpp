#include <QApplication>
#include <QFontDatabase>

#include "menu.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	app.setFont(QFont("Sans", 12));

	AED::Menu* menu = new AED::Menu();
	menu->resize(150, 200);
	menu->setWindowIcon(QIcon(":images/minesweeper_icon.png"));
	menu->setWindowTitle("Minesweeper");
	menu->show();

  return app.exec();
}
