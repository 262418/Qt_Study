#include "qmyselfvideowidget.h"

QMyselfVideoWidget::QMyselfVideoWidget(QWidget *parent) : QVideoWidget(parent)
{
}

void QMyselfVideoWidget::SetMediaPlayer(QMediaPlayer *player)
{
    theplayer = player;
}

void QMyselfVideoWidget::keyPressEvent(QKeyEvent *event)
{
    // 如果是 ESC 键，且处于全屏状态，则退出全屏
    if ((event->key() == Qt::Key_Escape) && (isFullScreen()))
    {
        setFullScreen(false);
        event->accept();
    }
    QVideoWidget::keyPressEvent(event);
}

void QMyselfVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && theplayer)
    {
        // Qt 6：用 playbackState() 代替 state()
        if (theplayer->playbackState() == QMediaPlayer::PlayingState)
            theplayer->pause();
        else
            theplayer->play();
    }
    QVideoWidget::mousePressEvent(event);
}