#ifndef _FINDDIALOG_H_
#define _FINDDIALOG_H_

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QPointer>
#include <QPlainTextEdit>
#include <QEvent>
#include <QTextCursor>
#include <QMessageBox>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexer.h>


#include "../ui/LineEdit.h"

class FindDialog : public QDialog
{
    Q_OBJECT

protected:
    QGroupBox *radio_group_box;

    QGridLayout *layout;
    QHBoxLayout *h_box_layout;

    QLabel *find_label;
    LineEdit *find_edit; 
    QPushButton *find_btn;
    QPushButton *cancel_btn;
    QCheckBox *match_check_box;
    QRadioButton *upward_btn;
    QRadioButton *downward_btn;

    QPointer<QsciScintilla> text;

    void initControl();
    void connectSlot();

public slots:
    void onFindClicked();
    void onCancelClicked();

public:
    FindDialog(QWidget *parent = nullptr, QsciScintilla *pText = nullptr);
    void setQsciScintilla(QsciScintilla *pText);
    QsciScintilla * getQsciScintilla();
    bool event(QEvent *e);
    int getCursorIndex();
    void setCursorIndex(int index, bool direction);
    ~FindDialog();
};

#endif