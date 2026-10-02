#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(260, 90);

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);

    // ==================== 创建控件 ====================
    labelmsg = new QLabel("自定义消息框");
    msgbutton = new QPushButton("测试操作");
    labeldispmsg = new QLabel("未测试状态");

    // ==================== 布局 ====================
    glayout->addWidget(labelmsg,     0, 0);        // 第0行第0列
    glayout->addWidget(msgbutton,    0, 1);        // 第0行第1列
    glayout->addWidget(labeldispmsg, 1, 0, 1, 1);  // 第1行第0列（跨1行1列）

    // ==================== 信号槽 ====================
    connect(msgbutton, SIGNAL(clicked()), this, SLOT(cumstomMsg()));
}

Dialog::~Dialog() = default;

// ==================== 自定义消息框 ====================
void Dialog::cumstomMsg()
{
    // 创建 QMessageBox 对象（而非静态方法）
    QMessageBox cMsgBox;

    // 设置窗口标题
    cMsgBox.setWindowTitle("消息框");

    // 添加自定义按钮
    // addButton(文字, 角色) 返回按钮指针，可用于后续判断
    QPushButton *yes = cMsgBox.addButton("Yes", QMessageBox::ActionRole);
    QPushButton *no  = cMsgBox.addButton("No",  QMessageBox::ActionRole);

    // 自定义图标（本地图片）
    cMsgBox.setIconPixmap(QPixmap("C:\\Users\\Acer\\Pictures\\Predator\\嘻嘻.png"));

    // 模态显示，等待用户操作
    cMsgBox.exec();

    // 通过 clickedButton() 判断用户点击了哪个按钮
    if (cMsgBox.clickedButton() == yes) {
        labeldispmsg->setText("用户点击Yes按钮");
    } else if (cMsgBox.clickedButton() == no) {
        labeldispmsg->setText("用户点击no按钮");
    }
}