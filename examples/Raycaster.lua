local map = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
}

local player = {x = 6.0, y = 6.0, dir_x = -1.0, dir_y = 0.0}
local plane_x, plane_y = 0, 0.66
local display_size = DisplaySize()
<<<<<<< HEAD
local move_speed, rot_speed = 0.08, 0.15
=======
local move_speed, rot_speed = 0.05, 0.05
>>>>>>> b81d0539ed15e15538464c4933a6f111a2331451
local map_size = 9
local minimap_scale = 2
local minimap_offset_x, minimap_offset_y = 2, 2

while true do
    DisplayClear()
    local px, py = player.x, player.y
    local dx, dy = player.dir_x, player.dir_y
    local plx, ply = plane_x, plane_y

    if ButtonDown("UP") then
        local nx, ny = px + dx * move_speed, py + dy * move_speed
        if map[math.floor(ny) + 1][math.floor(nx) + 1] == 0 then
            player.x, player.y = nx, ny
            px, py = nx, ny
        end
    end
    if ButtonDown("DOWN") then
        local nx, ny = px - dx * move_speed, py - dy * move_speed
        if map[math.floor(ny) + 1][math.floor(nx) + 1] == 0 then
            player.x, player.y = nx, ny
            px, py = nx, ny
        end
    end
    if ButtonDown("LEFT") then
        local old_dx = dx
        dx = dx * math.cos(rot_speed) - dy * math.sin(rot_speed)
        dy = old_dx * math.sin(rot_speed) + dy * math.cos(rot_speed)
        local old_plx = plx
        plx = plx * math.cos(rot_speed) - ply * math.sin(rot_speed)
        ply = old_plx * math.sin(rot_speed) + ply * math.cos(rot_speed)
        player.dir_x, player.dir_y, plane_x, plane_y = dx, dy, plx, ply
    end
    if ButtonDown("RIGHT") then
        local old_dx = dx
        dx = dx * math.cos(-rot_speed) - dy * math.sin(-rot_speed)
        dy = old_dx * math.sin(-rot_speed) + dy * math.cos(-rot_speed)
        local old_plx = plx
        plx = plx * math.cos(-rot_speed) - ply * math.sin(-rot_speed)
        ply = old_plx * math.sin(-rot_speed) + ply * math.cos(-rot_speed)
        player.dir_x, player.dir_y, plane_x, plane_y = dx, dy, plx, ply
    end

    for x = 0, display_size.x, 1 do
        local cam_x = 2 * x / display_size.x - 1
        local ray_dx, ray_dy = dx + plx * cam_x, dy + ply * cam_x
        local map_x, map_y = math.floor(px), math.floor(py)
        local delta_x = ray_dx == 0 and math.huge or math.abs(1 / ray_dx)
        local delta_y = ray_dy == 0 and math.huge or math.abs(1 / ray_dy)
        local step_x, step_y = ray_dx < 0 and -1 or 1, ray_dy < 0 and -1 or 1
        local side_dist_x = (ray_dx < 0 and (px - map_x) or (map_x + 1 - px)) * delta_x
        local side_dist_y = (ray_dy < 0 and (py - map_y) or (map_y + 1 - py)) * delta_y
        local hit, side = false, 0

        while not hit do
            if side_dist_x < side_dist_y then
                side_dist_x = side_dist_x + delta_x
                map_x = map_x + step_x
                side = 0
            else
                side_dist_y = side_dist_y + delta_y
                map_y = map_y + step_y
                side = 1
            end
            if map[map_y + 1][map_x + 1] > 0 then
                hit = true
            end
        end

        local perp_dist =
            (side == 0) and (map_x - px + (1 - step_x) / 2) / ray_dx or (map_y - py + (1 - step_y) / 2) / ray_dy
        local line_h = math.floor(display_size.y / perp_dist)
        local draw_start = math.max(0, math.floor(-line_h / 2 + display_size.y / 2))
        local draw_end = math.min(display_size.y - 1, math.floor(line_h / 2 + display_size.y / 2))
        local shade_val = math.max(30, math.floor(255 / (1 + perp_dist)))
        if side == 1 then
<<<<<<< HEAD
            shade_val = math.floor(shade_val * 1.0)
=======
            shade_val = math.floor(shade_val * 1.2)
>>>>>>> b81d0539ed15e15538464c4933a6f111a2331451
        end
        local wall_color = RGB(shade_val, shade_val, shade_val)
        DisplayLineV(x, draw_start, draw_end, wall_color)

        if draw_end < display_size.y - 1 then
<<<<<<< HEAD
            local start_y = draw_end + 1
            local end_y = display_size.y - 1
            local color = RGB(0, 150, 0)
            DisplayLineV(x, start_y, end_y, color)
=======
            local checker_size = 8
            local start_y = draw_end + 1
            local end_y = display_size.y - 1
            local toggle = false
            for y_line = start_y, end_y, checker_size do
                local color = toggle and RGB(0, 200, 0) or RGB(0, 150, 0)
                local y_end_line = math.min(y_line + checker_size - 1, end_y)
                DisplayLineV(x, y_line, y_end_line, color)
                toggle = not toggle
            end
>>>>>>> b81d0539ed15e15538464c4933a6f111a2331451
        end
    end

    for my = 1, map_size do
        for mx = 1, map_size do
            local color = map[my][mx] > 0 and 0xffff or 0x0000
            local px_minimap = minimap_offset_x + (mx - 1) * minimap_scale
            local py_minimap = minimap_offset_y + (my - 1) * minimap_scale
            for dy_mm = 0, minimap_scale - 1 do
                for dx_mm = 0, minimap_scale - 1 do
                    DisplayPixel(px_minimap + dx_mm, py_minimap + dy_mm, color)
                end
            end
        end
    end

    local player_px = minimap_offset_x + px * minimap_scale
    local player_py = minimap_offset_y + py * minimap_scale
    DisplayPixel(math.floor(player_px), math.floor(player_py), RGB(255, 0, 0))

    DisplayDraw()
    Sleep(16)
end
