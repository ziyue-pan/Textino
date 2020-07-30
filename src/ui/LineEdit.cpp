//*  Filename: LineEdit.cpp
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*         Implementation of LineEdit class

#include"LineEdit.h"
#include<QKeyEvent>

// QLineEdit override
LineEdit::LineEdit(QWidget* parent):QLineEdit(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void LineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Tab){}
    else{
        QLineEdit::keyPressEvent(event);
    }
    
}