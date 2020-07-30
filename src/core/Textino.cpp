//*  Filename: Textino.cpp
//*  Created Date: 2020-06-05 15:34:39
//*  Modified Date: 2020-07-28 10:57:26
//*  Description:
//*     Main function module of the whole notepad.
//*     The implementation of the main class

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

// qscintilla header files
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexerhtml.h>
#include <QSci/qscilexercsharp.h>
#include <Qsci/qscilexermarkdown.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerxml.h>


// constructor
Textino::Textino() {
    config = new ConfigManager();   // initalize config manager

    CreateMainEditor();             // create main editor 

    // initialize find functional dialogs
    find_dialog = new FindDialog(this, main_editor);      
    // initialize replace functional dialog  
    replace_dialog = new ReplaceDialog(this, main_editor);

    CreateActions();                // create actions
    CreateMenus();                  // create menus
    CreateToolBars();               // create tool bars
    CreateStatusBar();              // create status bars

    // set application font
    QApplication::setFont(config->GetDefaultFont());
}

// deconstructor: null implementation
Textino::~Textino() {}

// create main editor
void Textino::CreateMainEditor() {
    main_editor = new QsciScintilla();  // qscintilla as the main editor
    setCentralWidget(main_editor);      // qscintilla editor as the central part

    // connect content-changed signal to SLOT function
    connect(main_editor, SIGNAL(textChanged()), this, SLOT(Modified()));    

    main_editor->setMarginType(0, QsciScintilla::NumberMargin); // left margin content
    main_editor->setMarginsFont(config->GetDefaultFont());      // editor margin font
    main_editor->setMarginWidth(0, 45);                         // left margin width
    main_editor->setTabWidth(4);                                // set tab policy to 4 spaces
    main_editor->setTabIndents(true);                           // set tab button for indents

    // set UTF-8 as qscintilla encoding policy
    main_editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);
    // set qscintilla auto indentation policy
    main_editor->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);
    main_editor->setCaretLineVisible(true);                 // line number visible
    QColor line_color = QColor(Qt::green).lighter(195);     // line highlighting color
    main_editor->setCaretLineBackgroundColor(line_color);   // main editor set background color
    main_editor->setWrapMode(QsciScintilla::WrapWord);      // set content wrap

    setWindowIcon(QIcon(":/imgs/icon.png"));                // main icon
    resize(1280, 720);                                      // main size

    main_editor->setFont(config->GetFont());                // main editor font
    SetCurrentFile("");                                     // untitled text
}

// create actions:
//  1. set corresponding labels and icons
//  2. set shortcut
//  3. connect slot signals
void Textino::CreateActions() {
    
    // new file
    new_act = new QAction(QIcon(":/imgs/new.png"), tr("&New"), this);
    new_act->setShortcut(tr("Ctrl+N"));
    connect(new_act, SIGNAL(triggered()), this, SLOT(NewFile()));

    // open file
    open_act = new QAction(QIcon(":/imgs/open.png"), tr("&Open..."), this);
    open_act->setShortcut(tr("Ctrl+O"));
    connect(open_act, SIGNAL(triggered()), this, SLOT(Open()));

    // save file
    save_act = new QAction(QIcon(":/imgs/save.png"), tr("&Save"), this);
    save_act->setShortcut(tr("Ctrl+S"));
    connect(save_act, SIGNAL(triggered()), this, SLOT(Save()));

    // save file as ...
    save_as_act = new QAction(QIcon(":/imgs/save-as.png"), tr("Save &As..."), this);
    save_as_act->setShortcut(tr("Ctrl+Shift+S"));
    connect(save_as_act, SIGNAL(triggered()), this, SLOT(SaveAs()));

    // exit
    exit_act = new QAction(QIcon(":/imgs/exit.png"), tr("E&xit"), this);
    exit_act->setShortcut(tr("Ctrl+W"));
    connect(exit_act, SIGNAL(triggered()), this, SLOT(close()));

    //cut
    cut_act = new QAction(QIcon(":/imgs/cut.png"), tr("Cu&t"), this);
    cut_act->setShortcut(tr("Ctrl+X"));
    connect(cut_act, SIGNAL(triggered()), main_editor, SLOT(cut()));

    // copy
    copy_act = new QAction(QIcon(":/imgs/copy.png"), tr("&Copy"), this);
    copy_act->setShortcut(tr("Ctrl+C"));
    connect(copy_act, SIGNAL(triggered()), main_editor, SLOT(copy()));

    // paste
    paste_act = new QAction(QIcon(":/imgs/paste.png"), tr("&Paste"), this);
    paste_act->setShortcut(tr("Ctrl+V"));
    connect(paste_act, SIGNAL(triggered()), main_editor, SLOT(paste()));

    // undo
    undo_act = new QAction(QIcon(":/imgs/undo.png"), tr("&Undo"), this);
    undo_act->setShortcut(tr("Ctrl+Z"));
    connect(undo_act, SIGNAL(triggered()), main_editor, SLOT(undo()));

    // redo
    redo_act = new QAction(QIcon(":/imgs/redo.png"), tr("&Rndo"), this);
    redo_act->setShortcut(tr("Ctrl+Shift+Z"));
    connect(redo_act, SIGNAL(triggered()), main_editor, SLOT(redo()));

    // find
    find_act = new QAction(QIcon(":/imgs/find.png"), tr("&Find"), this);
    find_act->setShortcut(tr("Ctrl+F"));
    connect(find_act, SIGNAL(triggered()), this, SLOT(Find()));

    // replace
    replace_act = new QAction(QIcon(":/imgs/replace.png"), tr("&Replace"), this);
    replace_act->setShortcut(tr("Ctrl+R"));
    connect(replace_act, SIGNAL(triggered()), this, SLOT(Replace()));

    // about
    about_act = new QAction(QIcon(":/imgs/about.png"), tr("&About"), this);
    connect(about_act, SIGNAL(triggered()), this, SLOT(About()));

    // settings
    settings_act = new QAction(QIcon(":/imgs/settings.png"), tr("&Settings"), this);
    settings_act->setShortcut(tr("Ctrl+Shift+P"));
    connect(settings_act, SIGNAL(triggered()), this, SLOT(SetFont()));

    // cut action: initialize
    cut_act->setEnabled(false);
    copy_act->setEnabled(false);

    // connect to enable function
    connect(main_editor, SIGNAL(copyAvailable(bool)), cut_act, SLOT(setEnabled(bool)));
    connect(main_editor, SIGNAL(copyAvailable(bool)), copy_act, SLOT(setEnabled(bool)));
}


// create menus bar
void Textino::CreateMenus() {

    // first create the file menu item
    // then create the submenus
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(new_act);      // new file
    file_menu->addAction(open_act);     // open file
    file_menu->addAction(save_act);     // save
    file_menu->addAction(save_as_act);  // save as
    file_menu->addSeparator();          // a separator: ---
    file_menu->addAction(exit_act);     // exit

    // create edit sub menus
    edit_menu = menuBar()->addMenu(tr("&Edit"));
    edit_menu->addAction(cut_act);      // cut
    edit_menu->addAction(copy_act);     // copy
    edit_menu->addAction(paste_act);    // paste
    edit_menu->addAction(undo_act);     // undo
    edit_menu->addAction(redo_act);     // redos
    edit_menu->addAction(find_act);     // find
    edit_menu->addAction(replace_act);  // find & replace
    edit_menu->addSeparator();          
    edit_menu->addAction(settings_act); // settings

    // create help menus
    help_menu = menuBar()->addMenu(tr("&Help"));
    help_menu->addAction(about_act);    // about

}

// create tool bars
// quite similar to the menu items
// including 3 distributed menus and submenu items
void Textino::CreateToolBars() {

    // file tool bar
    file_tool_bar = addToolBar(tr("File"));
    file_tool_bar->addAction(new_act);
    file_tool_bar->addAction(open_act);
    file_tool_bar->addAction(save_act);
    file_tool_bar->addAction(save_as_act);

    // edit tool bar
    edit_tool_bar = addToolBar(tr("Edit"));
    edit_tool_bar->addAction(cut_act);
    edit_tool_bar->addAction(copy_act);
    edit_tool_bar->addAction(paste_act);
    edit_tool_bar->addAction(undo_act);
    edit_tool_bar->addAction(redo_act);
    edit_tool_bar->addAction(find_act);
    edit_tool_bar->addAction(replace_act);
    edit_tool_bar->addAction(settings_act);

    // help tool bar
    help_tool_bar = addToolBar(tr("Help"));
    help_tool_bar->addAction(about_act);
}

// create the status bar
// including the following functions:
//  1. display the full path in the left down corner
//  2. display current position of the cursor
//  3. display line and word count
void Textino::CreateStatusBar() {
    // initialize status bar
    status_bar = statusBar();
    // set status bar style
    status_bar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    
    // initialize status labels
    status_label = new QLabel("Ready");
    status_cursor_label = new QLabel("Ready");
    status_modification_label = new QLabel("Ready");
    status_filepath_label = new QLabel("Untitled.txt");

    // status bar set file path label
    // to display full file path in the left right corner
    status_bar->addWidget(status_filepath_label);

    // set status modification alignment
    status_modification_label->setAlignment(Qt::AlignCenter);
    ModificationChanged();
    // add modification label
    status_bar->addPermanentWidget(status_modification_label);

    // set cursor label style sheet
    // minimum width: 150 px
    // alignment: center
    status_cursor_label->setMinimumWidth(150);
    status_cursor_label->setAlignment(Qt::AlignCenter);
    CursorPositionChanged();
    status_bar->addPermanentWidget(status_cursor_label);

    // add status bar center widget
    status_bar->addPermanentWidget(new QLabel());
    status_label->setMinimumWidth(150);
    status_label->setAlignment(Qt::AlignCenter);
    TextChanged();
    status_bar->addPermanentWidget(status_label);

    // connect signals to slot function
    connect(main_editor, SIGNAL(copyAvailable(bool)), this, SLOT(TextSelected()));
    connect(main_editor, SIGNAL(textChanged()), this, SLOT(TextChanged()));
    connect(main_editor, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(CursorPositionChanged()));
    connect(main_editor, SIGNAL(modificationChanged(bool)), this, SLOT(ModificationChanged()));
}

// current content changed
// maybe save current text
bool Textino::MaybeSave() {
    
    // if modified
    // prompt messages
    if (main_editor->isModified()) {
        // warning
        int ret = QMessageBox::warning(this, tr("Textino"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);

        // check result
        if (ret == QMessageBox::Yes)
            return Save();
        // directly quit
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

// load file
void Textino::LoadFile(const QString &file_name) {
    // set qfile
    QFile file(file_name);
    
    // check if read-only
    if (!file.open(QFile::ReadOnly)) {
        // prompt warning message
        QMessageBox::warning(this, tr("Textino"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_name)
                             .arg(file.errorString()));
        return;
    }

    // create text stream
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // display text
    main_editor->setText(in.readAll());
    QApplication::restoreOverrideCursor();  // override cursor

    SetCurrentFile(file_name);              // set current file
}

// save file
bool Textino::SaveFile(const QString &given_path) {
    QFile file(given_path);
    // check if write only
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Textino"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(given_path)
                             .arg(file.errorString()));
        return false;
    }

    // create outstream
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // pass text from outstream to file
    out << main_editor->text();
    QApplication::restoreOverrideCursor();

    // set current file
    SetCurrentFile(given_path);
    return true;
}

// set current file info
void Textino::SetCurrentFile(const QString &given_path) {
    // successfully save the file
    current_path = given_path;
    main_editor->setModified(false);
    setWindowModified(false);

    // set current shown name in application
    QString shown_name;
    if (current_path.isEmpty())
        shown_name = "Untitled.txt";
    else {
        shown_name = GetFileName(current_path);
        status_filepath_label->setText(current_path);
    }
    // create lexer according to current file
    CreateLexer();
    
    // set current file name
    setWindowTitle(tr("%1[*] - %2").arg(shown_name).arg(tr("Textino")));
}

// get name
QString Textino::GetFileName(const QString &current_path) {
    return QFileInfo(current_path).fileName();
}

// create qscintilla lexer
void Textino::CreateLexer() {
    // get current file suffix
    QString ext = QFileInfo(current_path).suffix();

    // c/c++
    if(ext == "c" || ext == "cpp" || ext == "cc" || ext == "h" || ext=="hpp" || ext =="hh"){
        text_lexer = new QsciLexerCPP;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerCPP::CommentLine);
    }
    // java
    else if(ext == "java") {
        text_lexer = new QsciLexerJava;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerJava::CommentLine);
    }
    // python
    else if(ext =="py") {
        text_lexer = new QsciLexerPython;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerPython::Comment);
    }
    // javascript/typescript
    else if(ext =="js" || ext =="ts") {
        text_lexer = new QsciLexerJavaScript;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerJavaScript::CommentLine);
    }
    // verilog
    else if(ext =="v" || ext =="vhdl") {
        text_lexer = new QsciLexerVerilog;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerVerilog::CommentLine);
    }
    // sql
    else if(ext =="sql") {
        text_lexer = new QsciLexerSQL;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerSQL::CommentLine);
    }
    // html
    else if(ext == "html" || ext == "htm") {
        text_lexer = new QsciLexerHTML;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerHTML::HTMLComment);
    }
    // xml
    else if(ext == "xml") {
        text_lexer = new QsciLexerXML;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerXML::HTMLComment);
    }
    // c#
    else if(ext == "cs"){
        text_lexer = new QsciLexerCSharp;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerCSharp::CommentLine);
    }
    // markdown
    else if(ext == "md") {
        text_lexer = new QsciLexerMarkdown;
    }
    // shellscript
    else if(ext == "sh") {
        text_lexer = new QsciLexerBash;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerBash::Comment);
    }
    // plain text
    else {
        text_lexer = nullptr;
    }

    // create indent policy and brace matching
    // acording to the current lexer
    if(text_lexer) {
        text_lexer->setFont(config->GetFont());
        main_editor->setAutoIndent(true);
        main_editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    }
    else {
        main_editor->setAutoIndent(false);
        main_editor->setBraceMatching(QsciScintilla::NoBraceMatch);
    }

    // load current text lexer
    main_editor->setLexer(text_lexer);
    // use built-in auto completion souce
    main_editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    // auto completion case sensitivity
    main_editor->setAutoCompletionCaseSensitivity(true);

    // after 1 letter is typed in
    // then diplay the auto completion selection panel
    main_editor->setAutoCompletionThreshold(1);
}
