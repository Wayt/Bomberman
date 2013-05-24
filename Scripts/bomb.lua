#!/usr/bin/lua5.1

local timer = 0
local despawn_timer = 0

function LoadScript(me)
    Log:print("LoadScript !")
    timer = 5000
    despawn_timer = 50000
end

function UpdateAI(me, diff)
    if timer > 0 and timer <= diff then
        me:DoAction(1)
        timer = 0
        despawn_timer = 1000
    else
        timer = timer - diff
    end

    if despawn_timer > 0 and despawn_timer <= diff then
        me:Despawn()
        Log:print("Remove !")
        despawn_timer = 0
    else
        despawn_timer = despawn_timer - diff
    end
end
