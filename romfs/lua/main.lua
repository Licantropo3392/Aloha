Color = require("../romfs/lua/Aloha2D")

function Clamp(value, min, max)
    return math.min(math.max(value, min), max)
end

Window = {width = 800, height = 480, fps = 60, name = "Aloha2D", deltaTime = 0}

function Window:New(width, height, fps, name)
    local o = {
        width = width or self.width,
        height = height or self.height,
        fps = fps or self.fps,
        name = name or self.name
    }
    setmetatable(o, self)
    self.__index = self

    InitWindow(o.width, o.height, o.name)
    SetTargetFPS(o.fps)

    return o
end

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

Rectangle = {x = 0, y = 0, width = 1, height = 1, color = Color:White()}

function Rectangle:New(x, y, width, height, color)
    local o = {
        x = Clamp(x or self.x, 0, window.width - (width or self.width)),
        y = Clamp(y or self.y, 0, window.height - (height or self.height)),
        width = Clamp(width or self.width, 1, window.width),
        height = Clamp(height or self.height, 1, window.height),
        color = color or self.color
    }
    setmetatable(o, self)
    self.__index = self
    return o
end

function Rectangle:SetX(x)
    self.x = Clamp(x, 0, window.width - self.width)
end

function Rectangle:SetY(y)
    self.y = Clamp(y, 0, window.height - self.height)
end

function Rectangle:SetWidth(width)
    self.width = Clamp(width, 1, window.width)
end

function Rectangle:SetHeight(height)
    self.height = Clamp(height, 1, window.height)
end

function Rectangle:Draw()
    DrawRectangle(self.x, self.y, self.width, self.height, self.color)
end

Circle = {x = 0, y = 0, radius = 1, color = Color:White()}

function Circle:New(x, y, radius, color)
    local o = {
        x = Clamp(x or self.x, 0, window.width),
        y = Clamp(y or self.y, 0, window.height),
        radius = Clamp(radius or self.radius, 1, window.width / 2),
        color = color or self.color
    }
    setmetatable(o, self)
    self.__index = self
    return o
end

function Circle:SetX(x)
    self.x = Clamp(x, 0, window.width)
end

function Circle:SetY(y)
    self.y = Clamp(y, 0, window.height)
end

function Circle:SetRadius(radius)
    self.radius = Clamp(radius, 1, window.width / 2 or window.height / 2)
end

function Circle:Draw()
    DrawCircle(self.x, self.y, self.radius, self.color)
end

function Init()
    window = Window:New(800, 480, 60, "TESTING")

    rect = Rectangle:New(1, 1, 1, 1, Color:New(0, 121, 241))
    circle = Circle:New(window.width / 2, window.height / 2, window.height / 2, Color:New(255, 161, 0))

    grow = true
end

function Update()
    if grow and rect.width < window.width and rect.height < window.height then
        rect:SetWidth(rect.width + (window.deltaTime * 100))
        rect:SetHeight(rect.height + (window.deltaTime * 100))
        circle:SetRadius(circle.radius - (window.deltaTime * 50))
    elseif rect.width > 1 and rect.height > 1 then
        grow = false
        rect:SetWidth(rect.width - (window.deltaTime * 100))
        rect:SetHeight(rect.height - (window.deltaTime * 100))
        circle:SetRadius(circle.radius + (window.deltaTime * 50))
    else
        grow = true
    end

    rect:SetX((window.width / 2) - (rect.width / 2))
    rect:SetY((window.height / 2) - (rect.height / 2))

    rect:Draw()
    circle:Draw()
end

function Unload()
    CloseWindow()
end