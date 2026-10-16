#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>   // Qt 的线程基类

// WorkerThread：继承自 QThread，代表一个子线程
class WorkerThread : public QThread
{
    Q_OBJECT   // 使用信号与槽必须加的宏

public:
    WorkerThread();   // 构造函数

protected:
    // 关键：重写 run() 函数
    // 线程启动后（调用 start()），会自动执行 run() 里的代码
    // 注意：run() 是 protected 的，不能从外面直接调用
    void run();
};

#endif // WORKERTHREAD_H