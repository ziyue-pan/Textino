#include "Textino.h"

#include <QApplication>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Textino w;
    w.show();
    return a.exec();
}
