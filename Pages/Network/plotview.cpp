#include "plotview.h"

PlotView::~PlotView()
{
    delete mChart;
}

PlotView::PlotView(const QStringList &colors, const int max_time, QWidget *parent):
    QWidget(parent),
    mChart(new QChart),
    mChartView(new QChartView(mChart)),
    mSeries(new QLineSeries),
    axisX(new QValueAxis),
    axisY(new QValueAxis)
{
    mSeries->append(QPointF(0,0));
    mChart->addSeries(mSeries);
    mChartView->setChart(mChart);

    axisX->setRange(0,max_time);
    axisY->setRange(0, 1000); // 1Gbps

    mChart->addAxis(axisX, Qt::AlignBottom);
    mSeries->attachAxis(axisX);
    mChart->addAxis(axisY, Qt::AlignLeft);
    mSeries->attachAxis(axisY);
    mChart->legend()->hide();
}

QChartView *PlotView::getChart()
{
    return mChartView;
}

void PlotView::addPoint(double currentTime, double currentDebit)
{
    *mSeries << QPointF(currentTime, currentDebit);
}
