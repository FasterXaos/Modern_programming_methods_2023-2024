#include <QApplication>
#include <QFontDatabase>
#include <QTextEdit>

#include "menu.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	app.setFont(QFont("Sans", 12));

	Menu* menu = new Menu();
	menu->resize(300, 400);
	menu->setWindowIcon(QIcon("assets\\images\\minesweeper_icon.png"));
	menu->setWindowTitle("Minesweeper");
	menu->show();

  return app.exec();
}
