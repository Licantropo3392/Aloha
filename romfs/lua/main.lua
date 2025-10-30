package.path = package.path .. ";../src/lua/?.lua;../src/lua/rendering/?.lua"

local Aloha = require('Aloha')
-- package.loaded["Aloha"] = nil

function Init()
    window = Aloha.Window:New(800, 480, 60, "TESTING")

    rect = Aloha.Rectangle:New(1, 1, 1, 1, Aloha.Color:New(0, 121, 241))
    circle = Aloha.Circle:New(window.width / 2, window.height / 2, window.height / 2, Aloha.Color:New(255, 161, 0))

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