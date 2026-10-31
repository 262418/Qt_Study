#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmyselfvideowidget.h"
#include <QMediaPlayer>
#include <QAudioOutput>   // Qt 6 必须引入音频输出模块
#include <QFileDialog>

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
    QMediaPlayer *player;
    QAudioOutput *audioOutput; // Qt 6 必须自己管理音频输出
    QString drtTime;           // 视频总时长
    QString posTime;           // 当前播放进度

private slots:
    // 注意：Qt 6 的状态枚举叫 PlaybackState，信号叫 playbackStateChanged
    void onstatebuttonchanged(QMediaPlayer::PlaybackState state);
    void ondrttimechanged(qint64 drt);
    void onpostimechanged(qint64 pos);
    void on_pushButton_Open_clicked();
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Volumn_clicked();
    void on_horizontalSlider_Volumn_valueChanged(int value);
    void on_horizontalSlider_position_valueChanged(int value);
};

#endif // MAINWINDOW_H