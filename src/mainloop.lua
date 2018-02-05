luaDir = ';../src/'
luaPath = '?.lua'
mathPath = 'math/?.lua'
package.path = package.path .. luaDir .. luaPath
package.path = package.path .. luaDir .. mathPath
require("debugger")

--local Partical = require("Partical")
--local DirPartical = require("DirPartical")
local Robot = require("Robot")

local a

function init()
	a = Robot:create(	0,0,0
				    	--0,1,0,
					    --1,0,0
							)
end

function step()
	a:run(1)
end

function exit()
	a = nil
end

------------- C interface -------------
function getLX() return a.l.x end
function getLY() return a.l.y end
function getLZ() return a.l.z end
function getDX() return a.dirFront.x end
function getDY() return a.dirFront.y end
function getDZ() return a.dirFront.z end
function getUX() return a.dirUp.x end
function getUY() return a.dirUp.y end
function getUZ() return a.dirUp.z end
function setW(x) a:turn(x) end
function setV(x) a:forward(x) end

--[[
init()
while true do
	step()
end
--]]
