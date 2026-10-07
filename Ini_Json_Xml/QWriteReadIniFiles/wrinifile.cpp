#include "wrinifile.h"

#include <QSettings>   // Qt 读写配置文件的类
#include <QtDebug>     // qDebug() 调试输出

// ==================== 写配置文件 ====================
void WriteIniFiles()
{
    // 创建 QSettings 对象，指定文件名和 INI 格式
    QSettings *ConfigWriteIniFiles =
        new QSettings("MySQLFiles.ini", QSettings::IniFormat);

    // ---- [database] 节 ----
    ConfigWriteIniFiles->setValue("/database/ip", "192.xxx.xx.xxx");    // IP 地址
    ConfigWriteIniFiles->setValue("/database/port", "xxxx");            // 端口
    ConfigWriteIniFiles->setValue("/database/user", "root");            // 用户名
    ConfigWriteIniFiles->setValue("database/password", "123456");       // 密码

    // ---- [notice] 节 ----
    ConfigWriteIniFiles->setValue("/notice/version", "5.6");            // 版本
    ConfigWriteIniFiles->setValue("/notice/datetime", "2022-10-25 16:27:23"); // 日期

    // 释放内存
    delete ConfigWriteIniFiles;
}

// ==================== 读配置文件（按已知的键） ====================
void ReadIniFiles()
{
    QSettings *ConfigReadIniFiles =
        new QSettings("MySQLFiles.ini", QSettings::IniFormat);

    // 逐个读取已知的键
    QString strip       = ConfigReadIniFiles->value("/database/ip").toString();
    QString strport     = ConfigReadIniFiles->value("/database/port").toString();
    QString struser     = ConfigReadIniFiles->value("/database/user").toString();
    QString strpassword = ConfigReadIniFiles->value("/database/password").toString();
    QString strversion  = ConfigReadIniFiles->value("/notice/version").toString();
    QString strdatetime = ConfigReadIniFiles->value("/notice/datetime").toString();

    // 打印到控制台
    qDebug() << "读取INI配置文件参数选项如下：";
    qDebug() << "MySQL数据库IP地址:" << strip.toUtf8().data();
    qDebug() << "数据库端口:" << strport.toUtf8().data();
    qDebug() << "数据库用户:" << struser.toUtf8().data();
    qDebug() << "数据库密码:" << strpassword.toUtf8().data();
    qDebug() << "数据库版本:" << strversion.toUtf8().data();
    qDebug() << "数据库日期:" << strdatetime.toUtf8().data();

    delete ConfigReadIniFiles;
}

// ==================== 读配置文件（遍历所有键） ====================
void ReadIniFilesIsKey()
{
    // 用栈对象，不用 new/delete（更安全）
    QSettings setting("./MySQLFiles.ini", QSettings::IniFormat);

    // allKeys() 返回所有键，格式为 "节/键"
    foreach(QString key, setting.allKeys())
    {
        qDebug() << key.toUtf8().data()
        << ":"
        << setting.value(key).toString().toUtf8().data();
    }
}