#include "downloadtest.h"
#include <sys/time.h>

DownloadTest::DownloadTest(QObject *parent) : QObject(parent)
{

}

void DownloadTest::start()
{
    connect(&socket, &QTcpSocket::readyRead, this, &DownloadTest::readReady);
    connect(&timer, &QTimer::timeout, this, &DownloadTest::timeout);


    read = 0;
    readAll = 0;
    socket.connectToHost("bouygues.testdebit.info", 80);
    if( socket.waitForConnected() )
    {
        socket.write("GET /1G.iso HTTP/1.0\r\nHost: bouygues.testdebit.info\r\n\r\n");
        gettimeofday(&tv, NULL);
        timer.start(1000);
    }
    else
    {
        emit finished(-1);
    }
}

void DownloadTest::reset()
{
    read = 0;
    readAll = 0;
}

void DownloadTest::readReady()
{
    read += socket.bytesAvailable();
    gettimeofday(&tvnow, NULL);
    socket.readAll();
}

void DownloadTest::timeout()
{
    if( socket.state() != QTcpSocket::ConnectedState || this->read == 0)
    {
        timer.stop();
        this->evaluate();
        return;
    }

    int index = 0;
    int index2 = 0;
    QStringList sl;
    sl << "" << "k" << "M" << "G" << "T";
    double read = this->read * 8.0;
    readAll += read;
    emit step(read);

    this->read = 0;

    while( read > 1024 )
    {
        index++;
        read /= 1024;
    }

    int64_t t = tvnow.tv_usec - tv.tv_usec;
    t += (int64_t)tvnow.tv_sec * 1000000UL - (int64_t)tv.tv_sec * 1000000UL;
    double tt = t / 1000000.0;

    double ra = readAll / tt;
    while( ra > 1024 )
    {
        index2++;
        ra /= 1024;
    }
}

void DownloadTest::evaluate()
{
    int64_t t = tvnow.tv_usec - tv.tv_usec;
    t += (int64_t)tvnow.tv_sec * 1000000UL - (int64_t)tv.tv_sec * 1000000UL;
    double tt = t / 1000000.0;

    double ra = readAll / tt;
    emit finished( ra );
}
