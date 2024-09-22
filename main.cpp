#include "rgbxyzlab.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rgbxyzlab w;
    w.show();
    return a.exec();
}
