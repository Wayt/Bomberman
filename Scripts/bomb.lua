#!/usr/bin/lua5.1

local timer = 0
function LoadScript(me)
    Log:print("LoadScript !")
    timer = 5000
end

function UpdateAI(me, diff)
    if timer <= diff then
        me:Despawn()
        Log:print("Remove !")
    else
        timer = timer - diff
    end
end
