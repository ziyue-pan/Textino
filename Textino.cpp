#include "Textino.h"
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>


Textino::Textino(QWidget *parent)
    : QMainWindow(parent)
{
    file_path = "";
    changed = false;


    CreateMenuBar();
    CreateStatusBar();
    CreateMainEditor();

    setWindowTitle("New document - Textino");
    setWindowIcon(QIcon(":img/imgs/icon.png"));
    setAcceptDrops(true);

    QFont font;
    font.setFamily("Consolas");
    font.setPixelSize(18);
    main_editor.setFont(font);
    resize(800, 600);
}

Textino::~Textino()
{
}


void Textino::CreateMenuBar(){
    QMenuBar* menu_bar = menuBar();
    QMenu* menu_file = new QMenu("File", menu_bar);
    QMenu* menu_edit = new QMenu("Edit", menu_bar);
    QAction* action = nullptr;

    CreateAction(action, menu_file, "New", Qt::CTRL+Qt::Key_N, ":img/imgs/new.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionNew()));
    menu_file->addAction(action);
    CreateAction(action, menu_file, "Open", Qt::CTRL+Qt::Key_O, ":img/imgs/open.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionOpen()));
    menu_file->addAction(action);
    CreateAction(action, menu_file, "Save", Qt::CTRL+Qt::Key_S, ":img/imgs/save.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionSave()));
    menu_file->addAction(action);
    CreateAction(action, menu_file, "Save As", Qt::CTRL+Qt::SHIFT+Qt::Key_S, ":img/imgs/save-as.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionSaveAs()));
    menu_file->addAction(action);
    menu_file->addSeparator();
    CreateAction(action, menu_file, "Exit", Qt::CTRL+Qt::Key_W, ":img/imgs/exit.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionExit()));
    menu_file->addAction(action);
    
    CreateAction(action, menu_edit, "Copy", Qt::CTRL+Qt::Key_C, ":img/imgs/copy.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionCopy()));
    menu_edit->addAction(action);
    CreateAction(action, menu_edit, "Cut", Qt::CTRL+Qt::Key_X, ":img/imgs/cut.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionCut()));
    menu_edit->addAction(action);
    CreateAction(action, menu_edit, "Paste", Qt::CTRL+Qt::Key_V, ":img/imgs/paste.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionPaste()));
    menu_edit->addAction(action);
    CreateAction(action, menu_edit, "Undo", Qt::CTRL+Qt::Key_Z, ":img/imgs/undo.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionUndo()));
    menu_edit->addAction(action);
    CreateAction(action, menu_edit, "Redo", Qt::CTRL+Qt::SHIFT+Qt::Key_Z, ":img/imgs/redo.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ActionRedo()));
    menu_edit->addAction(action);

    menu_bar->addMenu(menu_file);
    menu_bar->addMenu(menu_edit);
}

void Textino::CreateStatusBar(){
    QStatusBar* status_bar = statusBar();
    
    status_label.setMinimumWidth(150);
    status_label.setAlignment(Qt::AlignCenter);
    status_label.setText("length: " + QString::number(0) + "    lines: " + QString::number(1));
    status_bar->addPermanentWidget(&status_label);
}

void Textino::CreateMainEditor(){
    QPalette palette = main_editor.palette();
    main_editor.setPalette(palette);
    main_editor.setParent(this);
    main_editor.setAcceptDrops(false);
    setCentralWidget(&main_editor);
    connect(&main_editor, SIGNAL(textChanged()), this, SLOT(ActionChanged()));
    connect(&main_editor, SIGNAL(cursorPositionChanged()), this, SLOT(ActionCursor()));
    connect(&main_editor, SIGNAL(cursorPositionChanged()), this, SLOT(ActionHighlight()));
    ActionHighlight();
}



void Textino::CreateAction(QAction*& action, QWidget* parent, QString instance, int short_cut, QString icon_path){
    action = new QAction(instance, parent);
    action->setShortcut(QKeySequence(short_cut));
    action->setIcon(QIcon(icon_path));
}

QString Textino::SaveFile(QString path, QString title){
    QString save_path = path;
    if(path=="")
        save_path=ShowDialog(QFileDialog::AcceptSave, title, ":/img/imgs/icon.png");
    if(save_path != ""){
        QFile file(save_path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream file_out(&file);
            file_out << main_editor.toPlainText();
            file.close();
            setWindowTitle(save_path + " - Textino");
            changed = false;
        } else
            ShowMessage(true, QString("Fail to save text!\n") + "\"" + save_path + "\"");
    }
    return save_path;
}

void Textino::OpenFile(QString open_path){
    QFile file(open_path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream instream(&file);
        main_editor.setPlainText(instream.readAll());
        file.close();
        file_path = open_path;
        changed = false;
        setWindowTitle(file_path+" - Textino");
    }else
        ShowMessage(true, QString("Fail to open file"));
}


QString Textino::ShowDialog(QFileDialog::AcceptMode mode, QString title, QString icon_path){
    QFileDialog dialog(this);
    QStringList filters;
    QMap<QString, QString> map;
    const char* filter_array[][2] = {
        {"文本文档(*.txt)", ".txt"},
        {"所有文件(*.*)"  , ".*"   },
        {nullptr         , nullptr}
    };
    QString text = "";

    for(int i=0; filter_array[i][0]!=nullptr; i++) {
        filters.append(filter_array[i][0]);
        map.insert(filter_array[i][0], filter_array[i][1]);
    }
    dialog.setWindowTitle(title);
    dialog.setWindowIcon(QIcon(icon_path));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilters(filters);

    if( mode == QFileDialog::AcceptOpen )
        dialog.setFileMode(QFileDialog::ExistingFile);

    if( dialog.exec() == QFileDialog::Accepted ) {
        text = dialog.selectedFiles()[0];

        if( mode == QFileDialog::AcceptSave ) {
            QString postfix = map[dialog.selectedNameFilter()];
            if((postfix != ".*") && !text.endsWith(postfix))
                text = text + postfix;
        }
    }
    return text;
}

int Textino::ShowMessage(bool error, QString text){
    QMessageBox message(this);
    message.setWindowTitle("Textino");
    message.setWindowFlag(Qt::Drawer);
    message.setText(text);
    if(error){
        message.setIcon(QMessageBox::Critical);
        message.setStandardButtons(QMessageBox::Ok);
    }
    else {
        message.setIcon(QMessageBox::Question);
        message.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    }
    return message.exec();
}

void Textino::SavePrevious(){
    QString this_file = file_path;
    int chioce = ShowMessage(false, QString("Want to save this file?"));
    if(chioce==QMessageBox::Yes)
        SaveFile(file_path, "Save");
    else if(chioce==QMessageBox::No){
        changed = false;
    }
}

void Textino::closeEvent(QCloseEvent* event){
    if(changed)
        SavePrevious();

    if(!changed)
        event->accept();
    else
        event->ignore();
}

