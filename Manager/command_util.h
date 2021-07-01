#ifndef COMMAND_UTIL_H
#define COMMAND_UTIL_H

#include <QString>
#include <QProcess>
#include <QTextEdit>
#include <QStandardPaths>
#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "Pages/Network/speedtestsubpage.h"

class CommandUtil : public QObject
{
    Q_OBJECT
public:
    static QProcess * clamScan(const QString &cmd, QStringList args, QTextEdit *lblOutput = nullptr,  QPushButton *btnScan = nullptr);
    static QString exec(const QString &cmd, QStringList args = QStringList(), QByteArray data = QByteArray());
    static QString fileSize(float size);
    //static void downloadTest(QNetworkAccessManager *manager, QNetworkRequest request, SpeedtestSubPage ins);

public slots:
    //void updateDownloadBar(qint64 bytesRead, qint64 bytesTotal);

private:
    QNetworkAccessManager *manager;
};

#endif // COMMAND_UTIL_H
