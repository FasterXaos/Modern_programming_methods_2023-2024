#pragma once

#include <QObject>
#include <QTimer>
#include <QLabel>

namespace AED {
	class Timer : public QObject {
		Q_OBJECT

	private:
		int elapsedTime;

		QLabel* label;
		QTimer* timer;

	public:
		Timer(QLabel* label, QObject* parent = nullptr);
		~Timer();

		void start();
		void stop();
		void reset();

	signals:
		void timeIsUp();

	private slots:
		void onUpdateTime();
	};
}
