#include <QApplication>

#include "snake.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	Snake window;
	window.setWindowTitle("Snake");
	window.setWindowIcon(QIcon(":/apple.png"));
	window.show();

	return app.exec();
}
