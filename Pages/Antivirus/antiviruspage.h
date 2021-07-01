#ifndef ANTIVIRUSPAGE_H
#define ANTIVIRUSPAGE_H

//#include <QMainWindow>
#include <QMenu>
#include <QPushButton>

#include "sliding_stacked_widget.h"
#include "Manager/app_manager.h"
//#include "Managers/setting_manager.h"

// Pages
#include "Pages/Antivirus/scansubpage.h"
#include "Pages/Antivirus/checksumsubpage.h"

namespace Ui {
    class AntivirusPage;
}

class AntivirusPage : public QWidget
{
    Q_OBJECT
public:
    explicit AntivirusPage(QWidget *parent = 0);
    ~AntivirusPage();

private slots:
    void init();
    void pageClick(QWidget *widget, bool slide = true);
    void clickSidebarButton(QString pageTitle, bool isShow = false);

    void on_btnVirusScan_clicked();
    void on_btnCheckSum_clicked();

private:
     QWidget *getPageByTitle(const QString &title);
     void checkUpperbarButtonByTooltip(const QString &text);
     void createTrayActions();

private:
    Ui::AntivirusPage *ui;
    QList<QWidget*> avListPages;
    QList<QPushButton*> avListSidebarButtons;

    SlidingStackedWidget *avSlidingStacked;

    ScanSubPage *scanSubPage;
    CheckSumSubPage *checkSumSubPage;

    QSystemTrayIcon *avTrayIcon;

    QMenu *avTrayMenu;
};

#endif // ANTIVIRUSPAGE_H
