/*
** Model.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Fri May 24 14:00:48 2013 maxime ginters
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
    _model = sModelFactory->load(_object->GetModelId());
    gdl::Model::cut_animation(*_model, "Take 001", 0, 0, "Idle");
    gdl::Model::cut_animation(*_model, "Take 001", 0, 30, "Start run");
    gdl::Model::cut_animation(*_model, "Take 001", 35, 53, "Run");
    gdl::Model::cut_animation(*_model, "Take 001", 57, 120, "End Run");
}

void GraphicObject::update(gdl::GameClock const &clock)
{
    if (!IsLoaded())
        Load();

    if (_object->HasMovementFlag(MOVEMENT_FORWARD))
        _model->play("Run");
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
