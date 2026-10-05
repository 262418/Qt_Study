#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("测试鼠标事件程序");

    // ==================== 状态栏控件 ====================
    // ---------- 左侧：事件消息 ----------
    statuslabel = new QLabel;
    statuslabel->setText("鼠标在当前窗口坐标为：");
    statuslabel->setFixedWidth(200);

    // ---------- 右侧：坐标 ----------
    mouselabelpos = new QLabel;
    mouselabelpos->setText("");
    mouselabelpos->setFixedWidth(200);

    // addPermanentWidget：把控件添加到状态栏右侧（永久显示）
    statusBar()->addPermanentWidget(statuslabel);
    statusBar()->addPermanentWidget(mouselabelpos);

    // ==================== 开启鼠标追踪 ====================
    setMouseTracking(true);        // 不按键也能收到 mouseMoveEvent
    // 默认 false：只有按住鼠标键移动才触发 mouseMoveEvent

    resize(800, 600);

    disppicture();                  // 显示图片
}

MainWindow::~MainWindow()
{
}

// 鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    // e->x() 和 e->y() 是相对当前 widget 的坐标
    mouselabelpos->setText(
        "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")"
        );
}
// setMouseTracking(true) 后，不按键移动也会触发

// 鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QString qstr = "(" + QString::number(e->x()) + "," +
                   QString::number(e->y()) + ")";

    // 用 button()（单数）判断"哪个键按下"
    if (e->button() == Qt::LeftButton) {
        statusBar()->showMessage("用户已按下鼠标[左键]坐标" + qstr);
    }
    else if (e->button() == Qt::RightButton) {
        statusBar()->showMessage("用户已按下鼠标[右键]坐标" + qstr);
    }
    else if (e->button() == Qt::MiddleButton) {
        statusBar()->showMessage("用户已按下鼠标[中键]坐标" + qstr);
    }
}

// 鼠标释放事件
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QString qstr = "(" + QString::number(e->x()) + "," +
                   QString::number(e->y()) + ")";

    // 第二个参数 2000 表示消息显示 2000 毫秒后消失
    statusBar()->showMessage("用户已释放鼠标坐标" + qstr, 2000);
}

// 显示图片
void MainWindow::disppicture()
{
    QString filenames("D:/Qt_Project/Graphic_Model_View/images/C.jpg");
    // 硬编码绝对路径

    QImage image;
    QLabel *imagelabel = new QLabel(this);           // 父对象是主窗口

    imagelabel->move(20, 20);
    imagelabel->setFixedSize(700, 400);

    if (!image.load(filenames)) {
        QMessageBox::information(this, "失败", "加载图片失败，请重新检查？");
        return;
    }

    imagelabel->setPixmap(QPixmap::fromImage(image));

}