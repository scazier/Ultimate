#include "antiviruspage.h"
#include "ui_antiviruspage.h"
#include <QStyle>
#include <QDebug>
#include <QDesktopWidget>

#include "utilities.h"

AntivirusPage::~AntivirusPage()
{
    delete ui;
}

AntivirusPage::AntivirusPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AntivirusPage),
    avSlidingStacked(new SlidingStackedWidget(this)),
    avTrayIcon(AppManager::ins()->getTrayIcon()),
    avTrayMenu(new QMenu(this))
{
    ui->setupUi(this);

    init();
}

void AntivirusPage::init()
{
    scanSubPage = new ScanSubPage(avSlidingStacked);
    checkSumSubPage = new CheckSumSubPage(avSlidingStacked);

    ui->verticalLayout->addWidget(avSlidingStacked);

    avListPages = {
            scanSubPage, checkSumSubPage
     };

     avListSidebarButtons = {
            ui->btnVirusScan, ui->btnCheckSum
     };

    // add pages
    for (QWidget *page: avListPages) {
        avSlidingStacked->addWidget(page);
    }

    AppManager::ins()->updateStylesheet();

    Utilities::addDropShadow(ui->antiviruswidget, 60);

    // set start page
    clickSidebarButton("Scan");

    createTrayActions();

    avTrayIcon->show();

}

void AntivirusPage::createTrayActions()
{
    for (QPushButton *button: avListSidebarButtons) {
        QString toolTip = button->toolTip();
        QAction *action = new QAction(toolTip, this);
        connect(action, &QAction::triggered, [=] {
            clickSidebarButton(toolTip, true);
        });
        avTrayMenu->addAction(action);
    }

    avTrayMenu->addSeparator();

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, [=] {qApp->quit();});
    avTrayMenu->addAction(quitAction);

    avTrayIcon->setContextMenu(avTrayMenu);
}

void AntivirusPage::clickSidebarButton(QString pageTitle, bool isShow)
{
    QWidget *selectedWidget = getPageByTitle(pageTitle);
    if (selectedWidget) {
        pageClick(selectedWidget, !isShow);
        checkUpperbarButtonByTooltip(pageTitle);
    } else {
        pageClick(avListPages.first());
    }
    setVisible(isShow);
    if (isShow) activateWindow();
}

void AntivirusPage::checkUpperbarButtonByTooltip(const QString &text)
{
    for (QPushButton *button: avListSidebarButtons) {
        if (button->toolTip() == text) {
            button->setChecked(true);
        }
    }
}

QWidget* AntivirusPage::getPageByTitle(const QString &title)
{
    for (QWidget *page: avListPages) {
        if (page->windowTitle() == title) {
            return page;
        }
    }
    return nullptr;
}

void AntivirusPage::pageClick(QWidget *widget, bool slide)
{
    if (widget) {
       //ui->pageTitle->setText(widget->windowTitle());
        if (slide) {
            avSlidingStacked->slideInIdx(avSlidingStacked->indexOf(widget));
        } else {
            avSlidingStacked->setCurrentWidget(widget);
        }
    }
}

void AntivirusPage::on_btnVirusScan_clicked()
{
    pageClick(scanSubPage);
}

void AntivirusPage::on_btnCheckSum_clicked()
{
    pageClick(checkSumSubPage);
}
