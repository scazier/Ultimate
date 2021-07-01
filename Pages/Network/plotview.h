#ifndef PLOTVIEW_H
#define PLOTVIEW_H

//#include <QWidget>
#include <QtCharts>

class PlotView : public QWidget
{
    Q_OBJECT
public:
    explicit PlotView(const QStringList &colors, const int max_time, QWidget *parent = 0);
    ~PlotView();

private slots:
    void addPoint(double currentTime, double currentDebit);
    QChartView *getChart();

private:
    QChart * mChart;
    QChartView *mChartView;
    QLineSeries *mSeries;

    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // PLOTVIEW_H
