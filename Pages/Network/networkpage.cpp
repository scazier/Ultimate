#include "networkpage.h"
#include "ui_networkpage.h"
#include <QStyle>
#include <QDesktopWidget>

#include "utilities.h"

NetworkPage::~NetworkPage()
{
    delete ui;
}

NetworkPage::NetworkPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkPage),
    nSlidingStacked(new SlidingStackedWidget(this)),
    nTrayIcon(AppManager::ins()->getTrayIcon()),
    nTrayMenu(new QMenu(this))
{
    ui->setupUi(this);

    init();
}

void NetworkPage::init()
{
    speedtestSubPage = new SpeedtestSubPage(nSlidingStacked);

    ui->verticalNetworkLayout->addWidget(nSlidingStacked);

    nListPages = {
        speedtestSubPage
     };

     nListSidebarButtons = {
         ui->btnSpeedtest
     };

     // add pages
     for (QWidget *page: nListPages) {
         nSlidingStacked->addWidget(page);
     }

     AppManager::ins()->updateStylesheet();

     Utilities::addDropShadow(ui->networkwidget, 60);

     // set start page
     clickSidebarButton("SpeedTest");

     createTrayActions();

     nTrayIcon->show();
}

void NetworkPage::createTrayActions()
{
    for (QPushButton *button: nListSidebarButtons) {
        QString toolTip = button->toolTip();
        QAction *action = new QAction(toolTip, this);
        connect(action, &QAction::triggered, [=] {
            clickSidebarButton(toolTip, true);
        });
        nTrayMenu->addAction(action);
    }

    nTrayMenu->addSeparator();

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, [=] {qApp->quit();});
    nTrayMenu->addAction(quitAction);

    nTrayIcon->setContextMenu(nTrayMenu);
}

void NetworkPage::clickSidebarButton(QString pageTitle, bool isShow)
{
    QWidget *selectedWidget = getPageByTitle(pageTitle);
    if (selectedWidget) {
        pageClick(selectedWidget, !isShow);
        checkUpperbarButtonByTooltip(pageTitle);
    } else {
        pageClick(nListPages.first());
    }
    setVisible(isShow);
    if (isShow) activateWindow();
}

void NetworkPage::checkUpperbarButtonByTooltip(const QString &text)
{
    for (QPushButton *button: nListSidebarButtons) {
        if (button->toolTip() == text) {
            button->setChecked(true);
        }
    }
}

QWidget* NetworkPage::getPageByTitle(const QString &title)
{
    for (QWidget *page: nListPages) {
        if (page->windowTitle() == title) {
            return page;
        }
    }
    return nullptr;
}

void NetworkPage::pageClick(QWidget *widget, bool slide)
{
    if (widget) {
       //ui->pageTitle->setText(widget->windowTitle());
        if (slide) {
            nSlidingStacked->slideInIdx(nSlidingStacked->indexOf(widget));
        } else {
            nSlidingStacked->setCurrentWidget(widget);
        }
    }
}
