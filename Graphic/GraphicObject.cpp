/*
** Model.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Wed May 22 19:07:08 2013 fabien casters
*/

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GraphicObject.h"
#include "Model.hpp"
#include "ModelFactory.h"
#include "ClientObject.h"

GraphicObject::GraphicObject(ClientObject const *o) :
    _object(o), _model(NULL)
{
    _model = sModelFactory->load(o->GetModelId());
    _model->play("Take 001");
}

void GraphicObject::update(gdl::GameClock const &clock)
{
    _model->update(clock);
}

void GraphicObject::draw()
{
    //float size = 5.0f;
    float x, y, z, o;
    _object->GetPosition(x, y, z, o);

    glPushMatrix();
    glColor3ub(0, 255, 0); // Vert
    glTranslatef(x, y, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef((o * 360.0f) / M_PI, 0.0f, 1.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    _model->draw();
    glPopMatrix();
}
