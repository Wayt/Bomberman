/*
** ModelMgr.cpp for Heex
*/

#include "GameObject.h"
#include "ModelMgr.h"

ModelMgr::ModelMgr() : _modelMap()
{
    _modelMap[0] = new Model(0, 2.0f, 2.0f, 2.0f, true);
    _modelMap[1] = new Model(1, 5.0f, 5.0f, 5.0f);
    _modelMap[2] = new Model(2, 2.0f, 2.0f, 2.0f);
    _modelMap[3] = new Model(3, 5.0f, 5.0f, 5.0f);
    _modelMap[4] = new Model(4, 4.0f, 4.0f, 2.0f, true);
    _modelMap[5] = new Model(5, 4.0f, 4.0f, 2.0f, true);
    _modelMap[6] = new Model(6, 4.0f, 4.0f, 2.0f, true);
    _modelMap[7] = new Model(7, 4.0f, 4.0f, 2.0f, true);
    _modelMap[8] = new Model(8, 5.0f, 5.0f, 5.0f, true);
}

ModelMgr::~ModelMgr()
{
    for (std::map<uint32, Model*>::iterator itr = _modelMap.begin(); itr != _modelMap.end(); ++itr)
        delete itr->second;
}

ModelBox ModelMgr::GetModelBoxAtPos(const GameObject *obj) const
{
    return GetModelBoxAtPos(obj->GetPositionX(), obj->GetPositionY(), obj->GetPositionZ(), obj->GetModelId());
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
    box.crossable = model->crossable;

    return box;
}

Model const* ModelMgr::GetModel(uint32 id) const
{
    std::map<uint32, Model*>::const_iterator itr = _modelMap.find(id);
    if (itr != _modelMap.end())
        return itr->second;
    return NULL;
}
