#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace AED {
	class Settings : public QWidget {
		Q_OBJECT

		private:
			QComboBox *fontComboBox;
			QPushButton *applyButton;

		public:
			Settings(QWidget *parent = nullptr);

		private slots:
			void onApplyClicked();
	};
}
