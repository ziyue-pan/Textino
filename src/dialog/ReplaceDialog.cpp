//*  Filename: ReplaceDialog.cpp
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*         Implementation of ReplaceDialog class

#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget* parent, QsciScintilla* pText)
    : FindDialog (parent, pText) {
    InitControl();
    ConnectSlot();
}

void ReplaceDialog::InitControl()
{
    // init some component
    replace_label = new QLabel("Replace");
    replace_btn = new QPushButton("Replace(&R)");
    replace_all_btn = new QPushButton("Replace all(&A)");
    replace_edit = new LineEdit();

    // remove the extra component 
    layout->removeWidget(match_check_box);
    layout->removeWidget(radio_group_box);
    layout->removeWidget(cancel_btn);

    // add component into layout
    layout->addWidget(replace_label, 1, 0);
    layout->addWidget(replace_edit, 1, 1);
    layout->addWidget(replace_btn, 1, 2);

    layout->addWidget(match_check_box, 2, 0);
    layout->addWidget(radio_group_box, 2, 1);
    layout->addWidget(replace_all_btn, 2, 2);

    layout->addWidget(cancel_btn, 3, 2);

    // set window size
    setFixedSize(600,350);
    setWindowTitle("Replace");
    setLayout(layout);
}

// connect signal with slot function
void ReplaceDialog::ConnectSlot()
{
    connect(replace_btn, SIGNAL(clicked()), this, SLOT(ReplaceClicked()));
    connect(replace_all_btn, SIGNAL(clicked()), this, SLOT(ReplaceAllClicked()));
}

// slot function, corresponding click event
void ReplaceDialog::ReplaceClicked()
{
    QString target = find_edit->text();
    QString to = replace_edit->text();
    bool case_sensitive = match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    // if target is exist
    if( (text != nullptr) && (target != "") && (to != "") )
    {
        QString selText = text->selectedText();
        if( selText == target || ( !case_sensitive && selText.toLower() == target.toLower()))
            text->replaceSelectedText(to);
        FindClicked(); // find the next target
    }
}

// slot function, corresponding click event
// replace all target
void ReplaceDialog::ReplaceAllClicked()
{
    QString target = find_edit->text();
    QString to = replace_edit->text();

    if( (text != nullptr) && (target != "") && (to != "") )
    {
        QString temp_text = text->text(); // get the text
        temp_text.replace(target, to, match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        text->clear();
        text->insert(temp_text);   // set text
    }
}
