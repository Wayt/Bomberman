/*
** ModelFactory.cpp for bomberman in /home/vaga/Projects/tek2/bomberman/Graphic
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Wed May 22 16:47:26 2013 fabien casters
** Last update Fri May 24 18:48:25 2013 fabien casters
*/

#include <fstream>

#include "Model.hpp"
#include "ModelFactory.h"

ModelFactory::ModelFactory() :
    _modelConfig()
{
}

bool ModelFactory::init(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open())
        return false;

    std::string line;
    while (std::getline(ifs, line))
    {
        modelConfig model;
        std::vector<std::string> elems;
        split(line, ';', elems);
        if (elems.size() < 10)
            continue;

        uint32 modelId = to<uint32>(elems[0].c_str());
        uint32 nbAnim = addModel(model, elems);
        for (uint32 i = 0; i < nbAnim && std::getline(ifs, line); ++i)
        {
            elems.clear();
            split(line, ';', elems);
            if (elems.size() < 3)
                --i;
            else
                addAnimation(model, elems);
        }

        _modelConfig[modelId] = model;
    }

    ifs.close();
    return true;
}

modelConfig const &ModelFactory::load(uint32 id)
{
    return _modelConfig[id];
}

uint32 ModelFactory::addModel(modelConfig &model, const std::vector<std::string> &elems)
{
    model.name = elems[1];
    model.stackAnim = elems[2];
    model.x = to<float>(elems[3].c_str());
    model.y = to<float>(elems[4].c_str());
    model.z = to<float>(elems[5].c_str());
    model.scaleX = to<float>(elems[6].c_str());
    model.scaleY = to<float>(elems[7].c_str());
    model.scaleZ = to<float>(elems[8].c_str());

    model.model = gdl::Model::load(model.name);
    return to<uint32>(elems[9].c_str());
}

void ModelFactory::addAnimation(modelConfig &model, const std::vector<std::string> &elems)
{
    gdl::Model::cut_animation(model.model, model.stackAnim, to<uint32>(elems[1].c_str()), to<uint32>(elems[2].c_str()), elems[0]);
}
