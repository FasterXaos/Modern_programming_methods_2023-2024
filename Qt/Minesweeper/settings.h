#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class Settings : public QWidget {
	Q_OBJECT

	private:
		QComboBox *font_combo_box;
		QPushButton *apply_button;

	public:
		Settings(QWidget *parent = nullptr);

	private slots:
		void onApplyClicked();
};
