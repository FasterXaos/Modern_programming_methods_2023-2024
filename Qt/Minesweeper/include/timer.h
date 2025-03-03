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

		int getElapsedTime() const;
		void reset();
		void start();
		void stop();

	signals:
		void timeIsUp();

	private slots:
		void onUpdateTime();
	};
}
