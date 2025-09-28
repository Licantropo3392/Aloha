Aloha2D = {}

Color = {r = 255, g = 255, b = 255, a = 255}
Color.__index = Color

function Color:New(r, g, b, a)
    local o = {
        r = Clamp(r or 255, 0, 255),
        g = Clamp(g or 255, 0, 255),
        b = Clamp(b or 255, 0, 255),
        a = Clamp(a or 255, 0, 255)
    }
    return setmetatable(o, Color)
end

function Color:White()
    return Color:New(255, 255, 255, 255)
end

return Aloha2D