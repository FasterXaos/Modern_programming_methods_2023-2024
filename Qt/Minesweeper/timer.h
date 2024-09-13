#pragma once

#include <QObject>
#include <QTimer>
#include <QLabel>

class Timer : public QObject {
	Q_OBJECT

private:
	QTimer* timer;
	QLabel* label;
	int elapsed_time;

public:
	Timer(QLabel* label, QObject* parent = nullptr);
	~Timer();

	void start();
	void stop();
	void reset();

signals:
	void timeIsUp();

private slots:
	void updateTime();
};
