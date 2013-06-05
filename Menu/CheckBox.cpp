//
// CheckBox.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Thu May 30 14:11:29 2013 
// Last update Thu May 30 14:11:29 2013 
//

#include "CheckBox.h"

CheckBox::CheckBox (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    ret_ = false;
    value_ = 0;
    intervalH_ = 500;
}

CheckBox::~CheckBox ()
{
}

bool CheckBox::select ()
{
    mvt_ = SubObject::NONE;
    if (!value_){
	SubObject::setTexture(img2_);
	value_ = 1;
    }
    else {
	SubObject::setTexture(img1_);
	value_ = 0;
    }
    return true;
}
