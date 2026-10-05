#include "qdirfileviews.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDirFileViews w;
    w.show();
    return QApplication::exec();
}
