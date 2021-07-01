#ifndef SPEEDTESTSUBPAGE_H
#define SPEEDTESTSUBPAGE_H

#include <QDebug>
#include <QWidget>

#include "circlebar.h"
#include "qcustomplot.h"
#include "Manager/command_util.h"
#include "Manager/setting_manager.h"

namespace Ui{
    class SpeedtestSubPage;
}

class SpeedtestSubPage : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedtestSubPage(QWidget *parent = 0);
    ~SpeedtestSubPage();

private slots:
    void init();

    void updateDownloadBar(qint64 bytesRead, qint64 bytesTotal);
    void updateUploadBar(qint64 bytesRead, qint64 bytesTotal);
    void downloadTest();
    void uploadTest();

    void on_btnSpeedTest_clicked();

private:
    Ui::SpeedtestSubPage *ui;

    CircleBar *dLoadBar;
    CircleBar *uLoadBar;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QElapsedTimer *timer;

    QVector<double> dValues;
    QVector<double> uValues;
    QVector<double>  axisX;

};

#endif // SPEEDTESTSUBPAGE_H
