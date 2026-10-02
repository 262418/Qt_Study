#include "dialog.h"
#include <QMessageBox>
#include <QIntValidator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("员工信息");

    // ---------- 左侧表单 ----------
    numberLabel = new QLabel("员工编号:", this);
    numberEdit  = new QLineEdit(this);

    nameLabel = new QLabel("员工姓名:", this);
    nameEdit  = new QLineEdit(this);

    sexLabel  = new QLabel("员工性别:", this);
    sexCombo  = new QComboBox(this);
    sexCombo->addItem("男");
    sexCombo->addItem("女");

    departLabel = new QLabel("所在部门:", this);
    departEdit  = new QLineEdit(this);

    ageLabel = new QLabel("年龄:", this);
    ageEdit  = new QLineEdit(this);
    ageEdit->setValidator(new QIntValidator(0, 150, this));

    leftLayout = new QGridLayout;
    leftLayout->addWidget(numberLabel, 0, 0);
    leftLayout->addWidget(numberEdit,  0, 1);
    leftLayout->addWidget(nameLabel,   1, 0);
    leftLayout->addWidget(nameEdit,    1, 1);
    leftLayout->addWidget(sexLabel,    2, 0);
    leftLayout->addWidget(sexCombo,    2, 1);
    leftLayout->addWidget(departLabel, 3, 0);
    leftLayout->addWidget(departEdit,  3, 1);
    leftLayout->addWidget(ageLabel,    4, 0);
    leftLayout->addWidget(ageEdit,     4, 1);
    leftLayout->setColumnStretch(0, 1);
    leftLayout->setColumnStretch(1, 3);

    // ---------- 右侧简历 ----------
    resumeLabel = new QLabel("个人简历:", this);
    resumeEdit  = new QTextEdit(this);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(resumeLabel);
    rightLayout->addWidget(resumeEdit);

    // ---------- 底部按钮 ----------
    okButton     = new QPushButton("确认", this);
    cancelButton = new QPushButton("退出", this);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton,     &QPushButton::clicked, this, &Dialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &Dialog::onCancelClicked);

    // ---------- 主布局 ----------
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout,   0, 0);
    mainLayout->addLayout(rightLayout,  0, 1);
    mainLayout->addLayout(buttonLayout, 1, 0, 1, 2);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

Dialog::~Dialog() = default;

void Dialog::onOkClicked()
{
    if (numberEdit->text().isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写员工编号");
        numberEdit->setFocus();
        return;
    }
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写员工姓名");
        nameEdit->setFocus();
        return;
    }
    accept();
}

void Dialog::onCancelClicked()
{
    reject();
}