/*
** ModelFactory.cpp for bomberman in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 22 16:47:26 2013 fabien casters
** Last update Wed May 22 18:00:06 2013 fabien casters
*/

#include "Model.hpp"
#include "ModelFactory.h"

ModelFactory::ModelFactory()
{
    _models[0] = "Assets/marvin.fbx";
    _models[2] = "Assets/bomb.fbx";
    _models[1] = "Assets/marvin.fbx";
}

gdl::Model *ModelFactory::load(uint32 id)
{
    return new gdl::Model(gdl::Model::load(_models[id]));
}
