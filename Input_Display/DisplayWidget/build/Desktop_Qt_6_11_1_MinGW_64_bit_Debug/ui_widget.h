/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *labeljpg;
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;
    QCalendarWidget *calendarWidget;
    QPushButton *progressBar_2;
    QLCDNumber *lcdNumber;
    QPushButton *pushbuttonstart;
    QPushButton *pushbuttonpause;
    QPushButton *pushbuttonreset;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(893, 950);
        labeljpg = new QLabel(Widget);
        labeljpg->setObjectName("labeljpg");
        labeljpg->setGeometry(QRect(30, 30, 521, 391));
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 480, 351, 211));
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(80, 750, 441, 41));
        progressBar->setValue(24);
        calendarWidget = new QCalendarWidget(Widget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(540, 460, 301, 241));
        progressBar_2 = new QPushButton(Widget);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setGeometry(QRect(520, 750, 141, 41));
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(590, 200, 131, 111));
        pushbuttonstart = new QPushButton(Widget);
        pushbuttonstart->setObjectName("pushbuttonstart");
        pushbuttonstart->setGeometry(QRect(740, 200, 131, 31));
        pushbuttonpause = new QPushButton(Widget);
        pushbuttonpause->setObjectName("pushbuttonpause");
        pushbuttonpause->setGeometry(QRect(740, 240, 131, 31));
        pushbuttonreset = new QPushButton(Widget);
        pushbuttonreset->setObjectName("pushbuttonreset");
        pushbuttonreset->setGeometry(QRect(740, 280, 131, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        labeljpg->setText(QCoreApplication::translate("Widget", "\346\226\207\346\234\254\346\240\207\347\255\276", nullptr));
        progressBar_2->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225\350\277\233\345\272\246\346\235\241", nullptr));
        pushbuttonstart->setText(QCoreApplication::translate("Widget", "start", nullptr));
        pushbuttonpause->setText(QCoreApplication::translate("Widget", "pause", nullptr));
        pushbuttonreset->setText(QCoreApplication::translate("Widget", "reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
