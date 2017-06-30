#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>

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

    connect(_timer.get(), SIGNAL(timeout()), SLOT(_onShowTime()));
    connect(_startButton, SIGNAL(pressed()), SLOT(_onStartButton()));
    connect(_stopButton, SIGNAL(pressed()), SLOT(_onStopButton()));
    connect(_pauseButton, SIGNAL(pressed()), SLOT(_onPauseButton()));
    _timer->start(100);

    _timeDisplay->display("00:00");

    setUiFields();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::_onShowTime()
{
    QTime time = QTime::fromMSecsSinceStartOfDay(stopwatch.elapsed());
    qDebug() << stopwatch.elapsed() << QTime::currentTime().elapsed();

    _timeDisplay->display(time.toString("mm:ss"));
}

void MainWidget::_onStartButton()
{
    stopwatch.start(6000);

    _onShowTime();
}

void MainWidget::_onStopButton()
{
    stopwatch.reset();
//    _timeDisplay->display(QTime::fromMSecsSinceStartOfDay(QRstopwatch.stop()));
//    stopwatch.reset();
}

void MainWidget::_onPauseButton()
{
    stopwatch.stop();
//    _timer->stop();
//    _timeDisplay->display(QTime::fromMSecsSinceStartOfDay(stopwatch.stop()).toString());
}

void MainWidget::setUiFields()
{
    QBoxLayout *lcdLayout = new QBoxLayout(QBoxLayout::Down);
    lcdLayout->addWidget(_timeDisplay.get());
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);

    layout->addWidget(_stopButton, 1);
    layout->addWidget(_pauseButton, 1);
    layout->addWidget(_startButton, 2);

    lcdLayout->addLayout(layout);

    setLayout(lcdLayout);
}
