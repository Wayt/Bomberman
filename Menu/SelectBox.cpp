//
// SelectBox.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Thu May 16 10:39:41 2013 
// Last update Thu May 16 10:39:41 2013 
//

#include <iostream>
#include <unistd.h>
#include "SelectBox.h"

/*{ SelectBox */
SelectBox::SelectBox (float x, float y, float z, float o) :
    SubObject(x, y, z, o)
{
    intervalH_ = 400;
    intervalV_ = 120;
    obj_ = NULL;
    ret_ = true;
    h_ = false;
}

SelectBox::~SelectBox ()
{
}

/*}*/

/*{ AObject */
void SelectBox::initialize ()
{
}

void SelectBox::update (gdl::GameClock const&clock, gdl::Input &input)
{
    switch (status_){
	case VISIBLE:
	    break;
	case HIDDEN:
	    break;
	case SELECTED:
	    if (obj_){
		obj_->update(clock, input);
	    }
	    break;
	default:
	    break;
    }
}

void SelectBox::draw ()
{
    switch (status_){
	case VISIBLE:
	    glEnable(GL_TEXTURE_2D);
	    texture_.bind();
	    glBegin(GL_QUADS);
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(_pos.x, _pos.y, _pos.z);
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(_pos.x, _pos.y + texture_.getWidth(), _pos.z);
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(_pos.x + texture_.getHeight(), _pos.y + texture_.getWidth(), _pos.z);
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(_pos.x + texture_.getHeight(), _pos.y, _pos.z);
	    glEnd();
	    glDisable(GL_TEXTURE_2D);
	    break;
	case HIDDEN:
	    break;
	case SELECTED:
	    if (obj_ && obj_->getRet() == true){
		obj_->draw();
	    }
	    else if (obj_){
		setStatus(SubObject::BACK);
		obj_->setRet(true);
	    }
	    break;
	default:
	    break;
    }
}
/*}*/

void SelectBox::setTexture (const std::string &s)
{
    texture_ = gdl::Image::load(s);
}

bool SelectBox::select ()
{
    setStatus (SubObject::SELECTED);
    if (obj_){
	obj_->initialize();
	obj_->setStatus (SubObject::VISIBLE);
    }
    return ret_;
}

void SelectBox::addSubObject (SubObject *obj)
{
    obj_ = obj;
}

/*{ Movements */
bool SelectBox::moveUp ()
{
    _pos.x -= 1;
    if (_pos.x > 0)
	_pos.z += 1;
    else
	_pos.z -= 1;
    if (_pos.x <= oldpos_.x - intervalV_){
	oldpos_.x = _pos.x;
	return false;
    }
    return true;
}

bool SelectBox::moveDown ()
{
    _pos.x += 1;
    if (_pos.x > 0)
	_pos.z -= 1;
    else
	_pos.z += 1;
    if (_pos.x >= oldpos_.x + intervalV_){
	oldpos_.x = _pos.x;
	return false;
    }
    return true;
}

bool SelectBox::moveRight ()
{
	_pos.y += 2;
	if (_pos.y >= oldpos_.y + intervalH_){
	    oldpos_.y = _pos.y;
	    return false;
	}
	return true;
}


bool SelectBox::moveLeft ()
{
    _pos.y -= 2;
    if (_pos.y <= oldpos_.y - intervalH_){
	oldpos_.y = _pos.y;
	return false;
    }
    return true;
}
/*}*/
