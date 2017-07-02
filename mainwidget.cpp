#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QTimeEdit>
//#include <QMediaPlayer>
#include <QtMultimedia/QMediaPlayer>
//#include <QtMultimediaWidgets>
//#include "timescalewidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    _startButton = new QPushButton("Start", this);
    _stopButton = new QPushButton("Stop", this);
    _pauseButton = new QPushButton("Pause", this);

    _timeDisplay.reset(new QLCDNumber(this));
    _timer.reset(new QTimer(_timeDisplay.get()));
    _timeEdit.reset(new QTimeEdit(this));

    _timeEdit->setDisplayFormat("mm:ss");
    QTime StartTime(0,25,0);
    _timeEdit->setTime(StartTime);

    connect(_timer.get(), &QTimer::timeout, this, &MainWidget::_onShowTime);
    connect(_startButton, &QPushButton::pressed, this, &MainWidget::_onStartButton);
    connect(_stopButton, &QPushButton::pressed, this, &MainWidget::_onStopButton);
    connect(_pauseButton, &QPushButton::pressed, this, &MainWidget::_onPauseButton);
    connect(_timeEdit.get(), &QTimeEdit::timeChanged, this, &MainWidget::_onSetStartValue);
    connect(&stopwatch.getTimer(), &QTimer::timeout, this, &MainWidget::_onTimerTimeout);

    _timeDisplay->display(StartTime.toString("mm:ss"));

    setUiFields();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::_onShowTime()
{
    QTime time = QTime::fromMSecsSinceStartOfDay(stopwatch.elapsed());

    _timeDisplay->display(time.toString("mm:ss"));
}

void MainWidget::_onSetStartValue(const QTime &start)
{
    _timeDisplay->display(start.toString("mm:ss"));
}

void MainWidget::_onStartButton()
{
    _timer->start(100);
    stopwatch.start(_timeEdit->time().msecsSinceStartOfDay());
    _onShowTime();
}

void MainWidget::_onStopButton()
{
    _timer->stop();
    stopwatch.reset();
}

void MainWidget::_onPauseButton()
{
    _timer->stop();
    stopwatch.pause();
}

void MainWidget::_onTimerTimeout()
{
    player.reset(new QMediaPlayer);
    player->setMedia(QUrl::fromLocalFile("/home/bodyo/Downloads/defaultmusic.mp3"));
    player->setVolume(50);
    player->play();
}

void MainWidget::setUiFields()
{
    QBoxLayout *lcdLayout = new QBoxLayout(QBoxLayout::Down);
    lcdLayout->addWidget(_timeDisplay.get());
    lcdLayout->addWidget(_timeEdit.get());
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);

    layout->addWidget(_stopButton, 1);
    layout->addWidget(_pauseButton, 1);
    layout->addWidget(_startButton, 2);

    lcdLayout->addLayout(layout);

    setLayout(lcdLayout);
}
