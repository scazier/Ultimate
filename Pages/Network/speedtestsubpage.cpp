#include "speedtestsubpage.h"
#include "ui_speedtestsubpage.h"

#include "utilities.h"

#include <QPen>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

SpeedtestSubPage::~SpeedtestSubPage()
{
    delete ui;
}

SpeedtestSubPage::SpeedtestSubPage(QWidget *parent):
    QWidget(parent),
    ui(new Ui::SpeedtestSubPage),
    dLoadBar(new CircleBar(tr("Download"), {"#FFB75E", "#ED8F03"}, this)),
    uLoadBar(new CircleBar(tr("Upload"), {"#DC2430", "#7B4397"}, this))
{
    ui->setupUi(this);

    init();
}

void SpeedtestSubPage::init()
{

    ui->circleBarsLayout->addWidget(dLoadBar);
    ui->circleBarsLayout->addWidget(uLoadBar);

    QVector<double> dValues = QVector<double>();
    QVector<double> uValues = QVector<double>();
    QVector<double> axisX = QVector<double>();

    dValues.append(0);
    uValues.append(0);
    axisX.append(0);

    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(QColor("#FFB75E")));
    ui->plot->graph(0)->setData(axisX,dValues);

    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(QColor("#DC2430")));
    ui->plot->graph(1)->setData(axisX,uValues);

    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(0, 20); // 20 seconds
    ui->plot->yAxis->setRange(0, 1000); // 1Gbps max
    ui->plot->xAxis->setLabel("Mbps");

    ui->plot->setBackground(QBrush(QColor("#212f3c")));
    ui->plot->replot();
    ui->plot->update();

    QList<QWidget*> widgets = {
        dLoadBar, uLoadBar
    };

    dLoadBar->setValue(0, QString("%1").arg("-"));
    uLoadBar->setValue(0, QString("%1").arg("-"));

    Utilities::addDropShadow(widgets, 60);
}

void SpeedtestSubPage::updateDownloadBar(qint64 bytesRead, qint64 bytesTotal)
{
    double secondElapsed = timer->elapsed() / 1000.0;
    if (bytesRead < bytesTotal && secondElapsed < 20.0){

        double MBitsRead = (bytesRead * 8) / (1000.0*1000.0);
        double debit = QString::number(MBitsRead / secondElapsed, 'f', 2).toDouble();
        dLoadBar->setValue(debit, QString("%1 Mbps").arg(debit));
        axisX.append(secondElapsed);
        dValues.append(debit);

        ui->plot->graph(0)->setData(axisX,dValues);
        ui->plot->replot();
        ui->plot->update();
    }
    else{
        delete manager;
        axisX.clear();
        uploadTest();
        return;
    }
}

void SpeedtestSubPage::downloadTest()
{
    manager = new QNetworkAccessManager(this);

    QUrl url(SettingManager::ins()->getSpeedTestHost()+"/10G.iso");
    const QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    timer = new QElapsedTimer();
    timer->start();

    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDownloadBar(qint64,qint64)));
}

void SpeedtestSubPage::updateUploadBar(qint64 bytesRead, qint64 bytesTotal)
{
    double secondElapsed = timer->elapsed() / 1000.0;
    if (bytesRead < bytesTotal && secondElapsed < 20.0){

        double MBitsRead = (bytesRead * 8) / (1000.0*1000.0);
        double debit = QString::number(MBitsRead / secondElapsed, 'f', 2).toDouble();
        uLoadBar->setValue(debit, QString("%1 Mbps").arg(debit));
        axisX.append(secondElapsed);
        uValues.append(debit);

        ui->plot->graph(1)->setData(axisX,uValues);
        ui->plot->replot();
        ui->plot->update();
    }
    else{
        delete manager;
        delete timer;
        return;
    }
}


void SpeedtestSubPage::uploadTest()
{
    manager = new QNetworkAccessManager(this);
    QUrl url(SettingManager::ins()->getSpeedTestHost()+"/1G.iso");
    const QNetworkRequest request(url);

    QIODevice * file = new QFile(SettingManager::ins()->getUploadTestFile());
    file->open(QIODevice::ReadOnly);
    QNetworkReply *reply = manager->put(request, file);

    timer = new QElapsedTimer();
    timer->start();

    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(updateUploadBar(qint64,qint64)));
}

void SpeedtestSubPage::on_btnSpeedTest_clicked()
{
    if (manager == NULL){
        axisX.clear();
        axisX.append(0.0);

        dValues.clear();
        dValues.append(0.0);

        uValues.clear();
        uValues.append(0.0);

        ui->plot->graph(0)->setData(axisX,dValues);
        ui->plot->graph(1)->setData(axisX,uValues);
        ui->plot->replot();
        ui->plot->update();
        downloadTest();
    }
}
