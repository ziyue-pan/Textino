#ifndef _REPLACEDIALOG_H
#define _REPLACEDIALOG_H

#include "FindDialog.h"
#include "../ui/LineEdit.h"

class ReplaceDialog : public FindDialog
{
    
    Q_OBJECT

protected:
    QLabel *replace_label;
    LineEdit *replace_edit;
    QPushButton *replace_btn;
    QPushButton *replace_all_btn;

    void initControl();
    void connectSlot();

protected slots:
    void onReplaceClicked();
    void onReplaceAllClicked();

public:
    ReplaceDialog(QWidget* parent = nullptr, QsciScintilla* pText = nullptr);
};

#endif // _REPLACEDIALOG_H
