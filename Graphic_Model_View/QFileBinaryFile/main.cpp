#include <QCoreApplication>    // 控制台应用基类（非 GUI 程序用）
#include <QFile>               // 文件操作类
#include <QDebug>              // 调试输出

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);   // 创建控制台应用对象

    // ==================== 1. 准备要写入的数据 ====================
    // qint32 是 Qt 保证的 32 位整数（跨平台都是 4 字节）
    qint32 qnumber[3] = {1, 2, 3};

    // ==================== 2. 把整数数组转成字节数组 ====================
    QByteArray bytearray;
    bytearray.resize(sizeof(qnumber));   // 分配 12 字节（3 × 4）

    for (int i = 0; i < 3; i++) {
        // memcpy(目标地址, 源地址, 字节数)
        // 逐个把整数复制到字节数组里
        // bytearray.data() 返回 char* 指向首字节
        // + i*sizeof(qint32) 定位到第 i 个整数位置
        // &(qnumber[i]) 取第 i 个整数的地址
        memcpy(
            bytearray.data() + i * sizeof(qint32),   // 目标位置
            &(qnumber[i]),                            // 源地址
            sizeof(qint32)                            // 拷贝 4 字节
            );
    }
    // 内存布局（小端序）：
    // [01 00 00 00] [02 00 00 00] [03 00 00 00]

    // ==================== 3. 创建文件对象 ====================
    QFile qfs("d:/QFileBinaryByte.dat");
    // 硬编码 D 盘路径，换成其它系统可能不存在
    // 二进制文件用 .dat 后缀，不加 QIODevice::Text

    // ==================== 4. 打开文件（写模式） ====================
    if (!qfs.open(QIODevice::WriteOnly)) {
        // 打开失败：可能路径不存在、没权限、文件被占用
        qDebug() << "打开文件失败，请重新检查";
    } else {
        qDebug() << "恭喜你，打开文件成功！";
    }
    // 这里没 return，打开失败也会继续往下执行

    // ==================== 5. 写入数据 ====================
    qfs.write(bytearray);
    // write 返回实际写入的字节数，没检查是否写全
    // 二进制模式写入，不做换行转换

    // ==================== 6. 关闭文件 ====================
    qfs.close();
    // 关闭后数据落盘，缓冲区清空

    // ==================== 7. 重新打开（读模式） ====================
    qfs.open(QIODevice::ReadOnly);

    QByteArray byteArray = qfs.readAll();
    // readAll 一次读完整个文件内容

    // ==================== 8. 打印读取的原始数据 ====================
    qDebug() << "byteArry：" << byteArray;
    // QByteArray 打印时会用十六进制转义显示不可打印字符
    // 输出：byteArray： "\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00"

    // ==================== 9. 把字节解释回整数 ====================
    // char *ctemp = byteArray.data();
    // // 拿到字节数组的首指针
    // while (*ctemp) {
    //     // 严重问题：用"当前字节是否为 0"判断循环
    //     // 数据里一旦出现 0 字节（大整数、负数）会提前退出
    //     // 文件读完继续读会越界（未定义行为）

    //     qDebug() << *(qint32 *)ctemp;
    //     // 问题1：强制转换 char* → qint32* 可能不对齐，某些平台崩溃
    //     // 问题2：严格别名规则不保证安全

    //     ctemp = ctemp + sizeof(qint32);
    //     // 指针前进 4 字节，指向下一个整数
    // }
    const char *ctemp = byteArray.constData();
    int count = byteArray.size() / sizeof(qint32);

    for (int i = 0; i < count; ++i) {
        qint32 val;
        memcpy(&val, ctemp + i * sizeof(qint32), sizeof(qint32));
        qDebug() << val;
    }
    qfs.close();

    return a.exec();
}