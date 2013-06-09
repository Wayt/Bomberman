/*
** Model.cpp for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:10 2013 vincent leroy
** Last update Sun Jun 09 16:30:00 2013 vincent leroy
*/

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GraphicObject.h"
#include "Model.hpp"
#include "ClientObject.h"

GraphicObject::GraphicObject(ClientObject const *o) :
    _object(o), _model(NULL),
    _config(), _color(NULL)

{
}

GraphicObject::~GraphicObject()
{
    delete _model;
    delete _color;
}

void GraphicObject::init()
{
    _config = sModelFactory->load(_object->GetModelId());
    _model = _config.model;

    if (_object->GetModelId() == 0 || _object->GetModelId() == 9)
    {
        _color = new gdl::Color(rand() % 255, rand() % 255, rand() % 255);
        _model->set_default_model_color(*_color);
    }
}

void GraphicObject::update(gdl::GameClock const &clock)
{
    if (_model == NULL)
        init();
    if (_config.nbAnim > 0)
    {
        if (_object->HasMovementFlag(MOVEMENT_FORWARD))
            _model->play("FORWARD");
        else if (_object->HasMovementFlag(MOVEMENT_BACKWARD))
            _model->play("BACKWARD", gdl::Anim::REVERT);
        else if (_model->anim_is_ended("FORWARD") || _model->anim_is_ended("BACKWARD"))
            _model->play("IDLE");
    }
    else
        _model->draw();
    _model->update(clock);
}

void GraphicObject::draw()
{
    if (_model == NULL)
        init();
    float x, y, z, o;
    _object->GetPosition(x, y, z, o);

    glPushMatrix();
    glTranslatef(_config.x + x, _config.y + y, _config.z);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef(((o * 180.0f) / M_PI) + 90, 0.0f, 1.0f, 0.0f);
    glScalef(_config.scaleX, _config.scaleY, _config.scaleZ);
    _model->draw();
    glPopMatrix();
}
