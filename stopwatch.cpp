#include "stopwatch.h"
#include <QTime>

Stopwatch::Stopwatch()
    : startTime{0}, stopTime{0}
{
    timer.setSingleShot(true);
    timer.start();
}

void Stopwatch::start(int micro)
{
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

int Stopwatch::elapsed()
{
    return (stopTime == 0 && timer.remainingTime() != -1) ? timer.remainingTime() : stopTime;
}

//QString Stopwatch::toString()
//{
//    return elapsed()
//}
