#include "stopwatch.h"
#include <QTime>
#include <QWidget>

Stopwatch::Stopwatch()
    : startTime{0}, stopTime{0}
{
    timer.setSingleShot(true);
}

void Stopwatch::start(int micro)
{
    timer.start();
    startTime = micro;
    if (stopTime)
        timer.start(stopTime);
    else
        timer.start(micro);
    stopTime = 0;
}

void Stopwatch::pause()
{
    if (timer.remainingTime() > 0)
        stopTime = timer.remainingTime();
    timer.stop();
}

void Stopwatch::reset()
{
    startTime = 0;
    stopTime = 0;
    timer.stop();
}

const QTimer &Stopwatch::getTimer()
{
    return timer;
}

bool Stopwatch::isActive()
{
    return timer.isActive();
}

void Stopwatch::setTypeOfTime(TypeOfTime type)
{
    _type = type;
}

TypeOfTime Stopwatch::getTypeOfTime()
{
    return _type;
}

int Stopwatch::elapsed()
{
    return (stopTime == 0 && timer.remainingTime() != -1) ? timer.remainingTime() : stopTime;
}
