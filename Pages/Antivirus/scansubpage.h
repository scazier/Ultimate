#ifndef SCANSUBPAGE_H
#define SCANSUBPAGE_H

#include <QWidget>
#include <QProcess>
#include <QCheckBox>
#include <QFileDialog>
#include <QPainter>
#include <QSequentialAnimationGroup>

namespace Ui{
    class ScanSubPage;
}

class ScanSubPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScanSubPage(QWidget *parent = 0);
    ~ScanSubPage();

private slots:
    void init();

    void on_btnVirusScan_clicked();
    void on_btnBrowse_clicked();

private:
    Ui::ScanSubPage *ui;

    QFileDialog *dialog;
    QProcess *clamScanProc;
    QSequentialAnimationGroup *animation;
    QPainter *scanLine;
};

#endif // SCANSUBPAGE_H
