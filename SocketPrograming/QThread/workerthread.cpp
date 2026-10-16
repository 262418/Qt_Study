#include "workerthread.h"

#include <QtDebug>

// ==================== 构造函数 ====================
WorkerThread::WorkerThread()
{
    // 什么都不做，线程的初始化在 start() 时发生
}

// ==================== 线程体：run() ====================
void WorkerThread::run()
{
    // 无限循环，疯狂打印数字
    while (true)
    {
        for (int i = 1; i <= 5; i++)
            qDebug() << i << i << i << i << i;
    }
}