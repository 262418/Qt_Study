#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

    // 数据读取接口
    QString number() const { return numberEdit->text(); }
    QString name()   const { return nameEdit->text(); }
    QString sex()    const { return sexCombo->currentText(); }
    QString depart() const { return departEdit->text(); }
    int     age()    const { return ageEdit->text().toInt(); }
    QString resume() const { return resumeEdit->toPlainText(); }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    QGridLayout *mainLayout;
    // 左侧表单
    QGridLayout *leftLayout;
    QLabel *numberLabel;
    QLineEdit *numberEdit;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *sexLabel;
    QComboBox *sexCombo;
    QLabel *departLabel;
    QLineEdit *departEdit;      // 改为单行
    QLabel *ageLabel;
    QLineEdit *ageEdit;

    // 右侧简历
    QVBoxLayout *rightLayout;
    QLabel *resumeLabel;
    QTextEdit *resumeEdit;

    // 底部按钮
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
};
#endif // DIALOG_H