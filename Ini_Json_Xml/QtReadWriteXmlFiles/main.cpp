#include "readwritexml.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReadWriteXml w;
    w.show();
    return a.exec();
}
