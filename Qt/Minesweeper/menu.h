#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget {
	Q_OBJECT

	public:
		Menu(QWidget *parent = nullptr);

	private slots:
		void onPlayButtonClicked();
		void onSettingsButtonClicked();
		void onExitButtonClicked();
};
