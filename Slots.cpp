#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QSettings>
#include <QSize>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qsciapis.h>

#include "Textino.h"

void Textino::Modified()
{
    setWindowModified(main_editor->isModified());
}

void Textino::About()
{
   QMessageBox::about(this, tr("About Textino"),
            tr("<b>Textino</b> is an extremely light text editor, written by Raymond Ziyue"));
}


bool Textino::SaveAs()
{
    QString file_name = QFileDialog::getSaveFileName(this);
    if (file_name.isEmpty())
        return false;

    return SaveFile(file_name);
}
