#include "timer.h"

Timer::Timer(QLabel* label, QObject* parent) :
	QObject(parent), label(label), elapsed_time(0)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Timer::updateTime);
}

Timer::~Timer() {
	delete timer;
	delete label;
}

void Timer::start() {
	timer->start(1000);
}

void Timer::stop(){
	timer->stop();
}

void Timer::reset() {
	elapsed_time = 0;
	label->setText("Time:000");
}

void Timer::updateTime() {
	elapsed_time++;
	label->setText("Time:" + QString::number(elapsed_time).rightJustified(3, '0'));

	if (elapsed_time >= 999) {
		timer->stop();
		emit timeIsUp();
	}
}
