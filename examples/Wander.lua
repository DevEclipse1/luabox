local guy_x = 50
local guy_y = 50
local guy_size = 3

local function redraw()
    DisplayClear()
    DisplayPrint("LUABOX TEST", 0, 0, 0x781f)
    for x = -guy_size, guy_size do
        for y = -guy_size, guy_size do
            DisplayPixel(guy_x + x, guy_y + y, 0x551b)
        end
    end

    DisplayDraw()
end

redraw()

while true do
    if ButtonDown("UP") then
        guy_y = guy_y - 1
        Sleep(5)
    elseif ButtonDown("DOWN") then
        guy_y = guy_y + 1
        Sleep(5)
    elseif ButtonDown("LEFT") then
        guy_x = guy_x - 1
        Sleep(5)
    elseif ButtonDown("RIGHT") then
        guy_x = guy_x + 1
        Sleep(5)
    end

    if ButtonDown("SET") then
        DisplayBacklight(64)
    elseif ButtonDown("GET") then
        DisplayBacklight(128)
    else
        DisplayBacklight(255)
    end

    if ButtonDown("SELECT") then
        if guy_size == 3 then
            guy_size = 6
        else
            guy_size = 3
        end
        ButtonWaitRelease("SELECT")
    end

    local display_size = DisplaySize()

    if guy_x < guy_size then
        guy_x = guy_size
    elseif guy_x > display_size.x - guy_size then
        guy_x = display_size.x - guy_size
    end

    if guy_y < guy_size then
        guy_y = guy_size
    elseif guy_y > display_size.y - guy_size then
        guy_y = display_size.y - guy_size
    end

    redraw()
    Sleep(16)
end