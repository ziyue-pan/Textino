#include "MenuBar.h"


#include <QMenu>
#include <QMenuBar>

MenuBar::MenuBar(QAction* action_list[]) {
    CreateMenuBar(action_list);
}


MenuBar::~MenuBar() {

}

void MenuBar::CreateMenuBar(QAction * action_list[])
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(action_list[0]);
    file_menu->addAction(action_list[1]);
    file_menu->addAction(action_list[2]);
    file_menu->addAction(action_list[3]);
    file_menu->addSeparator();
    file_menu->addAction(action_list[4]);

    edit_menu = menuBar()->addMenu(tr("&Edit"));
    edit_menu->addAction(action_list[5]);
    edit_menu->addAction(action_list[6]);
    edit_menu->addAction(action_list[7]);
    edit_menu->addAction(action_list[10]);
    edit_menu->addAction(action_list[9]);

    menuBar()->addSeparator();

    help_menu = menuBar()->addMenu(tr("&Help"));
    help_menu->addAction(action_list[8]);

}
