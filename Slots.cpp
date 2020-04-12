#include "Textino.h"
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>

void Textino::ActionCopy(){main_editor.copy();}
void Textino::ActionCut(){main_editor.cut();}
void Textino::ActionPaste(){main_editor.paste();}
void Textino::ActionUndo(){main_editor.undo();}
void Textino::ActionRedo(){main_editor.redo();}
void Textino::ActionCursor(){

}
void Textino::ActionChanged(){
    if(!changed)
        setWindowTitle("* "+windowTitle());
    changed = true;
    status_label.setText("length: " + QString::number(main_editor.toPlainText().length()) + "    lines: " + QString::number(main_editor.document()->lineCount()));
}

void Textino::ActionNew(){
    if(changed)
        SavePrevious();

    if(!changed){
        main_editor.clear();
        changed = false;
        file_path = nullptr;
        setWindowTitle("New document - Textino");
    }
}

void Textino::ActionOpen(){
    if(changed)
        SavePrevious();
    if(!changed){
        QString open_path = ShowDialog(QFileDialog::AcceptOpen, "Open", ":img/imgs/icon.png");
        OpenFile(open_path);
    }
}

void Textino::ActionSave(){
    QString save_path = SaveFile(file_path, "Save");
    if(save_path!="")
        file_path = save_path;
}
void Textino::ActionSaveAs(){
    QString save_path = SaveFile(nullptr, "Save As");
    if(save_path!="")
        file_path = save_path;
}
void Textino::ActionExit(){
    if(changed)
        SavePrevious();
    if(!changed)
        close();
}
