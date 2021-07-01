QT       += core gui charts network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Manager/app_manager.cpp \
    Manager/command_util.cpp \
    Manager/file_util.cpp \
    Manager/setting_manager.cpp \
    Pages/Antivirus/antiviruspage.cpp \
    Pages/Antivirus/checksumsubpage.cpp \
    Pages/Antivirus/scansubpage.cpp \
    Pages/Dashboard/dashboardpage.cpp \
    Pages/Network/circlebar.cpp \
    Pages/Network/networkpage.cpp \
    Pages/Network/plotview.cpp \
    Pages/Network/speedtestsubpage.cpp \
    app.cpp \
    main.cpp \
    signal_mapper.cpp \
    qcustomplot.cpp \
    sliding_stacked_widget.cpp

HEADERS += \
    Manager/app_manager.h \
    Manager/command_util.h \
    Manager/file_util.h \
    Manager/setting_manager.h \
    Pages/Antivirus/antiviruspage.h \
    Pages/Antivirus/checksumsubpage.h \
    Pages/Antivirus/scansubpage.h \
    Pages/Dashboard/dashboardpage.h \
    Pages/Network/circlebar.h \
    Pages/Network/networkpage.h \
    Pages/Network/plotview.h \
    Pages/Network/speedtestsubpage.h \
    app.h \
    signal_mapper.h \
    sliding_stacked_widget.h \
    qcustomplot.h \
    utilities.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Pages/Antivirus/antiviruspage.ui \
    Pages/Antivirus/checksumsubpage.ui \
    Pages/Antivirus/scansubpage.ui \
    Pages/Dashboard/dashboardpage.ui \
    Pages/Network/circlebar.ui \
    Pages/Network/networkpage.ui \
    Pages/Network/speedtestsubpage.ui \
    app.ui

DISTFILES += \
    static/themes/default/style/style.qss \
    static/themes/default/style/values.ini

RESOURCES += \
    static.qrc
