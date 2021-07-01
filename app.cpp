#include "app.h"
#include "ui_app.h"
#include "utilities.h"
#include <QStyle>
#include <QDebug>
#include <QDesktopWidget>

App::~App()
{
    delete ui;
}

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App),
    mSlidingStacked(new SlidingStackedWidget(this)),
    mTrayIcon(AppManager::ins()->getTrayIcon()),
    mTrayMenu(new QMenu(this))
{
    ui->setupUi(this);

    init();
}

void App::init()
{
    setGeometry(
        QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
            size(), qApp->desktop()->availableGeometry())
    );

    // form settings
    ui->horizontalLayout->setContentsMargins(0,0,0,0);
    ui->horizontalLayout->setSpacing(0);

    antivirusPage = new AntivirusPage(mSlidingStacked);
    networkPage = new NetworkPage(mSlidingStacked);

    ui->pageContentLayout->addWidget(mSlidingStacked);

    mListPages = {
            antivirusPage, networkPage
     };

     mListSidebarButtons = {
            ui->btnAntivirus, ui->btnNetwork
     };

    // add pages
    for (QWidget *page: mListPages) {
        mSlidingStacked->addWidget(page);
    }

    AppManager::ins()->updateStylesheet();

    Utilities::addDropShadow(ui->centralwidget, 60);

    // set start page
    clickSidebarButton(SettingManager::ins()->getStartPage());

    createTrayActions();

    mTrayIcon->show();

    //createQuitMessageBox();
}

void App::createTrayActions()
{
    for (QPushButton *button: mListSidebarButtons) {
        QString toolTip = button->toolTip();
        QAction *action = new QAction(toolTip, this);
        connect(action, &QAction::triggered, [=] {
            clickSidebarButton(toolTip, true);
        });
        mTrayMenu->addAction(action);
    }

    mTrayMenu->addSeparator();

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, [=] {qApp->quit();});
    mTrayMenu->addAction(quitAction);

    mTrayIcon->setContextMenu(mTrayMenu);
}


void App::clickSidebarButton(QString pageTitle, bool isShow)
{
    QWidget *selectedWidget = getPageByTitle(pageTitle);
    if (selectedWidget) {
        pageClick(selectedWidget, !isShow);
        checkSidebarButtonByTooltip(pageTitle);
    } else {
        pageClick(mListPages.first());
    }
    setVisible(isShow);
    if (isShow) activateWindow();
}

void App::checkSidebarButtonByTooltip(const QString &text)
{
    for (QPushButton *button: mListSidebarButtons) {
        if (button->toolTip() == text) {
            button->setChecked(true);
        }
    }
}

QWidget* App::getPageByTitle(const QString &title)
{
    for (QWidget *page: mListPages) {
        if (page->windowTitle() == title) {
            return page;
        }
    }
    return nullptr;
}

void App::pageClick(QWidget *widget, bool slide)
{
    if (widget) {
        ui->pageTitle->setText(widget->windowTitle());
        if (slide) {
            mSlidingStacked->slideInIdx(mSlidingStacked->indexOf(widget));
        } else {
            mSlidingStacked->setCurrentWidget(widget);
        }
    }
}

void App::on_btnAntivirus_clicked()
{
    pageClick(antivirusPage);
}

void App::on_btnNetwork_clicked()
{
    pageClick(networkPage);
}
