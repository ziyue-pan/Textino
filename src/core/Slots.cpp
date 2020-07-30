//*  Filename: Slots.cpp
//*  Created Date: 2020-06-05 15:34:39
//*  Modified Date: 2020-07-30 00:40:24
//*  Description:
//*     implementation of all slot functions

#include "../dialog/FindDialog.h"
#include "../dialog/ReplaceDialog.h"
#include "Textino.h"

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
#include <QLabel>
#include <QFontDialog>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexersql.h>

// override close event:
//  prompt save query and dicide whether to exit
void Textino::closeEvent(QCloseEvent *event) {
    if (MaybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

// create new file
void Textino::NewFile() {
    if (MaybeSave()) {
        main_editor->clear();
        SetCurrentFile("");
        status_filepath_label->setText("Untitled.txt");
    }
}

// open file
void Textino::Open() {
    if (MaybeSave()) {
        QString file_name = QFileDialog::getOpenFileName(this);
        if (!file_name.isEmpty())
            LoadFile(file_name);    // call LoadFile()
    }
}

// save
bool Textino::Save() {
    if (current_path.isEmpty()) {
        return SaveAs();            // if untitled
                                    // just save as
    } else {
        return SaveFile(current_path);
    }
}

// set modified
void Textino::Modified() {
    setWindowModified(main_editor->isModified());
}

// prompt about info
//TODO: add github link, but fail to display
void Textino::About() {
   QMessageBox::about(this, tr("About Textino"),
            tr("<b>Textino</b> is an extremely light text editor, \
            written by <a herf='https://github.com/PAN-Ziyue/Textino'>Raymond Ziyue</a>"));
}

// save as
bool Textino::SaveAs() {
    QString file_name = QFileDialog::getSaveFileName(this);
    if (file_name.isEmpty())
        return false;
    return SaveFile(file_name);
}

// find dialog
void Textino::Find() {
    find_dialog->show();
}

// replace dialog
void Textino::Replace() {
    replace_dialog->show();
}


void Textino::OnCursorPositionChanged() {
    int col = 0;
    int ln = 0;
    main_editor->getCursorPosition(&ln,&col);
    status_cursor_label->setText("Ln: " + QString::number(ln + 1) + "    Col: " + QString::number(col + 1));
}

void Textino::OnTextChanged() {
    status_label->setText("length: " + QString::number(main_editor->text().length()) + "    lines: " + QString::number(main_editor->lines()));
}

void Textino::OnTextSelected() {
    int col = 0;
    int ln = 0;
    main_editor->getCursorPosition(&ln,&col);
    if (main_editor->selectedText().length() != 0)
        status_cursor_label->setText( " " + QString::number(main_editor->selectedText().length()) + " selected     " + "Ln: " + QString::number(ln + 1) + "    Col: " + QString::number(col + 1) + "  ");
    else 
        status_cursor_label->setText("Ln: " + QString::number(ln + 1) + "    Col: " + QString::number(col + 1));
} 

void Textino::OnModificationChanged() {
    if (main_editor->isModified())
        status_modification_label->setText("modified");
    else
        status_modification_label->setText("");
}

void Textino::SetFont() {
    bool selected = false;
    QFont given_font = QFontDialog::getFont(&selected, config->GetFont(), this, "Select Fonts");

    if(selected) {
        main_editor->setFont(given_font);
        config->ModifyFont(given_font);
    }
}












