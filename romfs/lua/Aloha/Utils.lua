Utils = {}

function Utils.Clamp(value, min, max)
    return math.min(math.max(value, min), max)
end
