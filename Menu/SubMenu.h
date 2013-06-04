/*
** SubMenu.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Sat May 25 01:42:17 2013 
** Last update Sat May 25 01:42:17 2013 
*/


#ifndef __SUBMENU__
#define __SUBMENU__

#include <list>
#include <vector>
#include "SelectBox.h"

class SubMenu : public SubObject
{
public:
    SubMenu (float, float, float, float);
    virtual ~SubMenu ();

    /*{ AObject */
    void initialize ();
    void update (gdl::GameClock const&, gdl::Input &);
    void draw ();
    /*}*/

    bool select ();

    void	addObject(SelectBox *obj);
    void	addBox(const std::string &, SelectBox::e_boxtype);
    void   	addBox(const std::string &key, const std::string &img, SubObject *obj);
    void   	addBackBox(const std::string &img);

    SubObject *operator [] (const std::string &);

private:

    void	motionController (SelectBox *);

    //inputs
    void 	HandleKeyDown (gdl::Keys::Key);
    void 	HandleKeyUp (gdl::Keys::Key);
    void 	UpdateInput ();

    std::list<SelectBox *> 		boxes_;
    std::vector<bool> 			keyVector_;
    unsigned int			sbox_;
    unsigned int 			currentBox_;

};


#endif /*__MENU__*/
