#include "qjsonoper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QJsonOper w;
    w.show();
    return a.exec();
}
