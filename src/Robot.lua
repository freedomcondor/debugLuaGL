local Qua = require("Quaternion")
local DirPartical = require("DirPartical")
local Robot = {CLASSRobot = true}
Robot.__index = Robot
setmetatable(Robot,DirPartical)
	-- Robot is son class of DirPartical

--[[
	Robot has 
		what ever DirPartical has
			(w,wa,dirFront,dirUp,l,v,a  which are all vector )
		dirFront   	point front
		dirUp		point up
		w			a rotate vector
		wa			a acc rotate vector
--]]

function Robot:create(x,y,z,a,b,c,p,q,r)
	local instance = DirPartical:create(x,y,z,a,b,c,p,q,r)
	setmetatable(instance,self)
	return instance
end

function Robot:forward(x)
	if type(x)~= "number" then return -1 end

	local dir = self.dirFront:nor()
	dir = dir * x
	self.v = dir
	return 0
end

function Robot:turn(x)
	if type(x)~= "number" then return -1 end

	local dir = self.dirUp:nor()
	dir = dir * x
	self.w = dir
	return 0
	
end

--[[
function Robot:run(time)
	DirPartical.run(self,time)
end
--]]

return Robot
