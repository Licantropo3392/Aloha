local Aloha = {}

local Window = require("rendering.Window")
Aloha.Window = Window

local Utils = require("Utils")
Aloha.Utils = Utils

local Color = require("rendering.Color")
Aloha.Color = Color

local Rectangle = require("rendering.Rectangle")
Aloha.Rectangle = Rectangle

local Circle = require("rendering.Circle")
Aloha.Circle = Circle

-- Object = {x = 0, y = 0}

-- function Object:new(x, y)
--     if x == nil then
--         x = self.x
--     end

--     if y == nil then
--         y = self.y
--     end

--     self.x = x
--     self.y = y

--     return self
-- end

return Aloha