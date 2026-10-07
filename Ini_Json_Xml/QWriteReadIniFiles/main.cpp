#include <QCoreApplication>

#include "wrinifile.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 调用写入配置文件
    WriteIniFiles();


    // 调用读取配置文件
    // ReadIniFiles();

    // 整体读取
    ReadIniFilesIsKey();

    return a.exec();
}
