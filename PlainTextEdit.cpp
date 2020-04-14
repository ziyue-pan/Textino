#include"PlainTextEdit.h"
#include<QKeyEvent>

// QPlainTextEdit 重载
PlainTextEdit::PlainTextEdit(QWidget* parent):QPlainTextEdit(parent)
{
    setFocusPolicy(Qt::StrongFocus);

}

void PlainTextEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Tab){
        this->insertPlainText("    ");
    }
    else
    {
        QPlainTextEdit::keyPressEvent(event);
    }
    
}