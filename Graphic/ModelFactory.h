/*
** ModelFactory.h for bomberman in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 22 16:47:23 2013 fabien casters
** Last update Wed Jun 05 17:06:22 2013 vincent leroy
*/

#ifndef MODELFACTORY_H_
# define MODELFACTORY_H_

#include <list>

#include "Shared.h"
#include "MapObject.h"
#include "Model.hpp"

struct animation
{
    std::string name;
    uint32 frameBegin;
    uint32 frameEnd;
};

struct modelConfig
{
    std::string name;
    std::string stackAnim;
    float x;
    float y;
    float z;
    float scaleX;
    float scaleY;
    float scaleZ;
    std::vector<animation> elems;
    gdl::Model *model;
    uint32 nbAnim;
};

class ModelFactory : public Singleton<ModelFactory>
{
public:
    ModelFactory();

    void init(const std::string &filename);
    modelConfig load(uint32);

private:
    uint32 addModel(modelConfig &model, const std::vector<std::string> &elems);
    void addAnimation(modelConfig &model, const animation &anim) const;

    std::map<uint32, modelConfig> _modelConfig;
};

#define sModelFactory ModelFactory::instance()

#endif

