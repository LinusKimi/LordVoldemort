#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DownLoadButton_clicked()
{
    //开始下载 按钮
        QString urlSpec = ui->lineEdit->text().trimmed();
        if (urlSpec.isEmpty())
        {
            QMessageBox::information(this, "错误",
              "请指定需要下载的URL");
            return;
        }

        QUrl newUrl = QUrl::fromUserInput(urlSpec);//URL地址
        if (!newUrl.isValid())
        {
            QMessageBox::information(this, "错误",
              QString("无效URL: %1 \n 错误信息: %2").arg(urlSpec, newUrl.errorString()));
            return;
        }

        QString tempDir =ui->editPath->text().trimmed();//临时目录
        if (tempDir.isEmpty())
        {
            QMessageBox::information(this, tr("错误"), "请指定保存下载文件的目录");
            return;
        }

        QString fullFileName =tempDir+newUrl.fileName(); //文件名

        if (QFile::exists(fullFileName))
            QFile::remove(fullFileName);

        downLoadFile =new QFile(fullFileName);//创建临时文件
        if (!downLoadFile->open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("错误"),"临时文件打开错误");
            return;
        }

        ui->DownLoadButton->setEnabled(false);

        netReply = networkManger.get(QNetworkRequest(newUrl));
        connect(netReply, &QNetworkReply::finished, [this]{

            downLoadFile->close();
            delete downLoadFile;
            downLoadFile = Q_NULLPTR;

            netReply->deleteLater(); //
            netReply = Q_NULLPTR;

            QMessageBox::information(this, "Message", "下载完成");
            ui->DownLoadButton->setEnabled(true);
        });

        connect(netReply, &QNetworkReply::readyRead,[=]{
            downLoadFile->write(netReply->readAll());
        });

        connect(netReply, &QNetworkReply::downloadProgress,[=](qint64 bytesReceived, qint64 bytesTotal){
            ui->progressBar->setMaximum(bytesTotal);
            ui->progressBar->setValue(bytesReceived);
        });
}

void MainWindow::on_selectFilePath_clicked()
{
    QString dirPath = tr("F:/DownLoad/");
    QDir dir(dirPath);

    dir.mkdir(dirPath);
    ui->editPath->setText(dirPath);

}

void MainWindow::on_editPath_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

}


