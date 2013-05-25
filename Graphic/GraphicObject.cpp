/*
** Model.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Fri May 24 19:47:19 2013 fabien casters
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
}

bool GraphicObject::IsLoaded() const
{
    return _model != NULL;
}

void GraphicObject::Load()
{
    _model = new gdl::Model(sModelFactory->load(_object->GetModelId()).model);
}

void GraphicObject::update(gdl::GameClock const &clock)
{
    if (!IsLoaded())
        Load();

    if (_object->HasMovementFlag(MOVEMENT_FORWARD))
        _model->play("FORWARD");
    else if (_object->HasMovementFlag(MOVEMENT_BACKWARD))
        _model->play("BACKWARD", gdl::Anim::REVERT);
    else if (_model->anim_is_ended("FORWARD") || _model->anim_is_ended("BACKWARD"))
        _model->play("IDLE");
    _model->update(clock);
}

void GraphicObject::draw()
{
    if (!IsLoaded())
        Load();

    float x, y, z, o;
    _object->GetPosition(x, y, z, o);

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef(((o * 180.0f) / M_PI) + 90, 0.0f, 1.0f, 0.0f);
    glScalef(0.002f, 0.002f, 0.002f);
    _model->draw();
    glPopMatrix();
}
