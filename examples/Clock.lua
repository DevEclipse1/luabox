function formatTime(ms)
    local totalSeconds = math.floor(ms / 1000)
    local minutes = math.floor(totalSeconds / 60)
    local seconds = totalSeconds % 60
    local milliseconds = ms % 1000
    return string.format("%02d:%02d.%03d", minutes, seconds, milliseconds)
end

while true do
    DisplayClear()

    local elapsed = ScriptMillis()
    local timeStr = formatTime(elapsed)

    local x = 10
    local y = 10
    local color = 0xffff
    DisplayPrint(timeStr, x, y, color)

    DisplayDraw()
    Sleep(10)
end
