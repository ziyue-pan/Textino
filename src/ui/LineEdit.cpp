#include"LineEdit.h"
#include<QKeyEvent>

// QLineEdit 重载
LineEdit::LineEdit(QWidget* parent):QLineEdit(parent)
{
    setFocusPolicy(Qt::StrongFocus);

}

void LineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Tab){
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
    
}