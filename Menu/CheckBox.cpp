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
    SelectBox(x, y, z, o), status_(false)
{
    //SubObject::setMovableH();
    ret_ = false;
    intervalH_ = 500;
}

CheckBox::~CheckBox ()
{
}


bool CheckBox::select ()
{
    mvt_ = SubObject::NONE;
    if (status_){
	SelectBox::setTexture(img1_);
    }
    else {
	SelectBox::setTexture(img2_);
    }
    status_ = !status_;
    std::cout << "status:" << status_ << std::endl;
    return true;
}

void CheckBox::setTexture (const std::string &img1, const std::string &img2)
{
    img1_ = img1;
    img2_ = img2;

    SelectBox::setTexture(img1);
}
