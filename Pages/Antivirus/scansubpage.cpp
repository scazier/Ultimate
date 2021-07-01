#include "scansubpage.h"
#include "ui_scansubpage.h"

#include "Manager/command_util.h"

ScanSubPage::~ScanSubPage()
{
    delete ui;
}

ScanSubPage::ScanSubPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanSubPage)
{
    ui->setupUi(this);

    init();

    //systemInformationInit();
}
void ScanSubPage::init()
{
    ui->filePath->setText("/");

}

void ScanSubPage::on_btnVirusScan_clicked()
{
    if (clamScanProc == nullptr || clamScanProc->state() == QProcess::NotRunning){
        QFileInfo check_file(ui->filePath->text());
        if (!check_file.exists()){
            //ui->lblOutputCommand->setText("File path don't exists !");
            return;
        }

        QStringList args = {};

        // Set parameters
        if (ui->recursiveCheckbox->isChecked()) args.append("-r");
        if (ui->bellCheckbox->isChecked()) args.append("--bell");
        if (ui->removeCheckbox->isChecked()) args.append("--remove");

        args.append(ui->filePath->text());

        qDebug() << "[INFO]: Start scan";
        ui->lblOutputCommand->clear();
        clamScanProc = CommandUtil::clamScan("clamscan", args, ui->lblOutputCommand, ui->lblSummaryCommand, ui->btnVirusScan);
        ui->btnVirusScan->setStyleSheet("background: url(:/static/themes/default/img/stopVirusScan.png) no-repeat center;");
        ui->btnVirusScan->setToolTip("Stop scan");

    }
    else{
        qDebug() << "[INFO]: Stop scan";
        clamScanProc->kill();
        //ui->lblOutputCommand->append("\n\n======== Scan stopped by user ========");
        ui->btnVirusScan->setStyleSheet("QPushButton#btnVirusScan {border: 0; image: url(:/static/themes/default/img/virusScan.png) no-repeat center;}"
                                        "QPushButton#btnVirusScan:hover{ image: url(:/static/themes/default/img/startVirusScan.png) no-repeat center;}");
        ui->btnVirusScan->setToolTip("Start scan");
    }
}

void ScanSubPage::on_btnBrowse_clicked()
{
    dialog = new QFileDialog(this);
    //dialog->setFileMode(QFileDialog::Directory);
    dialog->setOption(QFileDialog::DontUseNativeDialog, true);
    dialog->setOption(QFileDialog::ShowDirsOnly, false);
    dialog->exec();

    QDir dir = dialog->directory();

    ui->filePath->setText(dir.path());
}
