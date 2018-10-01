#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow(this);
    w->setWindowTitle("C++词法分析器");
    w->show();
}

void Dialog::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择文件"));
    compiler a(fileName);
    a.compress();
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法写入文件 %1: \n %2")
                             .arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<a.showResult();
    QApplication::restoreOverrideCursor();
    QMessageBox::StandardButton res= QMessageBox::question(NULL,
                                               "压缩完毕", "压缩完毕，是否打开文件？",
                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(res == QMessageBox::Yes)
    {
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));//用对应程序打开文件
    }
    //Dialog2* b = new Dialog2(this);
    //b->show();
    return;
}
