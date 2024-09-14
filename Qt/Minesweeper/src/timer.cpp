#include "timer.h"

namespace AED {
	Timer::Timer(QLabel* label, QObject* parent) :
		elapsedTime(0), label(label), QObject(parent)
	{
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &Timer::onUpdateTime);
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
		elapsedTime = 0;
		label->setText("Time:000");
	}

	void Timer::onUpdateTime() {
		++elapsedTime;
		label->setText("Time:" + QString::number(elapsedTime).rightJustified(3, '0'));

		if (elapsedTime >= 999) {
			timer->stop();
			emit timeIsUp();
		}
	}
}
