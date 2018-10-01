#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *btn = new QPushButton(this);//选择文件按钮
    btn->setText("选择文件");
    QObject::connect(btn,SIGNAL(clicked(bool)),this,SLOT(openFile()));

    QGridLayout *layout = new QGridLayout;//新建栅格布局管理器
    layout->addWidget(btn,0,0,1,1);//选择文件按钮加入，放在0行0列，占位1行1列
    layout->addWidget(ui->lineEdit,0,1,1,2);//行编辑栏加入
    layout->addWidget(ui->textEdit,1,0,1,3);//输出框加入
    ui->centralWidget->setLayout(layout);
    ui->textEdit->setPlaceholderText(QStringLiteral("词法分析结果将显示于此。"));
}

void MainWindow::openFile()
{
    filePath = QFileDialog::getOpenFileName(this,tr("打开文件"));
    QFile file(filePath);//创建QFile对象
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,tr("打开文件失败"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(filePath).arg(file.errorString()));
        return;
    }
    compiler a(filePath);
    a.analyze();//开始词法分析
    ui->textEdit->setText(a.showResult());//将分析结果输出
    //ui->textEdit->setPlainText(a.showResult());
    /*
    QTextStream in(&file);//新建文本流对象
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //读取文件的全部文本内容，添加到编辑器中
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    */
    ui->lineEdit->setText(filePath);//标识文件路径
}

MainWindow::~MainWindow()
{
    delete ui;
}

