#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>

class MainWindow : public QMainWindow{
		Q_OBJECT

	private:
		QWidget* central_widget;
		QGridLayout* grid_layout;

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
};
