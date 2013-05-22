/*
** ModelFactory.h for bomberman in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 22 16:47:23 2013 fabien casters
** Last update Wed May 22 17:16:53 2013 fabien casters
*/

#ifndef MODELFACTORY_H_
# define MODELFACTORY_H_

#include "Shared.h"
#include "MapObject.h"

class ModelFactory : public Singleton<ModelFactory>
{
public:
    ModelFactory();
    gdl::Model *load(uint32);
private:
    std::map<uint32, std::string> _models;
};

#define sModelFactory ModelFactory::instance()

#endif

