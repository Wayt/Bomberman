/*
** Menu.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Thu May 16 11:01:55 2013 
** Last update Thu May 16 11:01:55 2013 
*/



#ifndef __MENU__
#define __MENU__

#include <list>
#include "AObject.h"
#include "SubMenu.h"
#include "InputBox.h"

class Menu : public AObject
{
public:
    Menu(float, float, float, float);
    virtual ~Menu();

    void initialize();
    void update(gdl::GameClock const&, gdl::Input &);
    void draw();
    void startSolo(InputBox *box);
    void joinServer(InputBox *box);
    void createServer(InputBox *box);
    void startWithMap(InputBox *name, InputBox *map);

private:
    SubMenu			menu_;
};


#endif /*__MENU__*/
