//*  Filename: ReplaceDialog.h
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*     Header files for replace function.
//*     A Class ReplaceDialog, the subclass of FindDialog

#ifndef _REPLACEDIALOG_H
#define _REPLACEDIALOG_H

#include "FindDialog.h"
#include "../ui/LineEdit.h"

//@ Class:  FindDialog
//@ Description:
//          Work as the replace windows of GUI application.
//@ Usage:
//          ReplaceDialog dialog;   
//          dialog.show();  

class ReplaceDialog : public FindDialog {
    
    Q_OBJECT

protected:
    QLabel *replace_label;          // replace label
    LineEdit *replace_edit;         // input box
    QPushButton *replace_btn;       // replace button
    QPushButton *replace_all_btn;   // replace all button

    void InitControl();             // initialize
    void ConnectSlot();             // config slots

protected slots:
    void ReplaceClicked();          // replace clicked
    void ReplaceAllClicked();       // replace all clicked

public:
    ReplaceDialog(QWidget* parent = nullptr, QsciScintilla* pText = nullptr);
};

#endif // _REPLACEDIALOG_H
