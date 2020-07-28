//*  Filename: ReplaceDialog.cpp
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*         Implementation of ReplaceDialog class

#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget* parent, QsciScintilla* pText) : FindDialog (parent, pText)
{
    initControl();
    connectSlot();
}

void ReplaceDialog::initControl()
{
    replace_label = new QLabel("Replace");
    replace_btn = new QPushButton("Replace(&R)");
    replace_all_btn = new QPushButton("Replace all(&A)");
    replace_edit = new LineEdit();

    layout->removeWidget(match_check_box);
    layout->removeWidget(radio_group_box);
    layout->removeWidget(cancel_btn);

    layout->addWidget(replace_label, 1, 0);
    layout->addWidget(replace_edit, 1, 1);
    layout->addWidget(replace_btn, 1, 2);

    layout->addWidget(match_check_box, 2, 0);
    layout->addWidget(radio_group_box, 2, 1);
    layout->addWidget(replace_all_btn, 2, 2);

    layout->addWidget(cancel_btn, 3, 2);

    setFixedSize(600,350);
    setWindowTitle("Replace");
    setLayout(layout);
}

void ReplaceDialog::connectSlot()
{
    connect(replace_btn, SIGNAL(clicked()), this, SLOT(onReplaceClicked()));
    connect(replace_all_btn, SIGNAL(clicked()), this, SLOT(onReplaceAllClicked()));
}

void ReplaceDialog::onReplaceClicked()
{
    QString target = find_edit->text();
    QString to = replace_edit->text();

    if( (text != nullptr) && (target != "") && (to != "") )
    {
        QString selText = text->selectedText();
        if( selText == target )
            text->replaceSelectedText(to);
        onFindClicked();
    }
}

void ReplaceDialog::onReplaceAllClicked()
{
    QString target = find_edit->text();
    QString to = replace_edit->text();

    if( (text != nullptr) && (target != "") && (to != "") )
    {
        QString temp_text = text->text();
        temp_text.replace(target, to, match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        text->clear();
        text->insert(temp_text);
    }
}