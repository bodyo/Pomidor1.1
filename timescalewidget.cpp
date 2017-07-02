//#include "timescalewidget.h"
//#include <qwt_scale_engine.h>
//#include <QPainter>
//#include <QWidget>
//#include <QStyleOption>
//#include <QPaintEvent>
//TimeScaleWidget::TimeScaleWidget(QWidget *parent) :
//    QwtScaleWidget(parent)
//{
//    setMouseTracking(true);
//    setAlignment(QwtScaleDraw::BottomScale);
//    QwtInterval interval(0, 5.9);
//    QwtLinearScaleEngine se;
//    setScaleDiv(se.divideScale(interval.minValue(), interval.maxValue(), 9, 10)); // as in QwtPlot::Axis
//    setBorderDist(289, 7);

////    qDebug() << parent->size().width();
//    flag = true;
//}

//void TimeScaleWidget::paintEvent(QPaintEvent *paint)
//{
//    if (flag)
//    {
//        flag = false;
//        widgetWidth = this->size().width()/2;
//    }
//    QPainter painter( this );
//    painter.setClipRegion(paint->region());
////    lastPos = this->size().width()/2;

//    QStyleOption opt;
//    opt.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

//    draw( &painter );

//    QPainterPath path;
//    path.moveTo(this->size().width()/2, this->size().height()/3);
//    path.lineTo(QPoint(this->size().width()/2-5, 0));
//    path.lineTo(QPoint(this->size().width()/2+5, 0));
//    path.lineTo(this->size().width()/2, this->size().height()/3);

//    painter.fillPath(path, QBrush(QColor("orange")));
//}

//void TimeScaleWidget::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//        firstPos = event->x();
//}

//void TimeScaleWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    qDebug() << event->x();
//    if ((event->buttons() & Qt::LeftButton) && (event->x() > 0) && (event->x() < this->size().width()))
//    {
//        lastPos = firstPos-event->x();
//        setBorderDist(widgetWidth-lastPos, 7);
//    }
//}

//void TimeScaleWidget::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        widgetWidth -= lastPos;
//    }
//}
