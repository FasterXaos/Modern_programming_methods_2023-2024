#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	MainWindow main_window;
	main_window.resize(1000, 1000);
	main_window.setWindowIcon(QIcon("assets\\images\\minesweeper_icon.png"));
	main_window.setToolTip("MainWindow");
	main_window.setWindowTitle("Minesweeper");
	main_window.show();

	return app.exec();
}
