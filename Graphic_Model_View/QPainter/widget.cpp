#include "widget.h"
#include "painterarea.h"

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QColorDialog>

// 构造函数
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Qt 绘图框架测试：QPainter");

    // ==================== 创建绘图区 ====================
    paintArea = new PainterArea(this);

    // ==================== 创建控制面板 ====================
    // ---------- 形状下拉框 ----------
    shapeLabel = new QLabel("绘制形状:", this);
    shapeCombo = new QComboBox(this);
    // addItem(显示文字, userData)
    // userData 存枚举值，索引变化也不影响
    shapeCombo->addItem("无",         static_cast<int>(PainterArea::Shape::None));
    shapeCombo->addItem("Line",       static_cast<int>(PainterArea::Shape::Line));
    shapeCombo->addItem("Rectangle",  static_cast<int>(PainterArea::Shape::Rectangle));

    // ---------- 画笔颜色 ----------
    penColorLabel = new QLabel("画笔颜色:", this);
    penColorBtn = new QPushButton(this);
    penColorBtn->setFixedSize(40, 24);
    // 用 QSS 显示当前颜色（黑色）
    penColorBtn->setStyleSheet("background-color: black; border: 1px solid gray;");

    // ---------- 填充颜色 ----------
    brushColorLabel = new QLabel("填充颜色:", this);
    brushColorBtn = new QPushButton(this);
    brushColorBtn->setFixedSize(40, 24);
    brushColorBtn->setStyleSheet("background-color: yellow; border: 1px solid gray;");

    // ---------- 画笔宽度 ----------
    penWidthLabel = new QLabel("画笔宽度:", this);
    penWidthSpin = new QSpinBox(this);
    penWidthSpin->setRange(1, 20);      // 1~20 像素
    penWidthSpin->setValue(2);           // 默认 2

    // ==================== 布局控制面板 ====================
    controlLayout = new QGridLayout;
    int row = 0;
    controlLayout->addWidget(shapeLabel,      row, 0);
    controlLayout->addWidget(shapeCombo,      row++, 1);

    controlLayout->addWidget(penColorLabel,   row, 0);
    controlLayout->addWidget(penColorBtn,     row++, 1);

    controlLayout->addWidget(brushColorLabel, row, 0);
    controlLayout->addWidget(brushColorBtn,   row++, 1);

    controlLayout->addWidget(penWidthLabel,   row, 0);
    controlLayout->addWidget(penWidthSpin,    row++, 1);

    controlLayout->setRowStretch(row, 1);   // 底部留空，控件靠上

    // ==================== 主布局 ====================
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(paintArea);           // 左：绘图区
    mainLayout->addLayout(controlLayout);        // 右：控制面板

    // ==================== 信号槽连接 ====================
    // ---------- 形状变化 ----------
    // QComboBox::currentIndexChanged 有重载，需要 QOverload 指定
    connect(shapeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Widget::onShapeChanged);

    // ---------- 画笔颜色按钮 ----------
    connect(penColorBtn, &QPushButton::clicked,
            this, &Widget::onPenColorClicked);

    // ---------- 填充颜色按钮 ----------
    connect(brushColorBtn, &QPushButton::clicked,
            this, &Widget::onBrushColorClicked);

    // ---------- 画笔宽度变化 ----------
    connect(penWidthSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Widget::onPenWidthChanged);

    // ---------- 初始状态：默认选中"无" ----------
    shapeCombo->setCurrentIndex(0);
}

Widget::~Widget() = default;

// 槽：形状下拉框变化
void Widget::onShapeChanged(int index)
{
    // 从 userData 取回枚举值（更稳定，不依赖索引）
    QVariant data = shapeCombo->itemData(index, Qt::UserRole);
    PainterArea::Shape shape =
        static_cast<PainterArea::Shape>(data.toInt());

    paintArea->setShape(shape);
}

// 槽：选择画笔颜色
void Widget::onPenColorClicked()
{
    // 弹出颜色对话框，初始颜色是当前画笔颜色
    QColor color = QColorDialog::getColor(
        paintArea->pen().color(),   // 初始颜色
        this,
        "选择画笔颜色"
        );

    if (!color.isValid()) return;   // 用户取消

    // 保留宽度，只改颜色
    QPen pen = paintArea->pen();
    pen.setColor(color);
    paintArea->setPen(pen);

    // 更新按钮颜色显示
    penColorBtn->setStyleSheet(QString(
                                   "background-color: %1; border: 1px solid gray;"
                                   ).arg(color.name()));
}

// 槽：选择填充颜色
void Widget::onBrushColorClicked()
{
    QColor color = QColorDialog::getColor(
        paintArea->brush().color(),
        this,
        "选择填充颜色"
        );

    if (!color.isValid()) return;

    paintArea->setBrush(QBrush(color));

    brushColorBtn->setStyleSheet(QString(
                                     "background-color: %1; border: 1px solid gray;"
                                     ).arg(color.name()));
}

// 槽：画笔宽度变化
void Widget::onPenWidthChanged(int width)
{
    QPen pen = paintArea->pen();
    pen.setWidth(width);
    paintArea->setPen(pen);
}