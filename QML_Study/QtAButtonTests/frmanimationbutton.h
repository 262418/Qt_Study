#ifndef FRMANIMATIONBUTTON_H
#define FRMANIMATIONBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FrmAnimationButton; }
QT_END_NAMESPACE

class FrmAnimationButton : public QWidget
{
    Q_OBJECT

public:
    FrmAnimationButton(QWidget *parent = nullptr);
    ~FrmAnimationButton();
private:
    Ui::FrmAnimationButton *ui;
};
#endif // FRMANIMATIONBUTTON_H
