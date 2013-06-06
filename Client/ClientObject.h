/*
** ClientObject.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed May 15 15:33:34 2013 maxime ginters
** Last update Thu Jun 06 15:50:25 2013 maxime ginters
*/

#ifndef CLIENTOBJECT_H_
# define CLIENTOBJECT_H_

#include "GraphicObject.h"
#include "GameObject.h"
#include "MotionMaster.hpp"

typedef SharedPtr<ClientObject> ClientObjectPtr;

class ClientObject : public GameObject
{
public:
    ClientObject(uint64 guid, uint32 modelid, std::string const& name);
    virtual ~ClientObject();

    uint32 GetModelId() const;
    GraphicObject &GetGraphicObject();

    void Update(uint32 const diff);

    void HandleRespawn();

    void TimedRemove(uint32 time);

    MotionMaster* GetMotionMaster();

private:
    uint32 _modelId;
    std::string _name;
    GraphicObject _graphicObject;
    MotionMaster* _motionMaster;

    uint32 _despawnTimer;
};

#endif /* !CLIENTOBJECT_H_ */
