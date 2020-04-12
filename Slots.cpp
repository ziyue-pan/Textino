#include "Textino.h"
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>

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
    else
        setWindowTitle("New document - Textino");
}
void Textino::ActionOpen(){


}
void Textino::ActionSave(){

}
void Textino::ActionSaveAs(){

}
void Textino::ActionExit(){

}
