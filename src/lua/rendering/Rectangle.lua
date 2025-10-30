local Color = require("rendering.Color")

local Rectangle = {x = 0, y = 0, width = 1, height = 1, color = Color:White()}

function Rectangle:New(x, y, width, height, color)
    local o = {
        x = x or self.x,
        y = y or self.y,
        width = width or self.width,
        height = height or self.height,
        color = color or self.color
    }
    setmetatable(o, self)
    self.__index = self
    return o
end

function Rectangle:SetX(x)
    self.x = x
end

function Rectangle:SetY(y)
    self.y = y
end

function Rectangle:SetWidth(width)
    self.width = width
end

function Rectangle:SetHeight(height)
    self.height = height
end

function Rectangle:Draw()
    DrawRectangle(self.x, self.y, self.width, self.height, self.color)
end

return Rectangle