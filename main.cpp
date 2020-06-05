
#include <QApplication>

#include "Textino.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    Textino text_editor;
    text_editor.show();
    return app.exec();
}
