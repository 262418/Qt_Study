#include "frmanimationbutton.h"
#include "ui_frmanimationbutton.h"

FrmAnimationButton::FrmAnimationButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmAnimationButton)
{
    ui->setupUi(this);

    // 设置窗口背景渐变色（深蓝色到浅蓝色）
    QString qss = "color:#BECEC6;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1B3152,stop:1 #255C80);";
    this->setStyleSheet(qss);

    // 初始化四个带图标的按钮
    ui->widget1->settext("主页");
    ui->widget1->setimage(":/new/prefix1/image/v-home.png");

    ui->widget2->settext("通讯录");
    ui->widget2->setimage(":/new/prefix1/image/v-contact.png");

    ui->widget3->settext("相册");
    ui->widget3->setimage(":/new/prefix1/image/v-img.png");

    ui->widget4->settext("录音");
    ui->widget4->setimage(":/new/prefix1/image/v-record.png");
}

FrmAnimationButton::~FrmAnimationButton()
{
    delete ui;
}