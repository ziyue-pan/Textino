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
    setFixedSize(600,250);
    setWindowTitle("Find");

    SetQsciScintilla(pText);
}

void FindDialog::InitControl() {
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

    layout->addWidget(find_label,0,0);
    layout->addWidget(find_edit,0,1);
    layout->addWidget(find_btn,0,2);

    layout->addWidget(match_check_box,1,0);
    layout->addWidget(radio_group_box,1,1);
    layout->addWidget(cancel_btn,1,2);

}

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

int FindDialog::GetCursorIndex() {
    int col, ln;
    text->getCursorPosition(&ln, &col);
    int index = 0;
    for (int i=0; i<ln; i++)
        index += text->lineLength(i);
    index += col;
    return index;
}

void FindDialog::SetCursorIndex(int index, bool direction) {
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = index;
    QString temp_text = text->text();
    QString target = find_edit->text();
    
    for(int i=0; i<pos; i++){
        if( temp_text[i] == '\n' ) {
            ln ++;
            flg = i;
        }
    }
    flg ++;
    col = pos - flg;
    if (direction)
        text->setSelection(ln, col, ln, col + target.length());
    else
        text->setSelection(ln, col + target.length(), ln, col);

}

void FindDialog::FindClicked()
{
    QString target = find_edit->text();
    if (( text != nullptr) && (target != "")){
        QString temp_text = text->text();
        int index = -1;

        if (downward_btn->isChecked()){
            index = temp_text.indexOf(target, GetCursorIndex() + target.length(),  match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
            if (index >= 0){
                SetCursorIndex(index, true);  
            }
        }

        if (upward_btn->isChecked()){
            index = temp_text.lastIndexOf(target, text->selectedText().length() == 0 ? GetCursorIndex() - temp_text.length() - 1 : GetCursorIndex() - temp_text.length() - 1 - target.length(), match_check_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
            if (index >= 0){
                SetCursorIndex(index, false);  
            }
        }

        if (index < 0){
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