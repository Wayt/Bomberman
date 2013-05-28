/*
** GraphicObject.h for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:13 2013 vincent leroy
** Last update Tue May 28 14:35:20 2013 fabien casters
*/

#ifndef GRAPHICOBJECT_H_
# define GRAPHICOBJECT_H_

#include "GameClock.hpp"
#include "ModelFactory.h"
#include "Model.hpp"

class ClientObject;

class GraphicObject
{
public:
    GraphicObject(ClientObject const *);
    void init();
    void update(gdl::GameClock const &);
    void draw();

private:
    ClientObject const *_object;
    gdl::Model *_model;
    modelConfig _config;
};

#endif
