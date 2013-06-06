#!/usr/bin/lua5.1

function LoadScript(me)
    Log:print("LoadScript !")
end

function UpdateAI(me, diff)
end

function HandleHit(me, by)
    Log:print("Boum by other");
    me:Kill(by)
end

function HandleRespawn(me)
    Log:print("Handle Respawn !")
    me:MovePoint(5, 5)
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
