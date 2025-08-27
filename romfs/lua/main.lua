function Init()
    width = 800
    height = 480

    frame = 0
    
    InitWindow(width, height, "GAME")
    SetTargetFPS(120)
end

function Update()
    if (width / 2 - (frame / 2) < 0 or height / 2 - (frame / 2) < 0) then
        frame = 0
    end

    DrawRectangle(width / 2 - (frame / 2), height / 2 - (frame / 2), frame, frame, {r = 0, g = 121, b = 241, a = 255})
    DrawCircle(width / 2, height / 2, 120 - frame, {r = 255, g = 161, b = 0, a = 255})

    frame = frame + 1
end

function Unload()
    CloseWindow()
end