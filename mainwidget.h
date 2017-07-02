#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QElapsedTimer>
#include <memory>
#include "stopwatch.h"
QT_FORWARD_DECLARE_CLASS(QPushButton);
QT_FORWARD_DECLARE_CLASS(QLCDNumber);
QT_FORWARD_DECLARE_CLASS(QTimer);
QT_FORWARD_DECLARE_CLASS(QTime);
QT_FORWARD_DECLARE_CLASS(QTimeEdit)
QT_FORWARD_DECLARE_CLASS(QMediaPlayer)

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void _onShowTime();
    void _onSetStartValue(const QTime &start);
    void _onStartButton();
    void _onStopButton();
    void _onPauseButton();
    void _onTimerTimeout();

private:
    void setUiFields();
    Ui::MainWidget *ui;

    QPushButton *_startButton;
    QPushButton *_stopButton;
    QPushButton *_pauseButton;

    std::unique_ptr<QLCDNumber> _timeDisplay;
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QTimeEdit> _timeEdit;
    std::unique_ptr<QMediaPlayer> player;
    Stopwatch stopwatch;
};

#endif // MAINWIDGET_H
