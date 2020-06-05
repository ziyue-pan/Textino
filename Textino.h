/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qsci/qscilexer.h>
#include <Qsci/qsciapis.h>

class QAction;
class QMenu;
class QsciScintilla;

class Textino : public QMainWindow
{
    Q_OBJECT

public:
    Textino();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void NewFile();
    void Open();
    bool Save();
    bool SaveAs();
    void About();
    void Modified();

private:
    void CreateActions();
    void CreateMenus();
    void CreateToolBars();
    void CreateStatusBar();
    void CreateLexer();
    bool MaybeSave();
    void LoadFile(const QString &file_name);
    bool SaveFile(const QString &file_name);
    void SetCurrentFile(const QString &file_name);
    QString GetFileName(const QString &file_name);

    QsciScintilla *main_editor;
    QString current_file;
    QsciLexer *text_lexer;

    QMenu *file_menu;
    QMenu *edit_menu;
    QMenu *help_menu;
    QToolBar *file_tool_bar;
    QToolBar *edit_tool_bar;
    QToolBar *help_tool_bar;
    QAction *new_act;
    QAction *open_act;
    QAction *save_act;
    QAction *save_as_act;
    QAction *exit_act;
    QAction *cut_act;
    QAction *copy_act;
    QAction *paste_act;
    QAction *about_act;
    QAction *redo_act;
    QAction *undo_act;
};

#endif
