local Color = require("rendering.Color")

local Circle = {x = 0, y = 0, radius = 1, color = Color:White()}

function Circle:New(x, y, radius, color)
    local o = {
        x = x or self.x,
        y = y or self.y,
        radius = radius or self.radius,
        color = color or self.color
    }
    setmetatable(o, self)
    self.__index = self
    return o
end

function Circle:SetX(x)
    self.x = x
end

function Circle:SetY(y)
    self.y = y
end

function Circle:SetRadius(radius)
    self.radius = radius
end

function Circle:Draw()
    DrawCircle(self.x, self.y, self.radius, self.color)
end

return Circle