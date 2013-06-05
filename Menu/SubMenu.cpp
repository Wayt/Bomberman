//
// Submenu.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/SubMenu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Sat May 25 01:42:07 2013 
// Last update Sat May 25 01:42:07 2013 
//


#include <iostream>
#include <sstream>
#include <unistd.h>
#include "CheckBox.h"
#include "SelectBox.h"
#include "ListBox.h"
#include "InputBox.h"
#include "SubMenu.h"
#include "Image.hpp"

/*{ SubMenu */
SubMenu::SubMenu(float x, float y, float z, float o) :
    SubObject(x, y, z, o), keyVector_(gdl::Keys::Count, false)
{
    currentBox_ = 0;
    sbox_ = 0;
    intervalV_ = 120;
}

SubMenu::~SubMenu()
{
}
/*}*/

/*{ AObject */
void SubMenu::initialize()
{
    int 		id;

    id = 0;
    for (std::list<SelectBox *>::iterator it = boxes_.begin(); 
	    it != boxes_.end(); ++it, id++){
	(*it)->setId(id);
	(*it)->initialize();
	(*it)->setStatus(SubObject::VISIBLE);
    }
}

void SubMenu::update(gdl::GameClock const &clock, gdl::Input &input)
{ 
    if (status_ == SubObject::VISIBLE){
	for (int i = 0; i < gdl::Keys::Count; ++i)
	    keyVector_[i] = input.isKeyDown((gdl::Keys::Key)i);
	UpdateInput();
    }
    for (std::list<SelectBox *>::iterator it = boxes_.begin(); it != boxes_.end(); ++it)
    {
	if (status_ == SubObject::VISIBLE)
	    motionController(*it);
	(*it)->update(clock, input);
	if ((*it)->getStatus() == SubObject::BACK){
	    for (std::list<SelectBox *>::iterator it = boxes_.begin(); 
		    it != boxes_.end(); ++it)
		(*it)->setStatus(SubObject::VISIBLE);
	    setStatus(SubObject::VISIBLE);
	}

    }
}

void SubMenu::draw()
{
    for (std::list<SelectBox *>::iterator it = boxes_.begin(); it != boxes_.end(); ++it)
    {
	(*it)->draw();
    }
}
/*}*/

/*{ Inputs */
void SubMenu::UpdateInput()
{
    static std::vector<bool> prevKeys(gdl::Keys::Count, false);

    int size = keyVector_.size();
    for (int i = 0; i < size; ++i)
    {
        if (keyVector_[i] && !prevKeys[i])
            HandleKeyDown((gdl::Keys::Key)i);
        else if (!keyVector_[i] && prevKeys[i])
            HandleKeyUp((gdl::Keys::Key)i);
        prevKeys[i] = keyVector_[i];
    }
}

void SubMenu::HandleKeyUp(gdl::Keys::Key key)
{
    (void)key;
}

void SubMenu::HandleKeyDown(gdl::Keys::Key key)
{
    if (mvt_ == NONE){
	if ( key == gdl::Keys::Space){
	    std::list<SelectBox *>::iterator sit = boxes_.begin();
	    std::advance(sit, currentBox_);
	    if ((*sit)->getRet() == true){
		for (std::list<SelectBox *>::iterator it = boxes_.begin(); 
			it != boxes_.end(); ++it){
		    (*it)->setStatus(SubObject::HIDDEN);
		}
		(*sit)->select();
		setStatus(SubObject::HIDDEN);
	    }
	    else if ((*sit)->select() == false){
		for (std::list<SelectBox *>::iterator it = boxes_.begin(); 
			it != boxes_.end(); ++it){
		    (*it)->initpos(_pos.x, _pos.y, _pos.z, intervalV_);
		}
		currentBox_ = 0;
		setRet(false);
	    }
	    mvt_ = (*sit)->getMvt();
	}
	if ( key == gdl::Keys::Up)
	    if (currentBox_ > 0){
		mvt_ = UP;
		currentBox_--;
	    }
	if ( key == gdl::Keys::Down)
	    if (currentBox_ < boxes_.size() - 1){
		mvt_ = DOWN;
		currentBox_++;
	    }
	if ( key == gdl::Keys::Right)
		mvt_ = RIGHT;
	if ( key == gdl::Keys::Left)
		mvt_ = LEFT;
    }
}
/*}*/

void	SubMenu::motionController(SelectBox *box)
{
    std::list<SelectBox *>::iterator it = boxes_.begin();
    std::advance(it, currentBox_);
	switch (mvt_)
	{
	    case UP:
		if (!box->moveUp()){
		    sbox_++;
		}
		break;
	    case DOWN:
		if (!box->moveDown()){
		    sbox_++;
		}
		break;
	    case RIGHT:
		if (isMovableH()){
		    if (!box->moveRight())
			mvt_ = NONE;
		}
		else
		    mvt_ = SRIGHT;
		break;
	    case LEFT:
		if (isMovableH()){
		    if (!box->moveLeft())
			mvt_ = NONE;
		}
		else
		    mvt_ = SLEFT;
		break;
	    case SRIGHT:
		if ((*it)->isMovableH()){
		    if (!(*it)->moveRight())
			mvt_ = NONE;
		}
		else
			mvt_ = NONE;
		break;
	    case SLEFT:
		if ((*it)->isMovableH()){
		    if (!(*it)->moveLeft())
			mvt_ = NONE;
		}
		else
			mvt_ = NONE;
		break;
	    default:
		break;
	}
	if (sbox_ == boxes_.size()){
	    mvt_ = NONE;
	    sbox_ = 0;
	}
}

void	SubMenu::addObject(SelectBox *obj)
{
    boxes_.push_back(obj);
    sbox_++;
}
void	SubMenu::addBox(const std::string &key, SelectBox::e_boxtype type) 
{
    SelectBox *box;
    switch (type)
    {
	case SelectBox::SELECTBOX:
	    box = new SelectBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
	    break;
	case SelectBox::CHECKBOX:
	    box = new CheckBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
	    break;
	case SelectBox::INPUTBOX:
	    box = new InputBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
	    break;
	default:
	    break;
    }
    box->setKey(key);
    addObject(box);
}

void   SubMenu::addBox(const std::string &key, const std::string &img, SubObject *obj)
{
    SelectBox *box = new SelectBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
    box->addSubObject(obj);
    box->setTexture(img);
    box->setKey(key);
    addObject(box);
}

void	SubMenu::addBox(const std::string &key, const std::list<std::string> &imgs) 
{
    ListBox *box;
    box = new ListBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
    box->setImgs(imgs);
    box->setKey(key);
    addObject(box);
}

void   SubMenu::addBackBox(const std::string &img)
{
    SelectBox *box = new SelectBox(_pos.x - (sbox_ * intervalV_), _pos.y, _pos.z - (sbox_ * intervalV_), _rot.x);
    box->setRet(false);
    box->setTexture(img);
    addObject(box);
}



bool SubMenu::select ()
{
    return true;
}

SubObject *SubMenu::operator [] (const std::string &key)
{
    SelectBox *box;
    for (std::list<SelectBox *>::iterator it = boxes_.begin(); 
	    it != boxes_.end(); ++it){
	if ((*it)->getKey() == key){
	    if ((box = dynamic_cast<SelectBox*>(*it)) != NULL)
		if (box->getSubObject())
		    return box->getSubObject();
	    return *it;
	}
    }
    return NULL;
}
