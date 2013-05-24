/*
** GraphicObject.h for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:13 2013 vincent leroy
** Last update Fri May 24 13:58:24 2013 maxime ginters
*/

#ifndef GRAPHICOBJECT_H_
# define GRAPHICOBJECT_H_

#include "GameClock.hpp"
#include "Model.hpp"

class ClientObject;

class GraphicObject
{
public:
    GraphicObject(ClientObject const *);
    void update(gdl::GameClock const &);
    void draw();

    bool IsLoaded() const;
    void Load();
private:
    ClientObject const *_object;
    gdl::Model *_model;
};

#endif
