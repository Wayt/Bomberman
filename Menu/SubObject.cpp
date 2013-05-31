//
// SubObject.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Tue May 28 16:59:17 2013 
// Last update Tue May 28 16:59:17 2013 
//

#include <iostream>
#include <unistd.h>
#include "SubObject.h"

/*{ SubObject */
SubObject::SubObject (float x, float y, float z, float o) :
    AObject(x, y, z, o)
{
    mvt_ = NONE;
    oldpos_.x = x;
    oldpos_.y = y;
    oldpos_.z = z;
    ret_ = true;
    h_ = false;
}

SubObject::~SubObject ()
{
}
/*}*/

void SubObject::setId (int id)
{
    id_ = id;
}

int SubObject::getId ()
{
    return id_;
}

void SubObject::setStatus(e_status status)
{
    status_ = status;
}

SubObject::e_status SubObject::getStatus()
{
    return status_;
}

void SubObject::setRet (bool ret)
{
    ret_ = ret;
}

bool SubObject::getRet ()
{
    return ret_;
}

void SubObject::setIntervalV(int intV)
{
    intervalV_ = intV;
}

void SubObject::setIntervalH(int intH)
{
    intervalH_ = intH;
}

void SubObject::setMovableH()
{
    h_ = true;
}

bool SubObject::isMovableH()
{
    return h_;
}

SubObject::e_movement SubObject::getMvt()
{
    return mvt_;
}
