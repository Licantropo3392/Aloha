Window = {width = 800, height = 480, fps = 60, name = "Aloha", deltaTime = 0}

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
