#include <QApplication>
#include <QFontDatabase>
#include <QTextEdit>

#include "mainwindow.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	int app_font = QFontDatabase::addApplicationFont("assets\\fonts\\unitology.ttf");
	QString fontFamily = QFontDatabase::applicationFontFamilies(app_font).at(0);
	QFont customFont(fontFamily);
	customFont.setPointSize(18);
	//app.setFont(customFont);

	MainWindow window;
	window.resize(16*32, 16*32);
	window.setWindowIcon(QIcon("assets\\images\\minesweeper_icon.png"));
	window.setWindowTitle("Minesweeper");
	window.show();

  return app.exec();
}
