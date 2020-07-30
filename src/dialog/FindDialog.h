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


#include "../ui/LineEdit.h"

class FindDialog : public QDialog {
    Q_OBJECT

protected:
    // UI elements
    QGroupBox *radio_group_box;     // group box

    QGridLayout *layout;            // grid layout
    QHBoxLayout *h_box_layout;      // horizontal layout

    QLabel *find_label;             // label
    LineEdit *find_edit;            // enter box (input box)
    QPushButton *find_btn;          // find button
    QPushButton *cancel_btn;        // cancel button
    QCheckBox *match_check_box;     // check box
    QRadioButton *upward_btn;       // upward
    QRadioButton *downward_btn;     // downward

    // Qscintilla text content
    QPointer<QsciScintilla> text;

    void InitControl();     // initialize the interface of Find
    void ConnectSlot();     // cnnect signals and slot functions

public slots:
    void FindClicked();     // find clicked
    void CancelClicked();   // cancel clicked

public:
    FindDialog(QWidget *parent = nullptr, QsciScintilla *pText = nullptr);
    ~FindDialog();

    // set qscintilla
    void SetQsciScintilla(QsciScintilla *pText);
    // get text content
    QsciScintilla * GetQsciScintilla();

    // override event function
    bool event(QEvent *e);
    
};

#endif
