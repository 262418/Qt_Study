#ifndef QMYSELFVIDEOWIDGET_H
#define QMYSELFVIDEOWIDGET_H

#include <QVideoWidget> // Qt 6 中 QVideoWidget 属于 multimediawidgets 模块
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QMouseEvent>

class QMyselfVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    QMyselfVideoWidget(QWidget *parent = nullptr);
    void SetMediaPlayer(QMediaPlayer *player);

protected:
    void keyPressEvent(QKeyEvent *event) override;     // 键盘事件：ESC 退出全屏
    void mousePressEvent(QMouseEvent *event) override; // 鼠标事件：左键暂停/播放
void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    QMediaPlayer *theplayer = nullptr;
};

#endif // QMYSELFVIDEOWIDGET_H