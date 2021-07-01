#include "command_util.h"

QString CommandUtil::exec(const QString &cmd, QStringList args, QByteArray data)
{
    std::unique_ptr<QProcess> process(new QProcess());
    process->start(cmd, args);

    if (! data.isEmpty()) {
        process->write(data);
        process->waitForBytesWritten();
        process->closeWriteChannel();
    }

    // 10 minutes
    process->waitForFinished(600*1000);

    QTextStream stdOut(process->readAllStandardOutput());

    QString err = process->errorString();

    process->kill();
    process->close();

    if (process->error() != QProcess::UnknownError)
        throw err;

    return stdOut.readAll().trimmed();
}

QProcess * CommandUtil::clamScan(const QString &cmd, QStringList args, QTextEdit *lblOutput, QPushButton *btnScan)
{
    auto process = new QProcess;
    lblOutput->append("======== STARTING SCAN OF : " + args[args.length()-1] + " ========\n");
    connect(process, &QProcess::readyReadStandardOutput, [process,lblOutput](){
        QTextStream stdOut(process->readAllStandardOutput());
        auto output = stdOut.readAll().trimmed();
        lblOutput->append(output);
    });

    if (btnScan != nullptr){
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus){
            btnScan->setStyleSheet("QPushButton#btnVirusScan {border: 0; image: url(:/static/themes/default/img/virusScan.png) no-repeat center;}"
                                            "QPushButton#btnVirusScan:hover{ image: url(:/static/themes/default/img/startVirusScan.png) no-repeat center;}");
            btnScan->setToolTip("Start scan");
        });
    }

    process->start(cmd, args);
    return process;
}

QString CommandUtil::fileSize(float size)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(size >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        size /= 1024.0;
    }
    return QString().setNum(size,'f',2)+" "+unit;
}
