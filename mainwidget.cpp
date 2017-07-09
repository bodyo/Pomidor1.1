#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QLabel>
#include <QTimeEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    _startButton = new QPushButton("Start", this);
    _stopButton = new QPushButton("Stop", this);
    _pauseButton = new QPushButton("Pause", this);
    _menuBar.reset(new QMenuBar(this));

    _timeDisplay.reset(new QLCDNumber(this));
    _timer.reset(new QTimer(_timeDisplay.get()));
    _workTimeEdit.reset(new QTimeEdit(this));
    _breakTimeEdit.reset(new QTimeEdit(this));

    player.reset(new QMediaPlayer);
    player->setVolume(50);

    _breakTimeEdit->setDisplayFormat("mm:ss");
    QTime beginTime(0,5,0);
    _breakTimeEdit->setTime(beginTime);

    _workTimeEdit->setDisplayFormat("mm:ss");
    beginTime.setHMS(0,25,0);
    _workTimeEdit->setTime(beginTime);

    connect(_timer.get(), &QTimer::timeout, this, &MainWidget::_onShowTime);
    connect(_startButton, &QPushButton::pressed, this, &MainWidget::_onStartButton);
    connect(_stopButton, &QPushButton::pressed, this, &MainWidget::_onStopButton);
    connect(_pauseButton, &QPushButton::pressed, this, &MainWidget::_onPauseButton);
    connect(_workTimeEdit.get(), &QTimeEdit::timeChanged, this, &MainWidget::_onSetStartValue);
    connect(&stopwatch.getTimer(), &QTimer::timeout, this, &MainWidget::_onTimerTimeout);

    _timeDisplay->display(beginTime.toString("mm:ss"));

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
    if (!stopwatch.isActive())
        _timeDisplay->display(start.toString("mm:ss"));
}

void MainWidget::_onStartButton()
{
    _timer->start(100);
    stopwatch.start(_workTimeEdit->time().msecsSinceStartOfDay());
    player->setMedia(QUrl(songsKeeper.firstStartWorkSong));
    player->play();
    _onShowTime();
}

void MainWidget::_onStopButton()
{
    _timer->stop();
    stopwatch.reset();
    _onSetStartValue(_workTimeEdit->time());
}

void MainWidget::_onPauseButton()
{
    _timer->stop();
    stopwatch.pause();
}

void MainWidget::_onTimerTimeout()
{
    player->play();
    if ((_breakTimeEdit->time() != QTime(0,0,0)) && (stopwatch.getTypeOfTime() != TypeOfTime::Break))
    {
        player->setMedia(QUrl(songsKeeper.endWorkSong));
        player->play();
        stopwatch.setTypeOfTime(TypeOfTime::Break);
        stopwatch.start(_breakTimeEdit->time().msecsSinceStartOfDay());
    }
    else
    {
        player->setMedia(QUrl(songsKeeper.firstStartWorkSong));
        player->play();
        stopwatch.setTypeOfTime(TypeOfTime::Work);
        stopwatch.start(_workTimeEdit->time().msecsSinceStartOfDay());
    }
}

void MainWidget::_onPathToFirstStartWorkMusicChanged()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Music", "/home", tr("Music files (*.mp3 *.aac *.flac)"));
    songsKeeper.firstStartWorkSong = filePath;
}

void MainWidget::_onPathToEndWorkMusicChanged()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Music", "/home", tr("Music files (*.mp3 *.aac *.flac)"));
    songsKeeper.endWorkSong = filePath;
}

void MainWidget::_onPathToEndBreakMusicChanged()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Music", "/home", tr("Music files (*.mp3 *.aac *.flac)"));
    songsKeeper.endBreakSong = filePath;
}

void MainWidget::createMenuBarActions()
{
    QMenu *menuFile = new QMenu("&Music", _menuBar.get());

    QAction *firstStartWorkMusic = new QAction("Change first start work music", _menuBar.get());
    QAction *endWorkMusic = new QAction("Change end work music", _menuBar.get());
    QAction *endBreakMusic = new QAction("Change end break music", _menuBar.get());

    menuFile->addAction(firstStartWorkMusic);
    menuFile->addAction(endWorkMusic);
    menuFile->addAction(endBreakMusic);

    _menuBar->addMenu(menuFile);
    this->layout()->setMenuBar(_menuBar.get());

    connect(firstStartWorkMusic, &QAction::triggered, this, &MainWidget::_onPathToFirstStartWorkMusicChanged);
    connect(endWorkMusic, &QAction::triggered, this, &MainWidget::_onPathToEndWorkMusicChanged);
    connect(endBreakMusic, &QAction::triggered, this, &MainWidget::_onPathToEndBreakMusicChanged);
}

void MainWidget::setUiFields()
{
    QBoxLayout *lcdLayout = new QBoxLayout(QBoxLayout::Down, this);
    QBoxLayout *timeSetLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    lcdLayout->addWidget(_timeDisplay.get());

    createMenuBarActions();

    QLabel *workLabel(new QLabel("Work:", this)); 
    timeSetLayout->addWidget(workLabel, 1);
    timeSetLayout->addWidget(_workTimeEdit.get(), 4);

    QLabel *breakLabel(new QLabel("Break:", this));
    timeSetLayout->addWidget(breakLabel,1);
    timeSetLayout->addWidget(_breakTimeEdit.get(),4);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(_stopButton, 1);
    layout->addWidget(_pauseButton, 1);
    layout->addWidget(_startButton, 2);

    lcdLayout->addLayout(timeSetLayout);
    lcdLayout->addLayout(layout);

    setLayout(lcdLayout);
}
