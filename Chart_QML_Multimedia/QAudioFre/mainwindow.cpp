#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 初始化播放器与音频输出（Qt 6 必须分开创建）
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5); // 初始音量 50%

    // 2. 绑定信号与槽
    connect(player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::onstatechg);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::onpstchg);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::onDrtchg);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
    connect(player, &QMediaPlayer::errorOccurred, this, &MainWindow::onErrorOccurred);

    // 双击列表里的歌曲名时，触发播放
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &MainWindow::onListItemDoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 更新界面上显示的当前歌曲名字
void MainWindow::updateSongName()
{
    QListWidgetItem *item = ui->listWidget->item(currentIndex);
    if (item)
        ui->label_Name->setText(item->text());
}

// 播放器状态改变时，更新按钮的亮暗
void MainWindow::onstatechg(QMediaPlayer::PlaybackState state)
{
    // 正在播放时，播放按钮禁用，暂停、停止按钮启用
    ui->pushButton_PLayer->setEnabled(state != QMediaPlayer::PlayingState);
    ui->pushButton_Pause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->pushButton_Stop->setEnabled(state == QMediaPlayer::PlayingState);
}

// 媒体状态改变（最核心的：自动连播功能）
void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "mediaStatus =" << status;

    // 1. 如果是“加载完成”状态（不管是手动切歌还是自然播完切歌）
    if (status == QMediaPlayer::LoadedMedia) {
        // 如果是手动切歌，加载完成后立刻播放
        if (isManualSwitching) {
            isManualSwitching = false; // 重置标志
            player->play();
        }
    }

    // 2. 如果是“这首歌播放结束”状态
    else if (status == QMediaPlayer::EndOfMedia && !playlist.isEmpty()) {
        // 自动切下一首
        currentIndex = (currentIndex + 1) % playlist.size();

        // 这里不需要设 isManualSwitching，因为 EndOfMedia 自然过渡
        player->setSource(playlist[currentIndex]);
        ui->listWidget->setCurrentRow(currentIndex);
        updateSongName();

        // 自然播完时，setSource 后直接 play 也可以，或者依靠上面的 LoadedMedia 播放
        player->play();
    }
}

// 播放器报错时，在控制台输出错误信息，方便排查
void MainWindow::onErrorOccurred(QMediaPlayer::Error error, const QString &errorString)
{
    qDebug() << "player error =" << error << errorString;
}

// 获取到文件总时长时触发
void MainWindow::onDrtchg(qint64 drt)
{
    // 设置进度条的最大值（进度条的单位是毫秒）
    ui->horizontalSlider_Speed->setMaximum(static_cast<int>(drt));

    // 把毫秒转换成 "分:秒" 的格式
    int sec = static_cast<int>(drt / 1000);
    int min = sec / 60;
    sec = sec % 60;

    drtTime = QString::asprintf("%d:%02d", min, sec);
    ui->label_Time->setText(pstTime + "/" + drtTime); // 刷新界面时间
}

// 当前播放进度改变时触发（自动更新进度条）
void MainWindow::onpstchg(qint64 pos)
{
    // 如果用户正在用鼠标拖着进度条，就不要自动更新，否则会和用户打架
    if (ui->horizontalSlider_Speed->isSliderDown())
        return;

    // ★ 防回环锁：标记现在是程序在改变进度条
    sliderUpdating = true;
    ui->horizontalSlider_Speed->setSliderPosition(static_cast<int>(pos));
    sliderUpdating = false; // 改完了，解锁

    // 把毫秒转成时间格式
    int sec = static_cast<int>(pos / 1000);
    int min = sec / 60;
    sec = sec % 60;

    pstTime = QString::asprintf("%d:%02d", min, sec);
    ui->label_Time->setText(pstTime + "/" + drtTime);
}

// 用户在界面双击某首歌时
void MainWindow::onListItemDoubleClicked(const QModelIndex &index)
{
    if (index.row() < 0 || index.row() >= playlist.size())
        return;

    currentIndex = index.row();

    // ★ 核心修改：先 stop 防止底层残留旧歌，挂上手动标志，再 setSource
    isManualSwitching = true;
    player->stop();
    player->setSource(playlist[currentIndex]);

    ui->listWidget->setCurrentRow(currentIndex);
    updateSongName();
    // 注意：这里不需要写 player->play()，交给下面的 mediaStatusChanged 处理
}

// 点击“打开”按钮，选择多首音乐
// 点击“打开”按钮，选择多首音乐
void MainWindow::on_pushButton_open_clicked()
{
    QString currentpath = QDir::homePath();
    QString dlgtitle = "请选择音频文件:";
    QString strfilter = "所有文件(*.*);;音频文件(*.mp3);;mp3文件(*.mp3)";

    QStringList filelist = QFileDialog::getOpenFileNames(
        this, dlgtitle, currentpath, strfilter);

    if (filelist.count() < 1)
        return;

    playlist.clear();
    ui->listWidget->clear();
    currentIndex = -1;

    for (int i = 0; i < filelist.count(); i++) {
        QString afile = filelist.at(i);
        playlist.append(QUrl::fromLocalFile(afile));
        QFileInfo fileinfo(afile);
        ui->listWidget->addItem(fileinfo.fileName());
    }

    // 核心修改：使用和切歌一样的逻辑，交给 mediaStatusChanged 去秒播
    if (!playlist.isEmpty()) {
        currentIndex = 0;

        isManualSwitching = true;       // 1. 挂起标志位
        player->stop();                 // 2. 停掉之前的残留
        player->setSource(playlist[0]); // 3. 加载第一首歌

        ui->listWidget->setCurrentRow(0);
        updateSongName();

        // 注意：这里千万不要写 player->play();
        // 等底层加载完，触发 LoadedMedia，自动执行 play()，绝对不会卡顿！
    }
}
// 点击“播放”按钮
void MainWindow::on_pushButton_PLayer_clicked()
{
    if (playlist.isEmpty())
        return;
    if (currentIndex < 0)
        currentIndex = 0;

    // 重新播放当前歌曲
    player->setSource(playlist[currentIndex]);
    updateSongName();
    player->play();
}

// 点击“暂停”
void MainWindow::on_pushButton_Pause_clicked()
{
    player->pause();
}

// 点击“停止”
void MainWindow::on_pushButton_Stop_clicked()
{
    player->stop();
}

// 点击“上一首”
void MainWindow::on_pushButton_Prev_clicked()
{
    if (playlist.isEmpty()) return;

    currentIndex = (currentIndex - 1 + playlist.size()) % playlist.size();

    isManualSwitching = true;
    player->stop();
    player->setSource(playlist[currentIndex]);

    ui->listWidget->setCurrentRow(currentIndex);
    updateSongName();
}

// 点击“下一首”
void MainWindow::on_pushButton_next_clicked()
{
    if (playlist.isEmpty()) return;

    currentIndex = (currentIndex + 1) % playlist.size();

    isManualSwitching = true;
    player->stop();
    player->setSource(playlist[currentIndex]);

    ui->listWidget->setCurrentRow(currentIndex);
    updateSongName();
}

// 静音按钮
void MainWindow::on_pushButton_Volumn_clicked()
{
    bool mute = audioOutput->isMuted();
    audioOutput->setMuted(!mute);

    if (mute)
        ui->pushButton_Volumn->setIcon(QIcon(":/new/prefix1/images/volumn.bmp"));
    else
        ui->pushButton_Volumn->setIcon(QIcon(":/new/prefix1/images/mute.bmp"));
}

// 拖动音量滑块
void MainWindow::on_horizontalSlider_Volumn_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0); // 0~100 映射到 0.0~1.0
}

// 拖动进度条跳转
void MainWindow::on_horizontalSlider_Speed_valueChanged(int value)
{
    // 如果是在被程序自动更新，直接 return 忽略
    if (sliderUpdating)
        return;

    // 如果是用户手动拖动，才改变播放进度
    player->setPosition(static_cast<qint64>(value));
}