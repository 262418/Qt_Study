#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

// 格式化大小
QString formatSize(qint64 bytes)
{
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int i = 0;
    double size = bytes;

    while (size >= 1024.0 && i < 4) {
        size /= 1024.0;
        ++i;
    }

    return QString("%1 %2").arg(size, 0, 'f', 2).arg(units[i]);
}

// 递归统计目录大小
qint64 getDirSize(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) return 0;

    qint64 total = 0;

    // ---------- 1. 累加当前目录所有文件 ----------
    const QFileInfoList files = dir.entryInfoList(QDir::Files);
    for (const QFileInfo &info : files) {
        total += info.size();
    }

    // ---------- 2. 递归子目录 ----------
    const QStringList subDirs = dir.entryList(
        QDir::Dirs | QDir::NoDotAndDotDot
        );

    for (const QString &subName : subDirs) {
        const QString subPath = dir.filePath(subName);

        // 跳过符号链接（防止无限递归）
        QFileInfo info(subPath);
        if (info.isSymLink()) continue;

        total += getDirSize(subPath);
    }

    return total;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ---------- 获取当前目录 ----------
    QString path = QDir::currentPath();
    qDebug() << "当前目录：" << path;

    // ---------- 统计 ----------
    qint64 totalBytes = getDirSize(path);

    // ---------- 打印 ----------
    qDebug() << "总大小：" << formatSize(totalBytes)
             << "(" << totalBytes << "字节 )";

    return a.exec();
}