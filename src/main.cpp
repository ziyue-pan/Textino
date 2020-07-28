//*  Filename: main.cpp
//*  Created Date: 2020-06-05 15:34:39
//*  Modified Date: 2020-07-28 11:01:01
//*  Description:
//*     Work as the driver module of qt application.
//*     Initialize the main class as the QApplication.
//*     Then execute the application.

#include "core/Textino.h"   // core header files
#include <QApplication> 

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(application);   // initialize qt resources

    QApplication app(argc, argv);   // pass parameters to the main class
    Textino text_editor;            // initialize the main class
    text_editor.show();             // show and execute
    return app.exec();
}
