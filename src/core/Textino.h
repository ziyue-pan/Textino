//*  Filename: Textino.h
//*  Created Date: 2020-06-05 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*     Header files for main class of notepad.
//*     Including declaration of all attributes, variables & functions.
//*     Using qscintilla class as main editor & lexer class

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../config/ConfigManager.h"    // config manager
#include <QMainWindow>                  // main window
#include <Qsci/qscilexer.h>             // qscintilla lexer

// Declaration for ready-to-show elements
class QLabel;           // label
class QStatusBar;       // status bar (bottom of the main window)
class QAction;          // qt gui application action signal
class QMenu;            // application menu
class FindDialog;       // functional class for finding contents
class ReplaceDialog;    // functional class for finding & replacing contents
class QsciScintilla;    // qscintilla class


//@ Class:  Textino
//@ Description:
//          Work as the main windows of GUI application.
//          Including specification of all application elements
//@ Usage:
//          int main() {
//              Textino main_application;
//              main_application.show();
//              return main_application.exec();
//          }           
class Textino : public QMainWindow
{
    Q_OBJECT            // Q_OBJECT attribute

public:
    Textino();          // constructor
    ~Textino();         // deconstructor

protected:
                        // overide closeEvent()
                        // to control file save or not
    void closeEvent(QCloseEvent *event);    
                                             

private slots:
    void NewFile();     // new file
    void Open();        // open current file
    bool Save();        // save file
    bool SaveAs();      // save as another file
    void Find();        // find contents
    void Replace();     // find & replace
    void About();       // about info
    void Modified();    // text had been modified
    void CursorPositionChanged();
    void OnTextChanged();
    void OnTextSelected();
    void OnModificationChanged();
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

    FindDialog *find_dialog;
    ReplaceDialog *replace_dialog;

    QStatusBar *status_bar;
    QLabel *status_label;
    QLabel *status_cursor_label;
    QLabel *status_filepath_label;
    QLabel *status_modification_label;


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
    QAction *find_act;
    QAction *replace_act;
    QAction *settings_act;
};

#endif
