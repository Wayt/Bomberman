//
// InputBox.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Wed Jun 05 11:49:27 2013 
// Last update Wed Jun 05 11:49:27 2013 
//

#include "InputBox.h"

InputBox::InputBox (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    ret_ = false;
    value_ = 0;
    intervalH_ = 500;
    input_ = "toto";
    setStatus(VISIBLE);
}

InputBox::~InputBox ()
{
}

bool InputBox::select ()
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

void InputBox::update (gdl::GameClock const&, gdl::Input &)
{
}

void InputBox::draw ()
{
    gdl::Text text;
    switch (status_){
	case VISIBLE:
	    SelectBox::draw();
	    text.setText(input_);
	    text.setSize(10);
	    text.setPosition(_pos.x, _pos.y);
	    //text.draw();
	    break;
	case HIDDEN:
	    break;
	case SELECTED:
	    break;
	default:
	    break;
    }
}
