#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMainWindow>

class MenuBar: public QMainWindow {
private:

    QMenu *file_menu;   // file menus
    QMenu *edit_menu;   // edit menus
    QMenu *help_menu;   // help menus


    void CreateMenuBar(QAction* action_list[]);

public:
    MenuBar(QAction* action_list[]);
    ~MenuBar();



};





#endif
