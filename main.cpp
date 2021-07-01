#include <QApplication>
#include <QSplashScreen>
#include <QDebug>
#include <QFontDatabase>

#include "app.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->setApplicationName("Ultimate");
    qApp->setApplicationDisplayName("Ultimate");
    qApp->setApplicationVersion("1.0.0");
    //qApp->setWindowIcon(QIcon(":/static/logo.png"));

    //QFontDatabase::addApplicationFont(":/static/font/Ubuntu-R.ttf");

    app.processEvents();

    App w;

    QLatin1String hideOption("--hide");

    if (argc < 2 || QString(argv[1]) != hideOption) {
        w.show();
    }

    return app.exec();
}
