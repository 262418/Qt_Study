#include <QCoreApplication>    // 控制台应用基类
#include <QFile>               // 文件类
#include <QtDebug>             // 调试输出（等同 QDebug）
#include <QTextStream>         // 文本流（核心）
#include <QDataStream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ==================== 写入数据 ====================
    QFile qfs("d:/qtextstreamfile.txt");
    // 硬编码 D 盘路径

    // ---------- 打开文件（写模式 + 文本模式） ----------
    if (!qfs.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "打开文件失败，请重新检查？";
    } else {
        qDebug() << "恭喜你，打开文件成功！";
    }
    // 打开失败没 return，会继续执行

    // ---------- 创建文本流 ----------
    QTextStream qtextstreamwrite(&qfs);
    // 绑定到文件，之后所有 << 操作都写入这个文件

    // ---------- 写入数据 ----------
    qtextstreamwrite << (QString)"Qt学习-bilibili大学";
    // 用 << 流操作符写入
    // (QString) 是 C 风格强制转换，可省略（Qt 隐式转换）
    // QTextStream 会自动把 QString 按 UTF-8 编码写入

    qfs.close();
    // 关闭文件（QTextStream 会把缓冲区剩余数据刷入文件）

    // ==================== 读取数据 ====================
    // ---------- 重新打开（读模式） ----------
    if (!qfs.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "打开文件失败，请重新检查？";
    } else {
        qDebug() << "恭喜你，打开文件成功(读取数据......)！";
    }

    // ---------- 创建文本流（读） ----------
    QTextStream qtextstreamread(&qfs);

    // ---------- 逐词读取 ----------
    while (!qtextstreamread.atEnd()) {
        // atEnd()：是否读到末尾

        QString strtemp;
        qtextstreamread >> strtemp;
        // 用 >> 读取（以空白字符分隔）
        // 遇到空格、换行、Tab 会停下

        qDebug() << strtemp;
    }

    qfs.close();

    return a.exec();
}