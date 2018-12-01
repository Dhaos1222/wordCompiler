#include "compiler.h"

compiler::compiler()
{
}

compiler::compiler(QString path)
{
    source = path.toStdString();
}
//判断是否是关键字
bool compiler::isKey(char* buf)
{
    for (int i = 0; i <keyNum; i++)
    {
        if (strcmp(buf, keyWord[i]) == 0)
            return true;
    }
    return false;
}
//判断是否是字母
bool compiler::isLetter(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A'&&letter <= 'Z'))
        return true;
    else
        return false;
}
//判断是否是数字
bool compiler::isDigit(char digit)
{
    if (digit >= '0'&&digit <= '9')
        return true;
    else
        return false;
}
//词法分析
void compiler::analyze()
{
    fstream file(source);
    while ((ch = file.get()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {}//若是空格，tab，换行则读入下一个字符
        else if (isLetter(ch))//如果是字母
        {
            memset(token, 0, sizeof(token));//清空token数组
            char token[20] = { '\0' };
            int i = 0;
            //若读入字符为字母或者数字或者"."则写入token数组
            while (isLetter(ch) || isDigit(ch) || ch == '.') {
                if(i !=0)
                    ch = file.get();
                token[i] = ch;
                i++;
                ch = file.peek();
            }
            //file.seekg(-2, ios_base::cur);//回退两个指针
            //ch = file.get();//读入下一个字符
            if (isKey(token)) {
                //关键字
                //cout << token  << "\t关键字" << endl;
                result.append(QString(QLatin1String(token))+"\t关键字\n");
                //qDebug()<<ch;
            }
            else {
                //标识符
                //cout << token  << "\t标识符" << endl;
                result.append(QString(QLatin1String(token))+"\t标识符\n");
            }
        }
        else if (isDigit(ch) || (ch == '.'))
        {
            int i = 0;
            char token[20] = { '\0' };
            while (isDigit(ch) || (ch == '.'))//&&isDigit(file.get()))
            {
                if(i!=0)
                    ch = file.get();
                token[i] = ch;
                i++;
                ch = file.peek();
            }
            //file.seekg(-2, ios_base::cur);//回退两个指针
            //ch = file.get();//读入下一个字符
            //属于无符号常数
            //cout << token  << "\t常数" << endl;
            result.append(QString(QLatin1String(token))+"\t常数\n");
        }
        else switch (ch) {
            //运算符
        case '+': {
            ch = file.peek();
            if (ch == '+' || ch == '='){
                //cout << "+" << ch << "\t特殊符号" << endl;
                result.append("+"+QString(QChar(ch))+"\t特殊符号\n");
                ch = file.get();
            }
            else {
                //cout << "+" << "\t特殊符号" << endl;
                result.append("+\t特殊符号\n");
            }
        }break;
        case '-': {
            ch = file.peek();
            if (ch == '-' || ch == '=') {
                //cout << "-" << ch <<  "\t特殊符号" << endl;
                result.append("-"+QString(QChar(ch))+"\t特殊符号\n");
                ch = file.get();
            }
            else {
                //cout << "-"  << "\t特殊符号" << endl;
                result.append("-\t特殊符号\n");
            }
        }break;
        case '*': {
            ch = file.peek();
            if (ch == '=') {
                //cout << "*" << ch << "\t特殊符号" << endl;
                result.append("="+QString(QChar(ch))+"\t特殊符号\n");
                ch = file.get();
            }
            else {
                //cout << "*" << "\t特殊符号" << endl;
                result.append("*\t特殊符号\n");
            }
        }break;
        case '/': {
            ch = file.peek();
            if (ch == '=') {
                //cout << "=" << ch << "\t特殊符号" << endl;
                result.append("/"+QString(QChar(ch))+"\t特殊符号\n");
                ch = file.get();
            }
            else if (ch == '/'){
                ch = file.get();
                string comment;
                getline(file,comment);//getline方法读入中文字符
                QString qstring;
                qstring = QString(QString::fromLocal8Bit(comment.c_str()));//解决乱码问题
                result.append("//"+qstring+"\t注释\n");
            }
            else {
                //cout << "/" << "\t特殊符号" << endl;
                result.append("/\t特殊符号\n");
            }
        }break;
            //分界符
        case '(':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case ')':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case '[':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case ']':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case ';':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case '{':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case '}':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
        case '#':result.append(QString(QChar(ch))+"\t特殊符号\n"); break;
            //运算符
        case '=': {
            ch = file.peek();//超前读入下一字符
            if (ch == '=') {
                result.append("="+QString(QChar(ch))+"\t特殊符号\n");
                //cout << "==" << "\t特殊符号" << endl;
                ch = file.get();//读入下一字符
            }
            else {
                //与下一字符无法构成特殊符号组合
                result.append(":\t特殊符号\n");
                //cout << "="  << "\t特殊符号" << endl;
            }
        }break;
        case ':': {
            ch = file.peek();
            if (ch == '=') {
                result.append(":"+QString(QChar(ch))+"\t特殊符号\n");
                //cout << ":=" << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append(":\t特殊符号\n");
                //cout << ":"  << "\t特殊符号" << endl;
            }
        }break;
        case '>': {
            ch = file.peek();
            if (ch == '=' || ch == '>') {
                result.append(">"+QString(QChar(ch))+"\t特殊符号\n");
                //cout << ">" << ch << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append(">\t特殊符号\n");
                //cout << ">"  << "\t特殊符号" << endl;
            }
        }break;
        case '<': {
            ch = file.peek();
            if (ch == '=' || ch == '<') {
                result.append("<"+QString(QChar(ch))+"\t特殊符号\n");
                //cout << "<" << ch << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append("<\t特殊符号\n");
                //cout << "<"  << "\t特殊符号" << endl;
            }
        }break;
        case '"': {
            memset(token, 0, sizeof(token));//清空token数组
            char token[20] = { '\0' };
            int i = 0;
             do{
                token[i] = ch;
                i++;
                ch = file.get();
             } while (ch != '"');
            token[i] = ch;
            result.append(QString(QLatin1String(token))+"\t串\n");
            //cout << token << "\t" << "串" << endl;
        }break;
            //无识别
        default: result.append(QString(QLatin1String(token))+"\t无识别符号\n");//cout << ch << "\t无识别符" << endl;
        }
    }
}

//压缩源文件
void compiler::compress()
{
    fstream file(source);
    while ((ch = file.get()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {}//若是空格，tab，换行则读入下一个字符
        else if (isLetter(ch))//如果是字母
        {
            memset(token, 0, sizeof(token));//清空token数组
            char token[20] = { '\0' };
            int i = 0;
            //若读入字符为字母或者数字或者"."则写入token数组
            while (isLetter(ch) || isDigit(ch) || ch == '.') {
                if(i !=0)
                    ch = file.get();
                token[i] = ch;
                i++;
                ch = file.peek();
            }
            //file.seekg(-2, ios_base::cur);//回退两个指针
            //ch = file.get();//读入下一个字符
            if (isKey(token)) {
                //关键字
                //cout << token  << "\t关键字" << endl;
                if(isKind(token))
                    result.append(QString(QLatin1String(token))+" ");
                else
                    result.append(QString(QLatin1String(token)));
                //qDebug()<<ch;
            }
            else {
                //标识符
                //cout << token  << "\t标识符" << endl;
                result.append(QString(QLatin1String(token)));
            }
        }
        else if (isDigit(ch) || (ch == '.'))
        {
            int i = 0;
            char token[20] = { '\0' };
            while (isDigit(ch) || (ch == '.'))//&&isDigit(file.get()))
            {
                if(i!=0)
                    ch = file.get();
                token[i] = ch;
                i++;
                ch = file.peek();
            }
            //file.seekg(-2, ios_base::cur);//回退两个指针
            //ch = file.get();//读入下一个字符
            //属于无符号常数
            //cout << token  << "\t常数" << endl;
            result.append(QString(QLatin1String(token)));
        }
        else switch (ch) {
            //运算符
        case '+': {
            ch = file.peek();
            if (ch == '+' || ch == '='){
                //cout << "+" << ch << "\t特殊符号" << endl;
                result.append("+"+QString(QChar(ch)));
                ch = file.get();
            }
            else {
                //cout << "+" << "\t特殊符号" << endl;
                result.append("+");
            }
        }break;
        case '-': {
            ch = file.peek();
            if (ch == '-' || ch == '=') {
                //cout << "-" << ch <<  "\t特殊符号" << endl;
                result.append("-"+QString(QChar(ch)));
                ch = file.get();
            }
            else {
                //cout << "-"  << "\t特殊符号" << endl;
                result.append("-");
            }
        }break;
        case '*': {
            ch = file.peek();
            if (ch == '=') {
                //cout << "*" << ch << "\t特殊符号" << endl;
                result.append("="+QString(QChar(ch)));
                ch = file.get();
            }
            else {
                //cout << "*" << "\t特殊符号" << endl;
                result.append("*");
            }
        }break;
        case '/': {
            ch = file.peek();
            if (ch == '=') {
                //cout << "=" << ch << "\t特殊符号" << endl;
                result.append("/"+QString(QChar(ch)));
                ch = file.get();
            }
            else if (ch == '/'){
                ch = file.get();
                string comment;
                getline(file,comment);//getline方法读入中文字符
                QString qstring;
                qstring = QString(QString::fromLocal8Bit(comment.c_str()));//解决乱码问题
                //result.append("//"+qstring);
            }
            else {
                //cout << "/" << "\t特殊符号" << endl;
                result.append("/");
            }
        }break;
            //分界符
        case '(':
        case ')':
        case '[':
        case ']':
        case ';':
        case '{':
        case '}':
        case '#':result.append(QString(QChar(ch))); break;
            //运算符
        case '=': {
            ch = file.peek();//超前读入下一字符
            if (ch == '=') {
                result.append("="+QString(QChar(ch)));
                //cout << "==" << "\t特殊符号" << endl;
                ch = file.get();//读入下一字符
            }
            else {
                //与下一字符无法构成特殊符号组合
                result.append(":");
                //cout << "="  << "\t特殊符号" << endl;
            }
        }break;
        case ':': {
            ch = file.peek();
            if (ch == '=') {
                result.append(":"+QString(QChar(ch)));
                //cout << ":=" << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append(":");
                //cout << ":"  << "\t特殊符号" << endl;
            }
        }break;
        case '>': {
            ch = file.peek();
            if (ch == '=' || ch == '>') {
                result.append(">"+QString(QChar(ch)));
                //cout << ">" << ch << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append(">");
                //cout << ">"  << "\t特殊符号" << endl;
            }
        }break;
        case '<': {
            ch = file.peek();
            if (ch == '=' || ch == '<') {
                result.append("<"+QString(QChar(ch)));
                //cout << "<" << ch << "\t特殊符号" << endl;
                ch = file.get();
            }
            else {
                result.append("<");
                //cout << "<"  << "\t特殊符号" << endl;
            }
        }break;
        case '"': {
            memset(token, 0, sizeof(token));//清空token数组
            char token[20] = { '\0' };
            int i = 0;
             do{
                token[i] = ch;
                i++;
                ch = file.get();
             } while (ch != '"');
            token[i] = ch;
            result.append(QString(QLatin1String(token)));
            //cout << token << "\t" << "串" << endl;
        }break;
            //无识别
        default: result.append(QString(QLatin1String(token)));//cout << ch << "\t无识别符" << endl;
        }
    }
}
//判断是否是数据类型
bool compiler::isKind(char *buf)
{
    for (int i = 0; i <7; i++)
    {
        if (strcmp(buf, wordKind[i]) == 0)
            return true;
    }
    return false;
}

//输出结果
QString compiler::showResult()
{
    return result;
}
