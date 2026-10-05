#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qt事件过滤器--测试程序");

    // ==================== 创建 3 张图片标签 ====================
    // ---------- 左图 ----------
    label1jpg = new QLabel;
    image1jpg.load("D:/Qt_Project/Graphic_Model_View/images/a1.jpg");                // 硬编码路径
    label1jpg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label1jpg->setPixmap(QPixmap::fromImage(image1jpg));

    // ---------- 中图 ----------
    label2jpg = new QLabel;
    image2jpg.load("D:/Qt_Project/Graphic_Model_View/images/b1.jpg");
    label2jpg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label2jpg->setPixmap(QPixmap::fromImage(image2jpg));

    // ---------- 右图 ----------
    label3jpg = new QLabel;
    image3jpg.load("D:/Qt_Project/Graphic_Model_View/images/c1.jpg");
    label3jpg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label3jpg->setPixmap(QPixmap::fromImage(image3jpg));

    // ==================== 创建提示标签 ====================
    labeldispinfo = new QLabel("鼠标按键提示信息!");
    labeldispinfo->setAlignment(Qt::AlignHCenter);

    // ==================== 布局 ====================
    // ---------- 水平布局：3 张图片 ----------
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1jpg);
    hlayout->addWidget(label2jpg);
    hlayout->addWidget(label3jpg);

    // ---------- 主容器：垂直布局 ----------
    QWidget *wgt = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(wgt);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(labeldispinfo);

    setCentralWidget(wgt);

    // ==================== 安装事件过滤器 ====================
    // 让 MainWindow 拦截 3 个图片标签的事件
    label1jpg->installEventFilter(this);   // this = MainWindow
    label2jpg->installEventFilter(this);
    label3jpg->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================================================================
// 事件过滤器（核心）
// watched：事件发生在哪个对象上
// event：事件对象
// 返回值：true = 拦截事件（不再传播）；false = 继续传播
// ============================================================================
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // ==================== 左图 ====================
    if (watched == label1jpg) {
        // ---------- 鼠标按下 ----------
        if (event->type() == QEvent::MouseButtonPress) {
            // 把 QEvent* 转成 QMouseEvent*
            QMouseEvent *mevent = (QMouseEvent *)event;

            if (mevent->buttons() & Qt::LeftButton) {
                labeldispinfo->setText("鼠标左键被按下：[左边图片]");
            }
            else if (mevent->buttons() & Qt::MiddleButton) {
                labeldispinfo->setText("鼠标中键被按下：[左边图片]");
            }
            else if (mevent->buttons() & Qt::RightButton) {
                labeldispinfo->setText("鼠标右键被按下：[左边图片]");
            }

            // ---------- 放大图片 2 倍 ----------
            QTransform transform;
            transform.scale(2, 2);
            QImage tempimage = image1jpg.transformed(transform);
            label1jpg->setPixmap(QPixmap::fromImage(tempimage));
        }

        // ---------- 鼠标释放 ----------
        if (event->type() == QEvent::MouseButtonRelease) {
            labeldispinfo->setText("鼠标按键已经释放：[左边图片]");
            label1jpg->setPixmap(QPixmap::fromImage(image1jpg));   // 恢复原图
        }
    }

    // ==================== 中图 ====================
    else if (watched == label2jpg) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mevent = (QMouseEvent *)event;

            if (mevent->buttons() & Qt::LeftButton) {
                labeldispinfo->setText("鼠标左键被按下：[中间图片]");
            }
            else if (mevent->buttons() & Qt::MiddleButton) {
                labeldispinfo->setText("鼠标中键被按下：[中间图片]");
            }
            else if (mevent->buttons() & Qt::RightButton) {
                labeldispinfo->setText("鼠标右键被按下：[中间图片]");
            }

            // 放大 2.5 倍
            QTransform transform;
            transform.scale(2.5, 2.5);
            QImage tempimage = image2jpg.transformed(transform);
            label2jpg->setPixmap(QPixmap::fromImage(tempimage));
        }

        if (event->type() == QEvent::MouseButtonRelease) {
            labeldispinfo->setText("鼠标按键已经释放：[中间图片]");
            label2jpg->setPixmap(QPixmap::fromImage(image2jpg));
        }
    }

    // ==================== 右图 ====================
    else if (watched == label3jpg) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mevent = (QMouseEvent *)event;

            if (mevent->buttons() & Qt::LeftButton) {
                labeldispinfo->setText("鼠标左键被按下：[右边图片]");
            }
            else if (mevent->buttons() & Qt::MiddleButton) {
                labeldispinfo->setText("鼠标中键被按下：[右边图片]");
            }
            else if (mevent->buttons() & Qt::RightButton) {
                labeldispinfo->setText("鼠标右键被按下：[右边图片]");
            }

            // 放大 3 倍
            QTransform transform;
            transform.scale(3, 3);
            QImage tempimage = image3jpg.transformed(transform);
            label3jpg->setPixmap(QPixmap::fromImage(tempimage));
        }

        if (event->type() == QEvent::MouseButtonRelease) {
            labeldispinfo->setText("鼠标按键已经释放：[右边图片]");
            label3jpg->setPixmap(QPixmap::fromImage(image3jpg));
        }
    }

    // 交给基类做默认处理
    return QMainWindow::eventFilter(watched, event);
}