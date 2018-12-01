#ifndef COMPILER_H
#define COMPILER_H
#include <iostream>
#include <fstream>
#include <QString>
#include <QDebug>
using namespace std;
#define keyNum 18


class compiler
{
public:
    compiler();
    compiler(QString path);
    void analyze();//词法分析
    void compress();//源文件压缩
    QString showResult();//输入结果
private:
    bool isKey(char* buf);//判断是否是关键字
    bool isLetter(char letter);//判断是否是字母
    bool isDigit(char letter);//判断是否是数字
    bool isKind(char* buf);//判断是否为数据类型，压缩文件用

    QString result;//保存分析结果
    string source;//保存文件路径
    char ch = ' ';//读入一个字符
    char token[20];//作单词判断的缓冲区
    //关键字数组
    const char* keyWord[keyNum] = {"void","main","break","switch","include","if",
                                   "else","while","iostream.h","int","cout","cin",
                                   "char","double","float","long","string","bool"};
    const char* wordKind[7] = {"int","bool","char","double","long","float","string"};
};

#endif // COMPILER_H
