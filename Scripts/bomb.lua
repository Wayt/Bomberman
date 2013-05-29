#!/usr/bin/lua5.1

local timer = 0
local despawn_timer = 0
local used = 0

function LoadScript(me)
    Log:print("LoadScript !")
    timer = 5000
    despawn_timer = 50000
    used = 0
end

function UpdateAI(me, diff)
    if timer > 0 and used == 0 and timer <= diff then
        used = 1
        me:DoAction(1)
        timer = 0
        despawn_timer = 100
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

function HandleHit(me, by)
    if used == 0 then
        used = 1
        Log:print("Boum by other");
        me:DoAction(1)
        despawn_timer = 100
    end
end
