#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>
#include <QRandomGenerator>
#include <QDebug>
#include <QMutex>

const int datasize = 100;
const int buffersize = 1;

QSemaphore freespace(buffersize);   // 空闲位置
QSemaphore usedspace(0);            // 已用位置
QMutex printMutex;                  // 保护打印，防止交错

int buffer[buffersize];             // 真正的共享缓冲区
int in = 0, out = 0;                // 读写位置

// ==================== 生产者线程 ====================
class Producer : public QThread
{
protected:
    void run() override
    {
        for (int i = 0; i < datasize; i++)
        {
            freespace.acquire();   // 申请空闲位置

            // 生产数据（模拟）
            int data = QRandomGenerator::global()->bounded(100);
            buffer[in] = data;
            in = (in + 1) % buffersize;

            // 加锁打印，防止交错
            printMutex.lock();
            qDebug() << "生产者生产：" << data;
            printMutex.unlock();

            usedspace.release();   // 通知消费者：有数据了
        }
    }
};

// ==================== 消费者线程 ====================
class Consumer : public QThread
{
protected:
    void run() override
    {
        for (int i = 0; i < datasize; i++)
        {
            usedspace.acquire();   // 申请已用位置

            // 消费数据
            int data = buffer[out];
            out = (out + 1) % buffersize;

            printMutex.lock();
            qDebug() << "消费者消费：" << data;
            printMutex.unlock();

            freespace.release();   // 通知生产者：有空位了
        }
    }
};

// ==================== 主函数 ====================
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Producer p;
    Consumer c;

    p.start();
    c.start();

    p.wait();
    c.wait();

    return 0;   // 不再用 a.exec()，因为线程已结束
}