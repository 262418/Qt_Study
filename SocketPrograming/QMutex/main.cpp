#include <QCoreApplication>

#include <iostream>      // C++ 标准输入输出
#include <QMutex>        // 互斥锁：保护共享数据，同一时刻只允许一个线程访问
#include <QThread>       // Qt 线程类
#include <QObject>       // Qt 对象基类（支持信号与槽）

// ==================== 售票类 ====================
// 继承 QObject 是为了能用 moveToThread + 信号与槽
class ticketsllers : public QObject
{
public:
    ticketsllers();
    ~ticketsllers();

public slots:
    void salefunc();   // 售票槽函数（在子线程里执行）

public:
    int *tickets;              // 指向共享的票数（多个售票员共用同一张票）
    QMutex *metx;              // 指向共享的互斥锁
    std::string sellersname;   // 售票员姓名
};

// ==================== 构造函数 ====================
ticketsllers::ticketsllers()
{
    metx = NULL;       // 指针初始化为空
    tickets = 0;       // 注意：这里把 int* 赋值为 0，实际是空指针
    //   真正的票数在 main 里通过 &ticket 赋值
}

// ==================== 售票函数 ====================
void ticketsllers::salefunc()
{
    while (true)
    {
        metx->lock();              // 先加锁
        if (*tickets <= 0)         // 在锁内判断
        {
            metx->unlock();
            break;
        }
        std::cout << sellersname << " : " << (*tickets)-- << std::endl;
        metx->unlock();
        QThread::msleep(10);   // 睡 10 毫秒，让别的线程有机会
    }
}

ticketsllers::~ticketsllers() {}

// ==================== 主函数 ====================
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int ticket = 20;    // 总票数 20
    QMutex mtx;         // 全局互斥锁（3 个售票员共用同一把锁）

    // ---------- 创建线程 1 ----------
    QThread th1;
    ticketsllers seller1;
    seller1.tickets = &ticket;            // 共享票数（传地址）
    seller1.metx = &mtx;                  // 共享锁（传地址）
    seller1.sellersname = "seller kitty";
    seller1.moveToThread(&th1);           // 把对象移到子线程

    // ---------- 创建线程 2 ----------
    QThread th2;
    ticketsllers seller2;
    seller2.tickets = &ticket;
    seller2.metx = &mtx;
    seller2.sellersname = "seller sunny";
    seller2.moveToThread(&th2);

    // ---------- 创建线程 3 ----------
    QThread th3;
    ticketsllers seller3;
    seller3.tickets = &ticket;
    seller3.metx = &mtx;
    seller3.sellersname = "seller andy";
    seller3.moveToThread(&th3);

    // 连接信号与槽：线程启动时，自动调用 salefunc
    // QThread::started 是线程启动信号
    QObject::connect(&th1, &QThread::started, &seller1, &ticketsllers::salefunc);
    QObject::connect(&th2, &QThread::started, &seller2, &ticketsllers::salefunc);
    QObject::connect(&th3, &QThread::started, &seller3, &ticketsllers::salefunc);

    // 启动 3 个线程
    th1.start();
    th2.start();
    th3.start();

    return a.exec();   // 进入事件循环
}