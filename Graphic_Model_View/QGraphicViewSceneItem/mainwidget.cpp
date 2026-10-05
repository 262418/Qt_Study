#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("GraphicsView图形视图架构--应用程序测试");

    // ---------- 初始化累计变量 ----------
    iAngle = 3;              // 初始角度
    scalevalues = 3;         // 初始缩放
    leanvalues = 3;          // 初始倾斜

    // ==================== 场景 ====================
    QGraphicsScene *sence = new QGraphicsScene;
    // setSceneRect(x, y, w, h)：场景的逻辑范围
    // 以 (-200, -200) 为左上角，380×380 大小
    sence->setSceneRect(-200, -200, 380, 380);

    // 加载图片（绝对路径，不适合发布）
    QPixmap *pixmap = new QPixmap(
        "D:\\Qt_Project\\Graphic_Model_View\\images\\C.jpg"
        );

    // ==================== 图元 ====================
    pixitem = new PixItem(pixmap);    // 创建自定义图元
    sence->addItem(pixitem);           // 加入场景
    pixitem->setPos(0, 0);             // 放在场景原点

    // ==================== 视图 ====================
    view = new QGraphicsView;
    view->setScene(sence);              // 视图绑定场景
    view->setMinimumSize(800, 600);

    // ==================== 控制面板 ====================
    controlframe = new QFrame;
    CreateControlFrameFunc();           // 创建右侧控件

    // ==================== 主布局 ====================
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(view);
    hlayout->addWidget(controlframe);
    setLayout(hlayout);
}

MainWidget::~MainWidget()
{
    // 未释放 pixitem 等资源（其实会被 Qt 父子机制自动释放）
}

// ============================================================================
// 旋转：新角度 - 旧角度 = 增量
// ============================================================================
void MainWidget::rotateFunc(int val)
{
    view->rotate(val - iAngle);   // 只旋转增量，不是绝对值
    iAngle = val;                  // 更新累计值
}
//   为什么不是 view->rotate(val)？
//   因为 view->rotate() 是"相对旋转"
//   如果每次传绝对值，会累积旋转 val 度
//   例如：滑块从 3 到 4 到 5，旋转累计 3+4+5=12 度（错）
//   用增量：旋转 1+1=2 度（对）

// ============================================================================
// 缩放：根据增量计算缩放因子
// ============================================================================
void MainWidget::scaleFunc(int val)
{
    qreal qs;
    if (val > scalevalues) {
        // 放大：1.1 的 (val - scalevalues) 次方
        qs = pow(1.1, (val - scalevalues));
    } else {
        // 缩小：1/1.1 的 (scalevalues - val) 次方
        qs = pow(1 / 1.1, (scalevalues - val));
    }
    view->scale(qs, qs);
    scalevalues = val;
}
// 例如：val=3 → 4，qs = 1.1^1 = 1.1（放大 10%）
//       val=4 → 3，qs = (1/1.1)^1 ≈ 0.909（缩小到 90.9%）

// ============================================================================
// 倾斜：水平倾斜（剪切变换）
// ============================================================================
void MainWidget::leanFunc(int val)
{
    // shear(sh, sv)：水平倾斜 sh，垂直倾斜 sv
    // 参数是"斜率"，不是角度
    view->shear((val - leanvalues) / 2.0, 0);
    leanvalues = val;
}
// 例如：val 从 3 到 4，shear(0.5, 0)
//       每次倾斜 0.5 的斜率

// ============================================================================
// 创建控制面板
// ============================================================================
void MainWidget::CreateControlFrameFunc()
{
    // ==================== 旋转 ====================
    QSlider *rotatesilder = new QSlider;                    // 拼写应为 slider
    rotatesilder->setOrientation(Qt::Horizontal);
    rotatesilder->setRange(0, 360);

    QHBoxLayout *rotatelayout = new QHBoxLayout;
    rotatelayout->addWidget(rotatesilder);

    QGroupBox *rotategroup = new QGroupBox("图形旋转");
    rotategroup->setLayout(rotatelayout);

    // ==================== 缩放 ====================
    QSlider *scalesilder = new QSlider;
    scalesilder->setOrientation(Qt::Horizontal);
    scalesilder->setRange(0, 2 * scalevalues);              // 0~6
    scalesilder->setValue(scalevalues);                      // 初始 3

    QHBoxLayout *scalelayout = new QHBoxLayout;
    scalelayout->addWidget(scalesilder);

    QGroupBox *scalegroup = new QGroupBox("图形缩放");
    scalegroup->setLayout(scalelayout);

    // ==================== 倾斜 ====================
    QSlider *leansilder = new QSlider;
    leansilder->setOrientation(Qt::Horizontal);
    leansilder->setRange(0, 2 * leanvalues);
    leansilder->setValue(leanvalues);

    QHBoxLayout *leanlayout = new QHBoxLayout;
    leanlayout->addWidget(leansilder);

    QGroupBox *leangroup = new QGroupBox(tr("图形倾斜"));
    leangroup->setLayout(leanlayout);

    // ==================== 信号槽连接 ====================
    connect(rotatesilder, SIGNAL(valueChanged(int)), this, SLOT(rotateFunc(int)));
    connect(scalesilder,  SIGNAL(valueChanged(int)), this, SLOT(scaleFunc(int)));
    connect(leansilder,   SIGNAL(valueChanged(int)), this, SLOT(leanFunc(int)));

    // ==================== 控制面板布局 ====================
    QVBoxLayout *vlayoutframe = new QVBoxLayout;
    vlayoutframe->addWidget(rotategroup);
    vlayoutframe->addWidget(scalegroup);
    vlayoutframe->addWidget(leangroup);

    controlframe->setLayout(vlayoutframe);
}