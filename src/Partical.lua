Vec3 = require('Vector3')

local Partical = {CLASSPartical = true}
Partical.__index = Partical

function Partical:create(x,y,z)
	local instance = {}
	setmetatable(instance,self)

	instance.v = Vec3:create(0,0,0);
	instance.a = Vec3:create(0,0,0);

	if type(x) == "table" and x.CLASS == "Vector3" then
		instance.l = Vec3:create(x)
	end

	if type(x) == "table" and x.CLASSPartical == true then
		instance.l = Vec3:create(x.l)
		return instance
	end

	if type(x) == "number" and
	   type(y) == "number" and
	   type(z) == "number" then
		instance.l = Vec3:create(x,y,z)
		return instance
	end

	instance.l = Vec3:create()
	return instance
end

function Partical:setA(x,y,z)
	self.a.x = x
	self.a.y = y
	self.a.z = z
end

function Partical:setV(x,y,z)
	self.v.x = x
	self.v.y = y
	self.v.z = z
end

function Partical:run(time)
	self.l = self.l + self.v * time
	--self.x = self.x + self.vx * time
	--self.y = self.y + self.vy * time
	--self.z = self.z + self.vz * time

	self.v = self.v + self.a * time
	--self.vx = self.vx + self.ax * time
	--self.vy = self.vy + self.ay * time
	--self.vz = self.vz + self.az * time
end

return Partical
