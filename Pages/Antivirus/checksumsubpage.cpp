#include "checksumsubpage.h"
#include "ui_checksumsubpage.h"

CheckSumSubPage::~CheckSumSubPage()
{
    delete ui;
}

CheckSumSubPage::CheckSumSubPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckSumSubPage)
{
    ui->setupUi(this);

    init();
}

void CheckSumSubPage::init()
{
    ui->hashList->addItems({"MD5","SHA","SHA1","SHA224","SHA256","SHA384","SHA512"});
}


void CheckSumSubPage::on_btnBrowse_clicked()
{
    dialog = new QFileDialog(this);
    //dialog->setFileMode(QFileDialog::Directory);
    QString filePath = dialog->getOpenFileName(this, "", QDir::homePath());

    ui->filePath->setText(filePath);
}

void CheckSumSubPage::on_btnCheck_clicked()
{
    QString cmd = ui->hashList->currentText();

    if (!cmd.compare("MD5")) cmd = "md5sum";
    if (!cmd.compare("SHA")) cmd = "shasum";
    if (!cmd.compare("SHA1")) cmd = "sha1sum";
    if (!cmd.compare("SHA224")) cmd = "sha224sum";
    if (!cmd.compare("SHA256")) cmd = "sha256sum";
    if (!cmd.compare("SHA384")) cmd = "sha384sum";
    if (!cmd.compare("SHA512")) cmd = "sha512sum";

    QString file, hash, res;

    file = ui->filePath->text();
    hash = CommandUtil::exec(cmd, {ui->filePath->text()}).split(' ')[0];

    ui->fileData->clear();
    ui->fileData->append("INFO: ");
    ui->fileData->append("File: "+file);
    ui->fileData->append("Size: "+CommandUtil::fileSize(QFileInfo(file).size()));
    ui->fileData->append("hash: "+hash);

    if (ui->lblExpectedhash->text().length() != 0){
        if (ui->lblExpectedhash->text().compare(hash) == 0){
            ui->checkSumResult->setPixmap(QPixmap(":/static/themes/default/img/check.png"));
        }
        else{
            ui->checkSumResult->setPixmap(QPixmap(":/static/themes/default/img/failed.png"));
        }
        ui->checkSumResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    //Check for any virus in the file
    QProcess *_p = CommandUtil::clamScan("clamscan",{"--bell", ui->filePath->text()}, ui->fileData);
}
