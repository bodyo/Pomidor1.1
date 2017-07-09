#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QElapsedTimer>
#include <memory>
#include "stopwatch.h"
#include "songskeeper.h"
QT_FORWARD_DECLARE_CLASS(QPushButton);
QT_FORWARD_DECLARE_CLASS(QLCDNumber);
QT_FORWARD_DECLARE_CLASS(QTimer);
QT_FORWARD_DECLARE_CLASS(QTime);
QT_FORWARD_DECLARE_CLASS(QTimeEdit)
QT_FORWARD_DECLARE_CLASS(QMediaPlayer)
class QMenuBar;
class QMenu;

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
    void _onPathToFirstStartWorkMusicChanged();
    void _onPathToEndWorkMusicChanged();
    void _onPathToEndBreakMusicChanged();

private:
    void createMenuBarActions();
    void setUiFields();
    Ui::MainWidget *ui;

    QPushButton *_startButton;
    QPushButton *_stopButton;
    QPushButton *_pauseButton;

    std::unique_ptr<QLCDNumber> _timeDisplay;
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QTimeEdit> _workTimeEdit;
    std::unique_ptr<QTimeEdit> _breakTimeEdit;
    std::unique_ptr<QMediaPlayer> player;
    std::unique_ptr<QMenuBar> _menuBar;
    std::unique_ptr<QMenu> _musicMenu;
    SongsKeeper songsKeeper;
    Stopwatch stopwatch;
};

#endif // MAINWIDGET_H
