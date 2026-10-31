#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QList>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // --- Qt 6 媒体核心 ---
    QMediaPlayer *player;      // 播放器（只负责解码）
    QAudioOutput *audioOutput; // 音频输出（负责发声、音量）

    // --- 播放列表相关 ---
    QList<QUrl> playlist;      // 存储所有歌曲的真实本地 URL
    int currentIndex = -1;     // 当前正在播放的歌曲索引（-1 表示没播）

    // --- 时间显示相关 ---
    QString drtTime = "0:00";  // 总时长
    QString pstTime = "0:00";  // 当前播放时间

    // --- 核心防冲突标志 ---
    bool sliderUpdating = false;   // 防止进度条更新死循环
    bool isManualSwitching = false;   // 标记是否为手动切歌
    void updateSongName();         // 更新界面左上角的歌曲名字

private slots:
    void onstatechg(QMediaPlayer::PlaybackState state); // 状态改变（播放/暂停/停止）
    void onDrtchg(qint64 drt);                          // 总时长改变
    void onpstchg(qint64 pos);                          // 当前进度改变
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status); // 媒体状态（放完自动切歌）
    void onErrorOccurred(QMediaPlayer::Error error, const QString &errorString); // 报错处理
    void onListItemDoubleClicked(const QModelIndex &index); // 双击列表项播放

    // 按钮和滑块槽函数
    void on_pushButton_open_clicked();
    void on_pushButton_PLayer_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Prev_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_Volumn_clicked();
    void on_horizontalSlider_Volumn_valueChanged(int value);
    void on_horizontalSlider_Speed_valueChanged(int value);
};

#endif // MAINWINDOW_H