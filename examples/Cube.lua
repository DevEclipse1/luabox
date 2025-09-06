local display_size = DisplaySize()
local cube_size = 20
local angle_x, angle_y = 0, 0
local scale = 1
local vertices = {
    {x=-1, y=-1, z=-1}, {x=1, y=-1, z=-1}, {x=1, y=1, z=-1}, {x=-1, y=1, z=-1},
    {x=-1, y=-1, z=1}, {x=1, y=-1, z=1}, {x=1, y=1, z=1}, {x=-1, y=1, z=1}
}
local edges = {
    {1,2},{2,3},{3,4},{4,1},
    {5,6},{6,7},{7,8},{8,5},
    {1,5},{2,6},{3,7},{4,8}
}

local function rotate_vertex(v, ax, ay)
    local cosx, sinx = math.cos(ax), math.sin(ax)
    local cosy, siny = math.cos(ay), math.sin(ay)
    local x, y, z = v.x, v.y, v.z

    local y1 = y * cosx - z * sinx
    local z1 = y * sinx + z * cosx
    y, z = y1, z1

    local x1 = x * cosy + z * siny
    local z1b = -x * siny + z * cosy
    x, z = x1, z1b

    return {x=x * cube_size * scale, y=y * cube_size * scale, z=z * cube_size * scale}
end

local function project(v)
    local scale_factor = 200 / (v.z + 200)
    local px = display_size.x // 2 + v.x * scale_factor
    local py = display_size.y // 2 - v.y * scale_factor
    return px, py
end

local function redraw_cube()
    DisplayClear()
    local projected = {}
    for i,v in ipairs(vertices) do
        projected[i] = {project(rotate_vertex(v, angle_x, angle_y))}
    end
    for _,edge in ipairs(edges) do
        local x1, y1 = projected[edge[1]][1], projected[edge[1]][2]
        local x2, y2 = projected[edge[2]][1], projected[edge[2]][2]
        local dx, dy = x2-x1, y2-y1
        local steps = math.max(math.abs(dx), math.abs(dy))
        for i=0,steps do
            local px = math.floor(x1 + dx * i / steps)
            local py = math.floor(y1 + dy * i / steps)
            DisplayPixel(px, py, 0xF800)
        end
    end

    DisplayDraw()
end

redraw_cube()

while true do
    local hold_set = ButtonDown("SET")
    local changed = false

    if ButtonDown("UP") then
        if hold_set then
            scale = math.min(scale + 0.05, 5)
            changed = true
        else
            angle_x = angle_x + 0.05
            changed = true
        end
    elseif ButtonDown("DOWN") then
        if hold_set then
            scale = math.max(scale - 0.05, 0.1)
            changed = true
        else
            angle_x = angle_x - 0.05
            changed = true
        end
    end
    if ButtonDown("LEFT") and not hold_set then
        angle_y = angle_y + 0.05
        changed = true
    elseif ButtonDown("RIGHT") and not hold_set then
        angle_y = angle_y - 0.05
        changed = true
    end

    if changed then
        redraw_cube()
    end

    Sleep(16)
end
