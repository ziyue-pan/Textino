/*
 * Created Date: Friday, June 5th 2020, 3:34:39 pm
 * Author: Raymond Rhino
 * 
 * Copyright (c) 2020 Textino
 */
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QSettings>
#include <QSize>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>
#include <QFontDialog>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexersql.h>

#include "Textino.h"


void Textino::closeEvent(QCloseEvent *event) {
    if (MaybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Textino::NewFile() {
    if (MaybeSave()) {
        main_editor->clear();
        SetCurrentFile("");
    }
}

void Textino::Open() {
    if (MaybeSave()) {
        QString file_name = QFileDialog::getOpenFileName(this);
        if (!file_name.isEmpty())
            LoadFile(file_name);
    }
}

bool Textino::Save() {
    if (current_path.isEmpty()) {
        return SaveAs();
    } else {
        return SaveFile(current_path);
    }
}


void Textino::Modified() {
    setWindowModified(main_editor->isModified());
}

void Textino::About() {
   QMessageBox::about(this, tr("About Textino"),
            tr("<b>Textino</b> is an extremely light text editor, \
            written by <a herf='https://github.com/PAN-Ziyue/Textino'>Raymond Ziyue</a>"));
}

bool Textino::SaveAs() {
    QString file_name = QFileDialog::getSaveFileName(this);
    if (file_name.isEmpty())
        return false;

    return SaveFile(file_name);
}

void Textino::SetFont() {
    bool selected = false;
    QFont given_font = QFontDialog::getFont(&selected, config->GetFont(), this, "Select Fonts");

    if(selected) {
        main_editor->setFont(given_font);
        config->ModifyFont(given_font);
    }
}












