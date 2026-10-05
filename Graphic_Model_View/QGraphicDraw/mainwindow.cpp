#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("图形绘制综合案例分析(双缓冲机制)");

    // ---------- 中央控件 ----------
    drawWidget = new DrawWidget;
    setCentralWidget(drawWidget);

    // ---------- 创建工具栏 ----------
    CreateToolBarFunc();

    setMinimumSize(600, 400);

    // ---------- 初始状态 ----------
    disstyle();                                              // 同步线形
    drawWidget->setWidth(spinboxlabelwidth->value());        // 同步线宽
    drawWidget->setColor(Qt::blue);                          // 初始蓝色
}

MainWindow::~MainWindow() = default;

// 创建工具栏

void MainWindow::CreateToolBarFunc()
{
    QToolBar *toolBar = addToolBar("Tool");

    // ---------- 线形风格下拉框 ----------
    labelstyle = new QLabel("线形风格");
    comboboxlabelstyle = new QComboBox;

    // addItem(显示文字, userData)
    // userData 存 Qt::PenStyle 枚举值
    comboboxlabelstyle->addItem("SolidLine",    static_cast<int>(Qt::SolidLine));
    comboboxlabelstyle->addItem("DotLine",      static_cast<int>(Qt::DotLine));
    comboboxlabelstyle->addItem("DashLine",     static_cast<int>(Qt::DashLine));
    comboboxlabelstyle->addItem("DashDotLine",  static_cast<int>(Qt::DashDotLine));

    connect(comboboxlabelstyle, SIGNAL(activated(int)),
            this, SLOT(disstyle()));

    // ---------- 线宽微调框 ----------
    labelwidth = new QLabel("线形宽度:");
    spinboxlabelwidth = new QSpinBox;
    connect(spinboxlabelwidth, SIGNAL(valueChanged(int)),
            drawWidget, SLOT(setWidth(int)));

    // ---------- 颜色按钮 ----------
    colorbutton = new QToolButton;
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);                     // 黑色初始色块
    colorbutton->setIcon(QIcon(pixmap));
    connect(colorbutton, SIGNAL(clicked()),
            this, SLOT(discolor()));

    // ---------- 清除按钮 ----------
    clearbutton = new QToolButton;
    clearbutton->setText("清除绘制");
    connect(clearbutton, SIGNAL(clicked()),
            drawWidget, SLOT(clearFunc()));

    // ---------- 加入工具栏 ----------
    toolBar->addWidget(labelstyle);
    toolBar->addWidget(comboboxlabelstyle);
    toolBar->addWidget(labelwidth);
    toolBar->addWidget(spinboxlabelwidth);
    toolBar->addWidget(colorbutton);
    toolBar->addWidget(clearbutton);
}

// 线形变化
void MainWindow::disstyle()
{
    // 从 itemData 取 userData，转成 int 后传给 setStyle
    int style = comboboxlabelstyle->itemData(
                                      comboboxlabelstyle->currentIndex(),
                                      Qt::UserRole
                                      ).toInt();
    drawWidget->setStyle(style);
}

// 颜色变化
void MainWindow::discolor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) {
        drawWidget->setColor(color);

        // 更新按钮图标显示当前颜色
        QPixmap ps(20, 20);
        ps.fill(color);
        colorbutton->setIcon(QIcon(ps));
    }
}