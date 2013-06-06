#!/usr/bin/lua5.1

local timer = 0
local used = 0

function LoadScript(me)
    Log:print("LoadScript !")
    timer = 3000
    used = 0
end

function UpdateAI(me, diff)
    if timer > 0 and used == 0 and timer <= diff then
        used = 1
        me:DoAction(1)
        me:Despawn()
        timer = 0
    else
        timer = timer - diff
    end
end

function HandleHit(me, by)
    if used == 0 then
        used = 1
        Log:print("Boum by other");
        me:DoAction(1)
        me:Despawn()
    end
end
