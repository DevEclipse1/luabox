local map = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
}

local map_width = 9
local map_height = 9

local player = {}
player.x = 6.0
player.y = 6.0
player.dir_x = -1.0
player.dir_y = 0.0

local plane_x = 0
local plane_y = 0.66

local display_size = DisplaySize()

while true do
    DisplayClear()
    
    if ButtonDown("UP") then
        player.x = player.x - 0.05 
    end
    
    if ButtonDown("DOWN") then
        player.x = player.x + 0.05 
    end
    
    for x = 0, display_size.x, 1 do
        local cam_x = 2 * x / display_size.x - 1;
        local ray_dir_x = player.dir_x + plane_x * cam_x
        local ray_dir_y = player.dir_y + plane_y * cam_x
        
        local map_x = math.floor(player.x)
        local map_y = math.floor(player.y)
        
        local delta_dist_x = (ray_dir_x == 0) and math.huge or math.abs(1 / ray_dir_x)
        local delta_dist_y = (ray_dir_y == 0) and math.huge or math.abs(1 / ray_dir_y)
        
        local side_dist_x = 0.0
        local side_dist_y = 0.0
        
        local step_x = 0
        local step_y = 0
        
        local hit = false
        local side = 0
        
        if ray_dir_x < 0 then
            step_x = -1;
            side_dist_x = (player.x - map_x) * delta_dist_x
        else
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x
        end
        
        if ray_dir_y < 0 then
            step_y = -1;
            side_dist_y = (player.y - map_y) * delta_dist_y
        else
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y
        end
        
        while hit == false do
            if side_dist_x < side_dist_y then
                side_dist_x = side_dist_x + delta_dist_x
                map_x = map_x + math.floor(step_x)
                side = 0
            else
                side_dist_y = side_dist_y + delta_dist_y
                map_y = map_y + math.floor(step_y)
                side = 1
            end
            
            if (map[map_x][map_y] > 0) then hit = 1 end
        end
        
        local perp_wall_dist = 0
        
        if side == 0 then perp_wall_dist = (side_dist_x - delta_dist_x)
        else perp_wall_dist = (side_dist_y - delta_dist_y) end
        
        local height =display_size.y / perp_wall_dist
        local draw_start = -height / 2 + display_size.y / 2
        if draw_start < 0 then draw_start = 0 end
        local draw_end = height / 2 + display_size.y / display_size.y
        if draw_end >= display_size.y then draw_end = display_size.y - 1 end
        
        DisplayLineV(math.floor(draw_start), math.floor(draw_end), math.floor(height), 0xffff)
    end
    
    DisplayDraw()
    Sleep(16)
end