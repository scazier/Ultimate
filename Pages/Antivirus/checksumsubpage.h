#ifndef CHECKSUMSUBPAGE_H
#define CHECKSUMSUBPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QComboBox>
#include <QDebug>

#include "Manager/command_util.h"

namespace Ui{
    class CheckSumSubPage;
}

class CheckSumSubPage:public QWidget
{
    Q_OBJECT
public:
    explicit CheckSumSubPage(QWidget *parent = 0);
    ~CheckSumSubPage();

private:
    void init();

private slots:
    void on_btnBrowse_clicked();
    void on_btnCheck_clicked();

private:
    Ui::CheckSumSubPage *ui;

    QFileDialog *dialog;
};

#endif // CHECKSUMSUBPAGE_H
