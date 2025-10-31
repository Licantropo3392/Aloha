-- local Clamp = require("Utils").Clamp

Color = {r = 255, g = 255, b = 255, a = 255}
Color.__index = Color

function Color:New(r, g, b, a)
    local o = {
        r = Utils.Clamp(r or 255, 0, 255),
        g = Utils.Clamp(g or 255, 0, 255),
        b = Utils.Clamp(b or 255, 0, 255),
        a = Utils.Clamp(a or 255, 0, 255)
    }
    return setmetatable(o, Color)
end

function Color:White()
    return Color:New(255, 255, 255, 255)
end
