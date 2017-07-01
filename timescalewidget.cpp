#include "timescalewidget.h"
#include <qwt_scale_engine.h>
#include <QPainter>
#include <QWidget>
#include <QStyleOption>
#include <QPaintEvent>
TimeScaleWidget::TimeScaleWidget(QWidget *parent) :
    QwtScaleWidget(parent)
{
    setAlignment(QwtScaleDraw::BottomScale);
    QwtInterval interval(0, 10);
    QwtLinearScaleEngine se;
    setScaleDiv(se.divideScale(interval.minValue(), interval.maxValue(), 10, 5)); // as in QwtPlot::Axis
    setBorderDist(289, 7);
}

void TimeScaleWidget::paintEvent(QPaintEvent *paint)
{
    QPainter painter( this );
    painter.setClipRegion( paint->region() );

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    draw( &painter );

    QPainterPath path;
    path.moveTo(this->size().width()/2, this->size().height()/3);
    path.lineTo(QPoint(this->size().width()/2-5, 0));
    path.lineTo(QPoint(this->size().width()/2+5, 0));
    path.lineTo(this->size().width()/2, this->size().height()/3);

    painter.fillPath(path, QBrush(QColor ("orange")));
}

void TimeScaleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

    }
}
