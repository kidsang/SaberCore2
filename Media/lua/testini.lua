
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
    -- test animation
    tlmgr = getTimeLineManager()
    tl = tlmgr:getTimeLine('Animation')
    animgr = getAnimationManager()
    anig = animgr:createUiAnimationGroup()
    ani = animgr:createUiAlphaAnimation(true)
    ani:createKeyFrame(0, 1, scKeyFrame.IT_LINEAR)
    ani:createKeyFrame(1000, 0, scKeyFrame.IT_LINEAR)
    ani:createKeyFrame(2000, 1, scKeyFrame.IT_LINEAR)
    anig:addAnimation(ani)
    --ani = animgr:createUiTranslateAnimation(true)
    --ani:createKeyFrame(0, 0, 0, scKeyFrame.IT_LINEAR)
    --ani:createKeyFrame(1000, 100, 0, scKeyFrame.IT_LINEAR)
    --ani:createKeyFrame(2000, 0, 0, scKeyFrame.IT_LINEAR)
    --anig:addAnimation(ani)
    ani = animgr:createUiRotateAnimation(true)
    ani:createKeyFrame(0, 0, 0.5, 0.5, scKeyFrame.IT_LINEAR)
    ani:createKeyFrame(2000, 6.28, 0.5, 0.5, scKeyFrame.IT_LINEAR)
    anig:addAnimation(ani)
    ani = animgr:createUiScaleAnimation(true)
    ani:createKeyFrame(0, 1, 1, 0.5, 0.5, scKeyFrame.IT_LINEAR)
    ani:createKeyFrame(1000, 2, 2, 0.5, 0.5, scKeyFrame.IT_LINEAR)
    ani:createKeyFrame(2000, 1, 1, 0.5, 0.5, scKeyFrame.IT_LINEAR)
    anig:addAnimation(ani)
    s:bindGuiAnimation('testimg', anig)
    tl:addAnimation(anig)

end


