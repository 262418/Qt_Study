#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建播放器
    player = new QMediaPlayer(this);

    // Qt 6 必须创建音频输出，并绑定给播放器，否则没声音
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // 2. 设置视频输出组件
    player->setVideoOutput(ui->graphicsView);

    // 3. 设置显示组件的关联播放器（为了响应鼠标点击）
    ui->graphicsView->SetMediaPlayer(player);

    // 4. 连接信号与槽（Qt 6 的新信号名）
    connect(player, &QMediaPlayer::playbackStateChanged,
            this, &MainWindow::onstatebuttonchanged);

    connect(player, &QMediaPlayer::positionChanged,
            this, &MainWindow::onpostimechanged);

    connect(player, &QMediaPlayer::durationChanged,
            this, &MainWindow::ondrttimechanged);

    // 初始化音量
    player->audioOutput()->setVolume(0.5); // 0.0 到 1.0
    ui->horizontalSlider_Volumn->setValue(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 控制按钮状态切换（参数类型变成 PlaybackState）
void MainWindow::onstatebuttonchanged(QMediaPlayer::PlaybackState state)
{
    // 如果正在播放，禁用播放按钮，启用暂停和停止按钮
    ui->pushButton_Play->setEnabled(state != QMediaPlayer::PlayingState);
    ui->pushButton_Pause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->pushButton_Stop->setEnabled(state == QMediaPlayer::PlayingState);
}

// 视频总时长解析
void MainWindow::ondrttimechanged(qint64 drt)
{
    ui->horizontalSlider_position->setMaximum(drt);
    int sec = drt / 1000;
    int min = sec / 60;
    sec = sec % 60;
    drtTime = QString::asprintf("%d:%02d", min, sec);
    ui->label_Time->setText(posTime + " | " + drtTime);
}

// 当前播放进度解析
void MainWindow::onpostimechanged(qint64 pos)
{
    if (ui->horizontalSlider_position->isSliderDown())
        return;

    ui->horizontalSlider_position->setSliderPosition(pos);
    int sec = pos / 1000;
    int min = sec / 60;
    sec = sec % 60;
    posTime = QString::asprintf("%d:%02d", min, sec);
    ui->label_Time->setText(posTime + " | " + drtTime);
}

// 打开文件
void MainWindow::on_pushButton_Open_clicked()
{
    QString currentpath = QDir::homePath();
    QString dlgtitle = "请选择视频文件";
    QString filter = "所有文件(*.*);;mp4文件(*.mp4)";
    QString strfile = QFileDialog::getOpenFileName(this, dlgtitle, currentpath, filter);

    if (strfile.isEmpty())
        return;

    QFileInfo fileinfo(strfile);
    ui->label_Name->setText(fileinfo.fileName());

    // Qt 6：setMedia 参数直接传 QUrl，不需要 QMediaContent 包装
    player->setSource(QUrl::fromLocalFile(strfile));
    player->play();
}

void MainWindow::on_pushButton_Play_clicked()
{
    player->play();
}

void MainWindow::on_pushButton_Pause_clicked()
{
    player->pause();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    player->stop();
}

// 静音控制
void MainWindow::on_pushButton_Volumn_clicked()
{
    bool bmute = player->audioOutput()->isMuted();
    player->audioOutput()->setMuted(!bmute);

    if (!bmute) // 如果之前没静音，说明现在静音了
        ui->pushButton_Volumn->setIcon(QIcon(":/new/prefix1/images/mute.bmp"));
    else        // 如果之前静音了，说明现在恢复声音了
        ui->pushButton_Volumn->setIcon(QIcon(":/new/prefix1/images/volumn.bmp"));
}

// 音量调节（0-100 映射到 0.0-1.0）
void MainWindow::on_horizontalSlider_Volumn_valueChanged(int value)
{
    if (player->audioOutput()) {
        player->audioOutput()->setVolume(value / 100.0);
    }
}

// 进度条拖动
void MainWindow::on_horizontalSlider_position_valueChanged(int value)
{
    player->setPosition(value);
}