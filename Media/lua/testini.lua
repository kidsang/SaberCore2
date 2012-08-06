
function iniScene(s)
    s:import "testevent"
    registerEntry(s)
    s:import "testscene"
    createScene(s)
    --s:import "testinput"
    s:registerMouseMoved("testinput", "onMouseMoved")
    s:registerMousePressed("testinput", "onMousePressed")
end


