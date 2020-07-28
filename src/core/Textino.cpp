//*  Filename: Textino.cpp
//*  Created Date: 2020-06-05 15:34:39
//*  Modified Date: 2020-07-28 10:57:26
//*  Description:
//*     Main function module of the whole notepad
//*     
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

#include "../dialog/FindDialog.h"
#include "../dialog/ReplaceDialog.h"
#include "Textino.h"

Textino::Textino()
{
    config = new ConfigManager();

    CreateMainEditor();

    find_dialog = new FindDialog(this, main_editor);
    replace_dialog = new ReplaceDialog(this, main_editor);

    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreateStatusBar();

    QApplication::setFont(config->GetDefaultFont());
}

Textino::~Textino() {

}


void Textino::CreateMainEditor() {
    main_editor = new QsciScintilla();

    setCentralWidget(main_editor);  // qscintilla editor as the central part

    connect(main_editor, SIGNAL(textChanged()), this, SLOT(Modified()));    // modified slot

    main_editor->setMarginType(0, QsciScintilla::NumberMargin);             // left margin content
    main_editor->setMarginsFont(config->GetDefaultFont());
    main_editor->setMarginWidth(0, 45);                                     // left margin width
    main_editor->setTabWidth(4);
    main_editor->setTabIndents(true);


    main_editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);
    main_editor->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);
    main_editor->setCaretLineVisible(true);                 // line number visible
    QColor line_color = QColor(Qt::green).lighter(195);     // line highlighting color
    main_editor->setCaretLineBackgroundColor(line_color);
    main_editor->setWrapMode(QsciScintilla::WrapWord);      // set content wrap

    setWindowIcon(QIcon(":/imgs/icon.png"));                // main icon
    resize(1280, 720);                                      // main size

    main_editor->setFont(config->GetFont());
    SetCurrentFile("");
}

void Textino::CreateActions()
{
    new_act = new QAction(QIcon(":/imgs/new.png"), tr("&New"), this);
    new_act->setShortcut(tr("Ctrl+N"));
    connect(new_act, SIGNAL(triggered()), this, SLOT(NewFile()));

    open_act = new QAction(QIcon(":/imgs/open.png"), tr("&Open..."), this);
    open_act->setShortcut(tr("Ctrl+O"));
    connect(open_act, SIGNAL(triggered()), this, SLOT(Open()));

    save_act = new QAction(QIcon(":/imgs/save.png"), tr("&Save"), this);
    save_act->setShortcut(tr("Ctrl+S"));
    connect(save_act, SIGNAL(triggered()), this, SLOT(Save()));

    save_as_act = new QAction(QIcon(":/imgs/save-as.png"), tr("Save &As..."), this);
    save_as_act->setShortcut(tr("Ctrl+Shift+S"));
    connect(save_as_act, SIGNAL(triggered()), this, SLOT(SaveAs()));

    exit_act = new QAction(QIcon(":/imgs/exit.png"), tr("E&xit"), this);
    exit_act->setShortcut(tr("Ctrl+W"));
    connect(exit_act, SIGNAL(triggered()), this, SLOT(close()));

    cut_act = new QAction(QIcon(":/imgs/cut.png"), tr("Cu&t"), this);
    cut_act->setShortcut(tr("Ctrl+X"));
    connect(cut_act, SIGNAL(triggered()), main_editor, SLOT(cut()));

    copy_act = new QAction(QIcon(":/imgs/copy.png"), tr("&Copy"), this);
    copy_act->setShortcut(tr("Ctrl+C"));
    connect(copy_act, SIGNAL(triggered()), main_editor, SLOT(copy()));

    paste_act = new QAction(QIcon(":/imgs/paste.png"), tr("&Paste"), this);
    paste_act->setShortcut(tr("Ctrl+V"));
    connect(paste_act, SIGNAL(triggered()), main_editor, SLOT(paste()));

    undo_act = new QAction(QIcon(":/imgs/undo.png"), tr("&Undo"), this);
    undo_act->setShortcut(tr("Ctrl+Z"));
    connect(undo_act, SIGNAL(triggered()), main_editor, SLOT(undo()));

    redo_act = new QAction(QIcon(":/imgs/redo.png"), tr("&Rndo"), this);
    redo_act->setShortcut(tr("Ctrl+Shift+Z"));
    connect(redo_act, SIGNAL(triggered()), main_editor, SLOT(redo()));

    find_act = new QAction(QIcon(":/imgs/find.png"), tr("&Find"), this);
    find_act->setShortcut(tr("Ctrl+F"));
    connect(find_act, SIGNAL(triggered()), this, SLOT(Find()));

    replace_act = new QAction(QIcon(":/imgs/replace.png"), tr("&Replace"), this);
    replace_act->setShortcut(tr("Ctrl+R"));
    connect(replace_act, SIGNAL(triggered()), this, SLOT(Replace()));

    about_act = new QAction(QIcon(":/imgs/about.png"), tr("&About"), this);
    connect(about_act, SIGNAL(triggered()), this, SLOT(About()));

    settings_act = new QAction(QIcon(":/imgs/settings.png"), tr("&Settings"), this);
    settings_act->setShortcut(tr("Ctrl+Shift+P"));
    connect(settings_act, SIGNAL(triggered()), this, SLOT(SetFont()));

    cut_act->setEnabled(false);
    copy_act->setEnabled(false);
    connect(main_editor, SIGNAL(copyAvailable(bool)),
            cut_act, SLOT(setEnabled(bool)));
    connect(main_editor, SIGNAL(copyAvailable(bool)),
            copy_act, SLOT(setEnabled(bool)));
}

void Textino::CreateMenus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(new_act);
    file_menu->addAction(open_act);
    file_menu->addAction(save_act);
    file_menu->addAction(save_as_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);

    edit_menu = menuBar()->addMenu(tr("&Edit"));
    edit_menu->addAction(cut_act);
    edit_menu->addAction(copy_act);
    edit_menu->addAction(paste_act);
    edit_menu->addAction(undo_act);
    edit_menu->addAction(redo_act);
    edit_menu->addAction(find_act);
    edit_menu->addAction(replace_act);
    edit_menu->addSeparator();
    edit_menu->addAction(settings_act);

    menuBar()->addSeparator();

    help_menu = menuBar()->addMenu(tr("&Help"));
    help_menu->addAction(about_act);

}

void Textino::CreateToolBars()
{
    file_tool_bar = addToolBar(tr("File"));
    file_tool_bar->addAction(new_act);
    file_tool_bar->addAction(open_act);
    file_tool_bar->addAction(save_act);
    file_tool_bar->addAction(save_as_act);

    edit_tool_bar = addToolBar(tr("Edit"));
    edit_tool_bar->addAction(cut_act);
    edit_tool_bar->addAction(copy_act);
    edit_tool_bar->addAction(paste_act);
    edit_tool_bar->addAction(undo_act);
    edit_tool_bar->addAction(redo_act);
    edit_tool_bar->addAction(find_act);
    edit_tool_bar->addAction(replace_act);
    edit_tool_bar->addAction(settings_act);

    help_tool_bar = addToolBar(tr("Help"));
    help_tool_bar->addAction(about_act);
}

void Textino::CreateStatusBar()
{
    status_bar = statusBar();
    status_bar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

    status_label = new QLabel("Ready");
    status_cursor_label = new QLabel("Ready");
    status_modification_label = new QLabel("Ready");
    status_filepath_label = new QLabel("Untitled.txt");

    status_bar->addWidget(status_filepath_label);

    status_modification_label->setAlignment(Qt::AlignCenter);
    OnModificationChanged();
    status_bar->addPermanentWidget(status_modification_label);

    status_cursor_label->setMinimumWidth(150);
    status_cursor_label->setAlignment(Qt::AlignCenter);
    OnCursorPositionChanged();
    status_bar->addPermanentWidget(status_cursor_label);

    status_bar->addPermanentWidget(new QLabel());
    status_label->setMinimumWidth(150);
    status_label->setAlignment(Qt::AlignCenter);
    OnTextChanged();
    status_bar->addPermanentWidget(status_label);

    connect(main_editor, SIGNAL(copyAvailable(bool)), this, SLOT(OnTextSelected()));
    connect(main_editor, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));
    connect(main_editor, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(OnCursorPositionChanged()));
    connect(main_editor, SIGNAL(modificationChanged(bool)), this, SLOT(OnModificationChanged()));
}

bool Textino::MaybeSave()
{
    if (main_editor->isModified()) {
        int ret = QMessageBox::warning(this, tr("Textino"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return Save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void Textino::LoadFile(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Textino"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_name)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    main_editor->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    SetCurrentFile(file_name);
}

bool Textino::SaveFile(const QString &given_path)
{
    QFile file(given_path);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Textino"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(given_path)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << main_editor->text();
    QApplication::restoreOverrideCursor();

    SetCurrentFile(given_path);
    return true;
}

void Textino::SetCurrentFile(const QString &given_path)
{
    current_path = given_path;
    main_editor->setModified(false);
    setWindowModified(false);

    QString shown_name;
    if (current_path.isEmpty())
        shown_name = "Untitled.txt";
    else {
        shown_name = GetFileName(current_path);
        status_filepath_label->setText(current_path);
    }
    CreateLexer();
    setWindowTitle(tr("%1[*] - %2").arg(shown_name).arg(tr("Textino")));
}

QString Textino::GetFileName(const QString &current_path) {
    return QFileInfo(current_path).fileName();
}

void Textino::CreateLexer(){
    QString ext = QFileInfo(current_path).suffix();

    if(ext == "c" || ext == "cpp" || ext == "cc" || ext == "h" || ext=="hpp" || ext =="hh"){
        text_lexer = new QsciLexerCPP;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerCPP::CommentLine);
    }
    else if(ext == "java") {
        text_lexer = new QsciLexerJava;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerJava::CommentLine);
    }
    else if(ext =="py") {
        text_lexer = new QsciLexerPython;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerPython::Comment);
    }
    else if(ext =="js" || ext =="ts") {
        text_lexer = new QsciLexerJavaScript;
        text_lexer->setColor(QColor(Qt:: gray),QsciLexerJavaScript::CommentLine);
    }
    else if(ext =="v" || ext =="vhdl") {
        text_lexer = new QsciLexerVerilog;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerVerilog::CommentLine);
    }
    else if(ext =="sql") {
        text_lexer = new QsciLexerSQL;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerSQL::CommentLine);
    }
    else if(ext == "html" || ext == "htm") {
        text_lexer = new QsciLexerHTML;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerHTML::HTMLComment);
    }
    else if(ext == "xml") {
        text_lexer = new QsciLexerXML;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerXML::HTMLComment);
    }
    else if(ext == "cs"){
        text_lexer = new QsciLexerCSharp;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerCSharp::CommentLine);
    }
    else if(ext == "md") {
        text_lexer = new QsciLexerMarkdown;
    }
    else if(ext == "sh") {
        text_lexer = new QsciLexerBash;
        text_lexer->setColor(QColor(Qt:: gray), QsciLexerBash::Comment);
    }
    else {
        text_lexer = nullptr;
    }

    if(text_lexer) {
        text_lexer->setFont(config->GetFont());
        main_editor->setAutoIndent(true);
        main_editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    }
    else {
        main_editor->setAutoIndent(false);
        main_editor->setBraceMatching(QsciScintilla::NoBraceMatch);
    }

    main_editor->setLexer(text_lexer);
    main_editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    main_editor->setAutoCompletionCaseSensitivity(true);
    main_editor->setAutoCompletionThreshold(1);
}
