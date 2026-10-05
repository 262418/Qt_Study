#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(300, 160);
    setWindowTitle("Qt窗口常用的API位置函数测试");

    // ==================== 主布局 ====================
    glayout = new QGridLayout(this);

    // ==================== 创建 5 组标签 ====================
    labelgeometry      = new QLabel("函数geometry():");
    labelgeometryvalue = new QLabel;

    labelwidth      = new QLabel("函数width():");
    labelwidthvalue = new QLabel;

    labelheight      = new QLabel("函数height():");
    labelheightvalue = new QLabel;

    labelrect      = new QLabel("函数rect()");
    labelrectvalue = new QLabel;

    labelsize      = new QLabel("函数size():");
    labelsizevalue = new QLabel;

    // ==================== 布局摆放 ====================
    // 左侧显示函数名，右侧显示值
    glayout->addWidget(labelgeometry,      0, 0);
    glayout->addWidget(labelgeometryvalue, 0, 1);

    glayout->addWidget(labelwidth,         1, 0);
    glayout->addWidget(labelwidthvalue,    1, 1);

    glayout->addWidget(labelheight,        2, 0);
    glayout->addWidget(labelheightvalue,   2, 1);

    glayout->addWidget(labelrect,          3, 0);
    glayout->addWidget(labelrectvalue,     3, 1);

    glayout->addWidget(labelsize,          4, 0);
    glayout->addWidget(labelsizevalue,     4, 1);

    // ==================== 首次更新数值 ====================
    UpdateLabelFunc();
}

Dialog::~Dialog() = default;

// ==================== 窗口大小变化事件 ====================
void Dialog::resizeEvent(QResizeEvent *)
{
    // 每次窗口大小变化，重新计算并显示
    UpdateLabelFunc();
}

// ==================== 窗口移动事件 ====================
void Dialog::moveEvent(QMoveEvent *)
{
    // 每次窗口移动，重新计算并显示
    UpdateLabelFunc();
}

// ==================== 更新所有标签 ====================
void Dialog::UpdateLabelFunc()
{
    // ---------- geometry()：客户区相对屏幕的位置和大小 ----------
    // geometry().x() / y()：窗口左上角相对屏幕的坐标
    // geometry().width() / height()：窗口客户区的宽高
    QString strgeometry;
    QString str1, str2, str3, str4;
    strgeometry = str1.setNum(geometry().x())   + "," +
                  str2.setNum(geometry().y())   + "," +
                  str3.setNum(geometry().width())  + "," +
                  str4.setNum(geometry().height());
    labelgeometryvalue->setText(strgeometry);

    // ---------- width() / height()：窗口客户区宽高 ----------
    QString strw, strh;
    labelwidthvalue->setText(strw.setNum(width()));
    labelheightvalue->setText(strh.setNum(height()));

    // ---------- rect()：窗口内部坐标系的矩形 ----------
    // rect() = QRect(0, 0, width(), height())
    QString strrect, strrect1, strrect2, strrect3, strrect4;
    strrect = strrect1.setNum(rect().x())      + "," +
              strrect2.setNum(rect().y())      + "," +
              strrect3.setNum(width())         + "," +
              strrect4.setNum(height());
    labelrectvalue->setText(strrect);

    // ---------- size()：窗口尺寸 ----------
    QString strsize, strsize1, strsize2;
    strsize = strsize1.setNum(size().width())  + "," +
              strsize2.setNum(size().height());
    labelsizevalue->setText(strsize);
}