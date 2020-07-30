//*  Filename: LineEdit.h
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*         The class to override some functions in class QLineEdit

#ifndef _LINEEDIT_H_
#define _LINEEDIT_H_

#include<QWidget>
#include<QLineEdit>
#include<QString>
#include<QKeyEvent>

class LineEdit:public QLineEdit {
    Q_OBJECT 
    public:
        LineEdit(QWidget * parent = 0);
    protected: 
        // keyPressEvent 函数重载
        void keyPressEvent(QKeyEvent * event);
};

#endif