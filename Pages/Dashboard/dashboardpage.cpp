#include "dashboardpage.h"
#include "ui_dashboardpage.h"

#include "utilities.h"

DashboardPage::~DashboardPage()
{
    delete ui;
}

DashboardPage::DashboardPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DashboardPage)
{
    ui->setupUi(this);

    init();
}

void DashboardPage::init()
{
}
