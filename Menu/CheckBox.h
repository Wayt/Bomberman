/*
** CheckBox.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Thu May 30 14:11:36 2013 
** Last update Thu May 30 14:11:36 2013 
*/


#ifndef __CHECKBOX__
#define __CHECKBOX__

#include <iostream>
#include "SelectBox.h"

class CheckBox : public SelectBox
{
    public:
	CheckBox (float, float, float, float);
	~CheckBox ();
	virtual bool select ();
};

#endif
