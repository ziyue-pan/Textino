#ifndef TEXTINO_H
#define TEXTINO_H

#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "PlainTextEdit.h"
#include <QString>
#include <QFileDialog>

class Textino : public QMainWindow
{
    Q_OBJECT

public:
    Textino(QWidget *parent = nullptr);
    ~Textino();

private:
    PlainTextEdit main_editor;
    QLabel status_label;
    QString file_path;
    bool changed;

    void CreateMenuBar();
    void CreateAction(QAction*& action, QWidget* parent, QString instence, int short_cut, QString icon_path);
    void CreateStatusBar();
    void CreateMainEditor();

    void OpenFile(QString open_path);

    void DragEnterEvent(QDragEnterEvent* drag_event);
    void DropEvent(QDropEvent* drop_event);
    void SavePrevious();
    QString SaveFile(QString path, QString title);
    int ShowMessage(bool error, QString text);
    QString ShowDialog(QFileDialog::AcceptMode mode, QString title, QString icon_path);

private slots:
    void ActionNew();
    void ActionOpen();
    void ActionSave();
    void ActionSaveAs();
    void ActionExit();

    void ActionCopy();
    void ActionCut();
    void ActionPaste();
    void ActionUndo();
    void ActionRedo();

    void ActionHighlight();
    void ActionCursor();
    void ActionChanged();

protected:
    void closeEvent(QCloseEvent* event);

};
#endif // TEXTINO_H
