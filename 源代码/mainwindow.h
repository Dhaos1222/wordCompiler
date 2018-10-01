#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <compiler.h>

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();


private:
    Ui::MainWindow *ui;
    QString filePath;
};

#endif // MAINWINDOW_H
