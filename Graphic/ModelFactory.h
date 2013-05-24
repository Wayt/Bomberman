/*
** ModelFactory.h for bomberman in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 22 16:47:23 2013 fabien casters
** Last update Fri May 24 18:39:11 2013 fabien casters
*/

#ifndef MODELFACTORY_H_
# define MODELFACTORY_H_

#include <list>

#include "Shared.h"
#include "MapObject.h"

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
    gdl::Model model;
};

class ModelFactory : public Singleton<ModelFactory>
{
public:
    ModelFactory();

    bool init(const std::string &filename);
    modelConfig const &load(uint32);

private:
    uint32 addModel(modelConfig &model, const std::vector<std::string> &elems);
    void addAnimation(modelConfig &model, const std::vector<std::string> &elems);

    std::map<uint32, modelConfig> _modelConfig;
};

#define sModelFactory ModelFactory::instance()

#endif

