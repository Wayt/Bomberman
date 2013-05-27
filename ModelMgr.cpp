/*
** ModelMgr.cpp for Heex
*/

#include "ModelMgr.h"

ModelMgr::ModelMgr() : _modelMap()
{
    _modelMap[1] = new Model(1, 5.0f, 5.0f, 5.0f);
}

ModelMgr::~ModelMgr()
{
    for (std::map<uint32, Model*>::iterator itr = _modelMap.begin(); itr != _modelMap.end(); ++itr)
        delete itr->second;
}

ModelBox ModelMgr::GetModelBoxAtPos(float x, float y, float z, uint32 modelid) const
{
    Model const* model = GetModel(modelid);
    if (!model)
        throw UnknowModelExcept();

    ModelBox box;
    box.min.x = x - (model->width / 2.0f);
    box.min.y = y - (model->height / 2.0f);
    box.min.z = z;
    box.max.x = x + (model->width / 2.0f);
    box.max.y = y + (model->height / 2.0f);
    box.max.z = z + model->zsize;

    return box;
}

Model const* ModelMgr::GetModel(uint32 id) const
{
    std::map<uint32, Model*>::const_iterator itr = _modelMap.find(id);
    if (itr != _modelMap.end())
        return itr->second;
    return NULL;
}
