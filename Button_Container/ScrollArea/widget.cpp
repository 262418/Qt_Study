#include "widget.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // ---------- 窗口基础设置 ----------
    resize(400, 300);
    setWindowTitle("图片查看器");

    // ---------- 创建显示图片的 QLabel ----------
    QLabel *imageLabel = new QLabel;

    // 保持宽高比缩放图片（不用 setScaledContents，避免变形）
    // 这里先加载原图，尺寸在窗口 resize 时会重算（见下方 resizeEvent）
    QPixmap pixmap(":/new/prefix1/Image/C.jpg");
    if (pixmap.isNull()) {
        qDebug() << "图片加载失败，请检查资源路径 :/new/prefix1/Image/C.jpg";
        imageLabel->setText("图片加载失败");
        imageLabel->setAlignment(Qt::AlignCenter);
    } else {
        imageLabel->setPixmap(pixmap);
        imageLabel->setAlignment(Qt::AlignCenter);
        // 记录原图，供后续缩放使用
        imageLabel->setProperty("originalPixmap", pixmap);
    }

    // ---------- 创建滚动区域 ----------
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignCenter);   // 内容在滚动区居中
    scrollArea->setWidgetResizable(true);        // 内容随容器缩放
    scrollArea->setWidget(imageLabel);           // 设内容控件（imageLabel 父对象变 scrollArea）

    // 滚动条策略：需要时才显示（内容缩放后一般用不上）
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // ---------- 主布局 ----------
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->setContentsMargins(0, 0, 0, 0);   // 去掉边距，让图片铺满
}

Widget::~Widget() = default;