/*
 * Created Date: Friday, June 5th 2020, 3:34:39 pm
 * Author: Raymond Rhino
 * 
 * Copyright (c) 2020 Textino
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../config/ConfigManager.h"

#include <QMainWindow>
#include <Qsci/qscilexer.h>

class QAction;      
class QMenu;
class QsciScintilla;    // qscintilla class

class Textino : public QMainWindow
{
    Q_OBJECT

public:
    Textino();
    ~Textino();

protected:
    void closeEvent(QCloseEvent *event);    // overide closeEvent

private slots:
    void NewFile();     // new file
    void Open();        // open current file
    bool Save();        // save file
    bool SaveAs();      // save as another file
    void About();       // about info
    void Modified();    // text had been modified
    void SetFont();     // change font & size

private:
    void CreateMainEditor();    // create main editor
    void CreateActions();       // create actions
    void CreateMenus();         // create menus
    void CreateToolBars();      // create tool bar
    void CreateStatusBar();     // create status bar
    void CreateLexer();         // create lexer
    bool MaybeSave();           // modified but unsaved
    void LoadFile(const QString &file_name);        // load file
    bool SaveFile(const QString &file_name);        // save file
    void SetCurrentFile(const QString &file_name);  // set file path
    QString GetFileName(const QString &file_name);  // get the file name

    QsciScintilla *main_editor; // main editor
    QString current_file;       // current file name
    QString current_path;       // current file path
    QsciLexer *text_lexer;      // current language lexer
    ConfigManager *config;

    QMenu *file_menu;   // file menus
    QMenu *edit_menu;   // edit menus
    QMenu *help_menu;   // help menus

    QToolBar *file_tool_bar;    // tool bars
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
    QAction *settings_act;
};

#endif
