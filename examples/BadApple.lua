local gif = GifCreate("/assets/badapple.gif", 0, 0)
gif:PlayAsync()

while not ButtonDown("SET") and not ButtonDown("GET") do
    Sleep(1)
end

gif:Stop()

ButtonWaitRelease("SELECT")