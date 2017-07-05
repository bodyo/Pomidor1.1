#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <cstdint>
#include <QString>
#include <QTimer>

enum class TypeOfTime
{
    Work,
    Break
};

class Stopwatch
{
public:
    Stopwatch();
    void start(int micro);
    void pause();
    void reset();
    const QTimer &getTimer();
    bool isActive();
    void setTypeOfTime(TypeOfTime type);
    TypeOfTime getTypeOfTime();

    int elapsed();
private:
    QTimer timer;
    TypeOfTime _type;
    int startTime;
    int stopTime;
};

#endif // STOPWATCH_H
