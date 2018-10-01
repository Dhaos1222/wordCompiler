#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog m;
    m.setWindowTitle("C++词法分析器");
    m.show();
    return a.exec();
}
