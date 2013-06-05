//
// ListBox.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Wed Jun 05 03:45:28 2013 
// Last update Wed Jun 05 03:45:28 2013 
//

#include "ListBox.h"

ListBox::ListBox (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    ret_ = false;
    value_ = 0;
    intervalH_ = 500;
}

ListBox::~ListBox ()
{
}

bool ListBox::select ()
{
    mvt_ = SubObject::NONE;
    value_ = (unsigned int)value_ < imgs_.size() - 1 ? value_ + 1 : 0;
    std::list<std::string>::const_iterator it = imgs_.begin();
    if (value_ > 0)
	std::advance(it, value_);
    SubObject::setTexture(*it);
    return true;
}

void ListBox::setImgs(const std::list<std::string> &imgs)
{
    imgs_.assign(imgs.begin(), imgs.end());
    SubObject::setTexture(*imgs.begin());
}

