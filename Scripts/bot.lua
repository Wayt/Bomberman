#!/usr/bin/lua5.1

function LoadScript(me)
    Log:print("LoadScript !")
    pl = me:FindNearestPlayer()
    me:MovePoint(pl:GetPositionX(), pl:GetPositionY())
end

function UpdateAI(me, diff)
    --if me:IsPositionSafe() == false then
    --    Log:print("Position pas safe !")
    --else
    --    Log:print("Position SAFE !")
    --end
end

function HandleHit(me, by)
    Log:print("Boum by other");
    me:Kill(by)
end

function HandleRespawn(me)
    Log:print("Handle Respawn !")

    pl = me:FindNearestPlayer()
    me:MovePoint(pl:GetPositionX(), pl:GetPositionY())
end

function HandlePathGenerated(me)
    Log:print("Path Generated !")
end

function HandleFailToCreatePath(me)
    Log:print("Fail to create path !")
end

function HandleFinishMovePoint(me)
    Log:print("Finish move point !")
end
