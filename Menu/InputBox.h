/*
** InputBox.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Wed Jun 05 11:50:23 2013 
** Last update Wed Jun 05 11:50:23 2013 
*/


#ifndef __INPUTBOX__
#define __INPUTBOX__

#include <iostream>
#include <sstream>
#include "SelectBox.h"
#include "Text.hpp"

class InputBox : public SelectBox
{
    public:
	virtual void draw ();
	virtual void update (gdl::GameClock const&clock, gdl::Input &input);

	InputBox (float, float, float, float);
	~InputBox ();
	virtual bool select ();
	void handleKeyDown(gdl::Keys::Key);


    private:
	std::string input_;
};

#endif
