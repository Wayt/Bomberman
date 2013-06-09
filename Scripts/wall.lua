#!/usr/bin/lua5.1

function LoadScript(me)
    -- Log:print("LoadScript !")
end

function UpdateAI(me, diff)
end

function HandleHit(me, by)
    -- Log:print("Wall get hit")
    me:SpawnBonus()
    me:Despawn()
end
