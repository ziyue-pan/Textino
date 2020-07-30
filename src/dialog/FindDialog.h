//*  Filename: FindDialog.h
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*     Header files for find function.
//*     A Class FindDialog

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

    void InitControl();    // initialize the interface of Find
    void ConnectSlot();    // cnnect signals and slot functions

public slots:
    void FindClicked();
    void CancelClicked();

public:
    FindDialog(QWidget *parent = nullptr, QsciScintilla *pText = nullptr);
    void SetQsciScintilla(QsciScintilla *pText);
    QsciScintilla * GetQsciScintilla();
    bool event(QEvent *e);
    int GetCursorIndex();
    void SetCursorIndex(int index, bool direction);
    ~FindDialog();
};

#endif