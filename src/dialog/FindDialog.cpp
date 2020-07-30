//*  Filename: FindDialog.cpp
//*  Created Date: 2020-07-25 15:34:39
//*  Modified Date: 2020-07-28 11:05:46
//*  Description:
//*         Implementation of FindDialog class


#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent, QsciScintilla *pText): 
    QDialog (parent, Qt::WindowCloseButtonHint | Qt::Drawer) {
    
    InitControl();
    ConnectSlot();
    setLayout(layout);
    // set size
    setFixedSize(600,250);
    setWindowTitle("Find");

    SetQsciScintilla(pText);
}

void FindDialog::InitControl() {

    // init some component
    find_edit = new LineEdit();
    find_label = new QLabel("Target: ");
    find_btn = new QPushButton("Find next(&F)");
    cancel_btn = new QPushButton("Cancel");
    match_check_box = new QCheckBox("Case sensitive");
    radio_group_box = new QGroupBox("Deriction");
    upward_btn = new QRadioButton("Upward(&U)");
    layout = new QGridLayout();
    downward_btn = new QRadioButton("Downward(&D)");
    downward_btn->setChecked(true);

    h_box_layout = new QHBoxLayout();
    h_box_layout->addWidget(upward_btn);
    h_box_layout->addWidget(downward_btn);
    radio_group_box->setLayout(h_box_layout);

    // add component into layout
    layout->addWidget(find_label,0,0);
    layout->addWidget(find_edit,0,1);
    layout->addWidget(find_btn,0,2);

    layout->addWidget(match_check_box,1,0);
    layout->addWidget(radio_group_box,1,1);
    layout->addWidget(cancel_btn,1,2);

}

// connect signal with slot function
void FindDialog::ConnectSlot() {
    connect(find_btn, SIGNAL(clicked()), this, SLOT(FindClicked()));
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(CancelClicked()));
}

void FindDialog::SetQsciScintilla(QsciScintilla *pText) {
    text = pText;
}

QsciScintilla * FindDialog::GetQsciScintilla() {
    return text;
}

// slot function, corresponding click event
void FindDialog::FindClicked()
{
    QString target = find_edit->text();
    // if case sensitive
    bool case_sensitive = match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    bool is_find = true;
    int ln, col;
    text->getCursorPosition(&ln, &col);
    if (( text != nullptr) && (target != "")){
        QString temp_text = text->text();

        if (downward_btn->isChecked()){

            // find the first target from the location (ln, col) 
            if ( ! text->findFirst(target, false, case_sensitive, false, true, true, ln , col) )
                is_find = false; // if not find 
        }

        if (upward_btn->isChecked()){

            if ( ! text->findFirst(target, false, case_sensitive, false, true, false, ln, col - target.length()) )
                is_find = false;
        }

        // if not find, send massage
        if (! is_find){ 
            QMessageBox msg(this);
            msg.setWindowTitle("notepad");
            msg.setText(QString("cann't find ") + "\"" + target + "\"");
            msg.setWindowFlag(Qt::Drawer);
            msg.setIcon(QMessageBox::Information);
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
        }
    }
}

void FindDialog::CancelClicked()
{
    close();
}

bool FindDialog::event(QEvent* e)
{
    if( e->type() == QEvent::Close ){
        hide();
        return true;
    }
    return QDialog::event(e);
}

FindDialog::~FindDialog(){}
