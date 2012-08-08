
function iniScene(s)
    --s:import "testevent"
    --registerEntry(s)
    s:iniEvent("testevent.lua", "callbackEntry",
        "testevent.lua", "registerEntry")
    --s:import "testscene"
    --createScene(s)
    s:iniScene("testscene.lua", "createScene")
    --s:import "testinput"
    s:registerMouseMoved("testinput", "onMouseMoved")
    s:registerMousePressed("testinput", "onMousePressed")
    s:iniGui("testguievent.lua", "registerEvents")
end


