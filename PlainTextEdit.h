#ifndef PlainTextEdit_H
#define PlainTextEdit_H

#include<QWidget>
#include<QString>
#include<QKeyEvent>
#include<QPlainTextEdit>

class PlainTextEdit:public QPlainTextEdit
{
    Q_OBJECT
    public:
        PlainTextEdit(QWidget * parent = 0);
    protected:
        void keyPressEvent(QKeyEvent * event);
        // void keyReleaseEvent(QkeyEvent * event);
};

#endif