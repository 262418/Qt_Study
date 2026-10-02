#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QLabel *labelmsg,*labeldispmsg;
    QPushButton *msgbutton;
    QGridLayout *glayout;
private slots:
    void cumstomMsg();
};
#endif // DIALOG_H
