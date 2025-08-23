function Init()
    print("Hello from Lua!")
    frame = 0
    InitWindow(800, 450, "GAME")
    SetTargetFPS(60)
end

function Update()
    DrawRectangle(400 - (frame / 2), 225 - (frame / 2), frame, frame, {r = 0, g = 121, b = 241, a = 255})
    DrawCircle(400, 225, 225 - frame, {r = 255, g = 161, b = 0, a = 255})

    frame = frame + 1
    -- print(frame)
end

function Unload()
    CloseWindow()
    print("Goodbye from Lua!")
end