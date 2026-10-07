#include "qjsonoper.h"
#include "ui_qjsonoper.h"

#include <QMessageBox>      // 消息弹窗
#include <QDebug>           // 调试输出
#include <QFile>            // 文件读写
#include <QJsonDocument>    // JSON 文档（最外层容器）
#include <QJsonObject>      // JSON 对象（{}）
#include <QJsonParseError>  // JSON 解析错误信息

// ==================== 构造函数 ====================
QJsonOper::QJsonOper(QWidget *parent)
    : QDialog(parent)              // 调用父类构造函数
    , ui(new Ui::QJsonOper)        // 创建界面对象
{
    ui->setupUi(this);             // 加载 .ui 界面布局
}

// ==================== 析构函数 ====================
QJsonOper::~QJsonOper()
{
    delete ui;   // 释放界面对象
}

// ==================== 写入 JSON 文件 ====================
void QJsonOper::on_pushButtonWriteJson_clicked()
{
    // ---------- 第 1 步：创建 JSON 对象 ----------
    QJsonObject mysqinfo;
    mysqinfo.insert("ip", "192.xxx.xx.xxx");
    mysqinfo.insert("port", 3308);
    mysqinfo.insert("user", "root");
    mysqinfo.insert("password", "123456");

    QJsonObject jsonifo;
    jsonifo.insert("code", 1);
    jsonifo.insert("dbmsg", "MySQL数据库配置参数");
    jsonifo.insert("data", mysqinfo);

    // ---------- 第 2 步：创建 JSON 文档 ----------
    QJsonDocument jsondoc;
    jsondoc.setObject(jsonifo);

    // ---------- 第 3 步：写入文件（存在则覆盖） ----------
    QFile qfiles("./databasejsonfiles.json");

    // WriteOnly | Truncate：
    //   不存在 → 创建
    //   已存在 → 清空，从头写入（覆盖）
    if (qfiles.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qfiles.write(jsondoc.toJson());
        qfiles.close();
        qDebug() << "恭喜你，json数据文件写入成功！";
        QMessageBox::information(this, "写入成功",
                                 "恭喜你，json数据文件写入成功！");
    }
    else
    {
        QMessageBox::critical(this, "错误", "文件打开失败，无法写入！");
    }
}
// ==================== 读取 JSON 文件 ====================
void QJsonOper::on_pushButtonReadJson_clicked()
{
    QString strjson;   // 存放从文件读出的内容
    QString strmsg;    // 存放最终显示的消息

    // ---------- 第 1 步：读取文件内容 ----------
    QFile qfiles("./databasejsonfiles.json");
    if (qfiles.open(QIODevice::ReadOnly))    // 以只读方式打开
    {
        strjson = qfiles.readAll();          // 一次性读取全部内容
        qfiles.close();                      // 关闭文件
    }

    // ---------- 第 2 步：把字符串解析成 JSON 文档 ----------
    QJsonParseError jsonerror;   // 存放解析错误信息
    // fromJson：把字符串转成 QJsonDocument
    // 第二个参数传入错误对象，解析失败时会把错误信息填进去
    QJsonDocument jsondoc = QJsonDocument::fromJson(strjson.toUtf8(), &jsonerror);

    QString strtemp;

    // ---------- 第 3 步：检查解析是否成功 ----------
    if (!jsondoc.isEmpty() && (jsonerror.error == QJsonParseError::NoError))
    {
        // 只要 jsondoc 不为空，且解析没有错误，就继续处理

        // 把文档转成 JSON 对象
        QJsonObject json = jsondoc.object();

        QJsonValue code = json.value("code");   // 取 code 字段
        QJsonValue data = json.value("data");   // 取 data 字段

        // ---------- 第 4 步：检查 code 和 data 是否合法 ----------
        if (code.isUndefined() || code.toDouble() != 1 ||
            data.isUndefined() || !data.isObject())
        {
            // code 不存在 / code 不等于 1 / data 不存在 / data 不是对象
            qDebug() << "转换JSON数据错误，请重新检查?";
            QMessageBox::critical(this, "错误", "转换JSON数据错误，请重新检查?");
            exit(100);   // 直接退出程序
        }

        // ---------- 第 5 步：取出 data 里的数据库信息 ----------
        QJsonObject databaseinfo = data.toObject();   // data 转对象

        QJsonValue dbip       = databaseinfo.value("ip");
        QJsonValue dbport     = databaseinfo.value("port");
        QJsonValue dbuser     = databaseinfo.value("user");
        QJsonValue dbpassword = databaseinfo.value("password");

        // ---------- 第 6 步：检查接口（字段）是否都存在 ----------
        if (dbip.isUndefined() ||
            dbport.isUndefined() ||
            dbuser.isUndefined() ||
            dbpassword.isUndefined())
        {
            qDebug() << "接口错误，请重新检查?";
            QMessageBox::critical(this, "错误", "接口错误，请重新检查?");
            exit(100);
        }

        // ---------- 第 7 步：类型转换 ----------
        QString strip       = dbip.toString();      // 转字符串
        int iport           = dbport.toInt();       // 转整数
        QString struser     = dbuser.toString();
        QString strpassword = dbpassword.toString();

        // ---------- 第 8 步：检查数据项是否为空 ----------
        if (strip.isEmpty() || struser.isEmpty() || strpassword.isEmpty())
        {
            qDebug() << "此数据项不能为空，请重新检查?";
            QMessageBox::critical(this, "错误", "此数据项不能为空，请重新检查?");
            exit(100);
        }

        // ---------- 第 9 步：打印到控制台 ----------
        qDebug() << "数据库IP地址:" << strip;
        qDebug() << "数据库端口:" << iport;
        qDebug() << "数据库用户:" << struser;
        qDebug() << "数据库密码:" << strpassword;

        // ---------- 第 10 步：拼接显示字符串 ----------
        strmsg += "【JSON配置参数】";
        strmsg += "\n数据库IP地址:" + strip;
        strmsg += "\n数据库端口:" + QString::number(iport, 10);   // 数字转字符串
        strmsg += "\n数据库用户:" + struser;
        strmsg += "\n数据库密码:" + strpassword;
    }

    // ---------- 第 11 步：弹窗显示结果 ----------
    QMessageBox::information(this, "成功", strmsg, QMessageBox::Yes);
}