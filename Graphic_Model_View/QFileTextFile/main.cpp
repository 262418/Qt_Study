#include <QCoreApplication>   // 控制台应用基类（非 GUI）
#include <QFile>              // 文件操作类
#include <QDebug>             // 调试输出

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);   // 控制台应用对象（无界面）

    // ==================== 1. 创建 QFile 对象 ====================
    QFile qfs("d:/Qfiletext.txt");
    // 构造时传入文件路径
    // Windows 下路径用 / 或 \\，不能用单 \

    // ==================== 2. 打开文件（写模式） ====================
    // QIODevice::WriteOnly：只写
    // QIODevice::Text：文本模式（自动转换换行符）
    if (!qfs.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "打开文件失败，请重新检查";
    } else {
        qDebug() << "恭喜你，打开文件成功";
    }

    // ==================== 3. 写入数据 ====================
    qfs.write("QFileTextFile--");        // 无换行
    qfs.write("Qt零基础学习\n");        // 有换行
    qfs.write("Qt课堂：bilibili大学");  // 无换行

    // 文件内容实际是：
    // QFileTextFile--Qt零基础学习
    // Qt课堂：bilibili大学

    // ==================== 4. 关闭文件 ====================
    qfs.close();

    // ==================== 5. 重新打开（读模式） ====================
    // 每次 open 之前要先 close，否则 open 会失败
    if (!qfs.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "打开文件失败，请生重新检查？";
    } else {
        qDebug() << "恭喜你，打开文件成功（读取数据）！";
    }

    // ==================== 6. 逐行读取 ====================
    char *pStr = new char[200];
    qint64 rcount = qfs.readLine(pStr, 200);
    // readLine 返回读取的字节数：
    //   正常读取：> 0
    //   文件末尾：0
    //   出错：-1

    while ((rcount != 0) && (rcount != -1)) {
        qDebug() << pStr;                // 打印当前行
        rcount = qfs.readLine(pStr, 200); // 继续读下一行
    }

    // ==================== 7. 关闭文件 ====================
    qfs.close();

    delete[] pStr;
    return a.exec();
}