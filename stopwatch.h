#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <cstdint>
#include <QString>
#include <QTimer>

class Stopwatch
{
public:
    Stopwatch();
    void start(int micro);
    void stop();
    void reset();

    int elapsed();

private:
    QTimer timer;
    int startTime;
    int stopTime;
};

#endif // STOPWATCH_H
