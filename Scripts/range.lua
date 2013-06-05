#!/usr/bin/lua5.1

function LoadScript(me)
    -- Log:print("LoadScript !")
end

local timer = 200
function UpdateAI(me, diff)
    if timer <= diff then
        me:CheckBonusCross(2)
        timer = 200
    else
        timer = timer - diff;
    end
end

function HandleHit(me, by)
    Log:print("Range catch")
    me:Despawn()
end

function HandleCross(me, by)
    Log:print("CROSSED")
end
