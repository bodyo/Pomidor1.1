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
    void pause();
    void reset();
    const QTimer &getTimer();
//    bool isAlive();

    int elapsed();
//signals:
//    void timeout();
private:
    QTimer timer;
    int startTime;
    int stopTime;
};

#endif // STOPWATCH_H
