#!/usr/bin/lua5.1

local tosafe = 0
local movetimer = 0
function LoadScript(me)
	-- Log:print("LoadScript !")
	pl = me:FindNearestPlayer()
	if pl then
		me:MovePointTarget(pl)
	end
end

function UpdateAI(me, diff)
	if movetimer > 0 then
		if movetimer <= diff then
			mov = me:IsMoving()
			if mov == false then
				pl = me:FindNearestPlayer()
			end
			if pl then
				me:MovePointTarget(pl)
				movetimer = 0
			else
				movetimer = 1000
			end
		else
			movetimer = movetimer - diff
		end
	end
	if me:IsPositionSafe() == false then
		-- Log:print("Position pas safe !")
		if tosafe == 0 then
			if me:MoveToSafePosition() == true then
				tosafe = 1
			end
		end
	else
		-- Log:print("Position SAFE !")
		if me:HasPlayerInRange(me:GetBombRange()) == true then
			me:DropBombIfPossible()
		elseif me:FindNearestPlayer() == nil then
			me:DropBombIfPossible()
			me:MoveTosafePosition()
			tosafe = 1
		end
	end
end

function HandleHit(me, by)
	-- Log:print("Boum by other");
	me:Kill(by)
end

function HandleRespawn(me)
	-- Log:print("Handle Respawn !")
	tosafe = 0
	pl = me:FindNearestPlayer()
	if pl then
		me:MovePointTarget(pl)
	end
end

function HandlePathGenerated(me)
	-- Log:print("Path Generated !")
end

function HandleFailToCreatePath(me)
	-- Log:print("Fail to create path !")
	tosafe = 0
end

function HandleFinishMovePoint(me)
	-- Log:print("Finish move point !")
	if tosafe == 0 then
		me:DropBombIfPossible()
	else
		movetimer = 3000
	end
	tosafe = 0
end

function HandleBombBoum(me)
	pl = me:FindNearestPlayer()
	if pl then
		me:MovePointTarget(pl)
	end
end
