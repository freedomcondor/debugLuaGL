local Qua = require("Quaternion")
local Partical = require("Partical")
local DirPartical = {CLASSDirPartical = true}
DirPartical.__index = DirPartical
setmetatable(DirPartical,Partical)
	-- DirPartical is son class of Partical

--[[
	DirPartical has 
		what ever Partical has
			(l,v,a  which are all vector )
		dirFront   	point front
		dirUp		point up
		w			a rotate vector
		wa			a acc rotate vector
--]]

function DirPartical:create(x,y,z,a,b,c,p,q,r)
	if type(x) == "table" and x.CLASS == "Vector3" or
	   type(x) == "table" and x.CLASSPartical == true then
		local instance = Partical:create(x)
		if (type(y) == "table" and y.CLASS == "Vector3" or
	        type(y) == "table" and y.CLASSPartical == true) and
		   (type(z) == "table" and z.CLASS == "Vector3" or
	        type(z) == "table" and z.CLASSPartical == true) then
		   	instance.dirFront = Vec3:create(y)
		   	instance.dirUp = Vec3:create(z)
		end
	end
	if type(x) == "number" and
	   type(y) == "number" and
	   type(z) == "number" then
		instance = Partical:create(x,y,z)
		if type(a) == "number" and
	   	   type(b) == "number" and
	   	   type(c) == "number" and
		   type(p) == "number" and
	   	   type(q) == "number" and
	   	   type(r) == "number" then
		   	instance.dirFront = Vec3:create(a,b,c)
		   	instance.dirUp = Vec3:create(p,q,r)
		end
	end

	if instance == nil then 
		instance = Partical:create(0,0,0)
	end
	if instance.dirFront == nil then
		instance.dirFront = Vec3:create(1,0,0)
		instance.dirUp = Vec3:create(0,0,1)
	end

	instance.w = Vec3:create()
	instance.wa = Vec3:create()

	setmetatable(instance,self)
	return instance
end

function DirPartical:setW(x,y,z,w)
	if type(x) == "number" and
	   type(y) == "number" and
	   type(z) == "number" and
	   type(w) == "nil" then
		self.w.x = x
		self.w.y = y
		self.w.z = z
	else if type(x) == "number" and
	   		type(y) == "number" and
	   		type(z) == "number" and
	   		type(w) == "number" then
		self.w.x = x
		self.w.y = y
		self.w.z = z
		self.w = self:nor() * w
	end end
end
function DirPartical:setWA(x,y,z,w)
	if type(x) == "number" and
	   type(y) == "number" and
	   type(z) == "number" and
	   type(w) == "nil" then
		self.wa.x = x
		self.wa.y = y
		self.wa.z = z
	else if type(x) == "number" and
	   		type(y) == "number" and
	   		type(z) == "number" and
	   		type(w) == "number" then
		self.wa.x = x
		self.wa.y = y
		self.wa.z = z
		self.wa = self:nor() * w
	end end
end

function DirPartical:run(time)
	Partical.run(self,time)
	local q = Qua:createFromRotation(
										self.w.x,
									 	self.w.y,
										self.w.z,
										math.sqrt(self.w.x^2+
											 	  self.w.y^2+
												  self.w.z^2) * time
									)
	self.dirUp = self.dirUp:rotatedby(q)
	self.dirFront = self.dirFront:rotatedby(q)
	self.w = self.w + self.wa * time
end

return DirPartical
