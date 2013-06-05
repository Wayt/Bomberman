/*
** ListBox.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Wed Jun 05 03:45:33 2013 
** Last update Wed Jun 05 03:45:33 2013 
*/

#ifndef __LISTBOX__
#define __LISTBOX__

#include <iostream>
#include <list>
#include "SelectBox.h"

class ListBox : public SelectBox
{
    public:
	ListBox (float, float, float, float);
	~ListBox ();
	virtual bool select ();
	void setImgs(const std::list<std::string> &);
    private:
	std::list<std::string> imgs_;
};

#endif
