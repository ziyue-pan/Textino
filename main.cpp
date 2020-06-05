/*
 * Created Date: Friday, June 5th 2020, 3:34:39 pm
 * Author: Raymond Rhino
 * 
 * Copyright (c) 2020 Textino
 */
#include <QApplication>

#include "Textino.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    Textino text_editor;
    text_editor.show();
    return app.exec();
}
