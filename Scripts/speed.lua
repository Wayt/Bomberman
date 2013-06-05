#!/usr/bin/lua5.1

function LoadScript(me)
    -- Log:print("LoadScript !")
end

function UpdateAI(me, diff)
end

function HandleHit(me, by)
    Log:print("Speed catch")
    me:Despawn()
end

function HandleCross(me, by)
    Log:print("CROSSED")
    by:SetSpeed(1.5)
    me:Despawn()
end
