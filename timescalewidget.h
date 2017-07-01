#ifndef TIMESCALEWIDGET_H
#define TIMESCALEWIDGET_H
#include <qwt_scale_widget.h>

class TimeScaleWidget : public QwtScaleWidget
{
public:
    TimeScaleWidget(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *paint) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // TIMESCALEWIDGET_H
