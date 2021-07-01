#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QMenu>
#include <QPushButton>

#include "sliding_stacked_widget.h"
#include "Manager/app_manager.h"

//Pages
#include "Pages/Network/speedtestsubpage.h"


namespace  Ui{
    class NetworkPage;
}

class NetworkPage : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPage(QWidget *parent = 0);
    ~NetworkPage();

private slots:
    void init();
    void pageClick(QWidget *widget, bool slide = true);
    void clickSidebarButton(QString pageTitle, bool isShow = false);

private:
     QWidget *getPageByTitle(const QString &title);
     void checkUpperbarButtonByTooltip(const QString &text);
     void createTrayActions();

private:
    Ui::NetworkPage *ui;
    QList<QWidget*> nListPages;
    QList<QPushButton*> nListSidebarButtons;

    SlidingStackedWidget *nSlidingStacked;

    SpeedtestSubPage *speedtestSubPage;

    QSystemTrayIcon *nTrayIcon;

    QMenu *nTrayMenu;
};

#endif // NETWORKPAGE_H
