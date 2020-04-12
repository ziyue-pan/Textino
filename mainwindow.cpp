#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QIcon>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    current_file = "";  // current file name
    changed = false;    // changed text

    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    QFont font;
    font.setPixelSize(18);
    font.setFamily("Consolas");
    ui->textEdit->setFont(font);

    setWindowTitle("New Document - Textino");
    //setWindowIcon(QIcon(":/Res/imgs/icon.png"));
    setAcceptDrops(true);


}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot Save File: "+file.errorString());
        return;
    }
    current_file = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
