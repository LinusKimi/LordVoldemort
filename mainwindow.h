#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDir>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager networkManger;
    QNetworkReply *netReply;
    QFile *downLoadFile;

private slots:
    void on_DownLoadButton_clicked();
    void on_selectFilePath_clicked();
    void on_editPath_textChanged(const QString &arg1);

};
#endif // MAINWINDOW_H
