#ifndef _LINEEDIT_H_
#define _LINEEDIT_H_

#include<QWidget>
#include<QLineEdit>
#include<QString>
#include<QKeyEvent>

class LineEdit:public QLineEdit
{
    Q_OBJECT 
    public:
        LineEdit(QWidget * parent = 0);
    protected: 
        // keyPressEvent 函数重载
        void keyPressEvent(QKeyEvent * event);
        // void keyReleaseEvent(QkeyEvent * event);
};

#endif