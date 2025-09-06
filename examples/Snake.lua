local display_size = DisplaySize()
local grid_size = 4
local snake = {}
local snake_length = 5
local direction = "RIGHT"
local food = {}
local colors = {0xF800, 0xF810, 0xF820, 0xF830, 0xF840, 0xF850, 0xF860}

local function snap_to_grid(x, y)
    return math.floor(x / grid_size) * grid_size, math.floor(y / grid_size) * grid_size
end

local function spawn_food()
    food.x = math.random(0, display_size.x // grid_size - 1) * grid_size
    food.y = math.random(0, display_size.y // grid_size - 1) * grid_size
end

local function init_snake()
    snake = {}
    local start_x, start_y = snap_to_grid(display_size.x // 2, display_size.y // 2)
    for i = 0, snake_length - 1 do
        table.insert(snake, {x = start_x - i * grid_size, y = start_y})
    end
end

init_snake()
spawn_food()

local function redraw()
    DisplayClear()
    for i, segment in ipairs(snake) do
        local color = colors[(i - 1) % #colors + 1]
        for x = 0, grid_size - 1 do
            for y = 0, grid_size - 1 do
                DisplayPixel(segment.x + x, segment.y + y, color)
            end
        end
    end
    for x = 0, grid_size - 1 do
        for y = 0, grid_size - 1 do
            DisplayPixel(food.x + x, food.y + y, 0x07E0)
        end
    end

    DisplayDraw()
end

while true do
    if ButtonDown("UP") and direction ~= "DOWN" then
        direction = "UP"
    elseif ButtonDown("DOWN") and direction ~= "UP" then
        direction = "DOWN"
    elseif ButtonDown("LEFT") and direction ~= "RIGHT" then
        direction = "LEFT"
    elseif ButtonDown("RIGHT") and direction ~= "LEFT" then
        direction = "RIGHT"
    end

    local head = {x = snake[#snake].x, y = snake[#snake].y}

    if direction == "UP" then
        head.y = head.y - grid_size
    elseif direction == "DOWN" then
        head.y = head.y + grid_size
    elseif direction == "LEFT" then
        head.x = head.x - grid_size
    elseif direction == "RIGHT" then
        head.x = head.x + grid_size
    end

    if head.x < 0 then head.x = display_size.x - grid_size end
    if head.y < 0 then head.y = display_size.y - grid_size end
    if head.x >= display_size.x then head.x = 0 end
    if head.y >= display_size.y then head.y = 0 end

    table.insert(snake, head)

    if head.x == food.x and head.y == food.y then
        snake_length = snake_length + 1
        spawn_food()
    end

    while #snake > snake_length do
        table.remove(snake, 1)
    end

    for i = 1, #snake - 1 do
        if snake[i].x == head.x and snake[i].y == head.y then
            snake_length = 5
            direction = "RIGHT"
            init_snake()
            spawn_food()
            break
        end
    end

    redraw()
    Sleep(100)
end