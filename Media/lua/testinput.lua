
function toString(num)
	return string.format("%d", num)
end

function onMouseMoved( arg )
	evt = scEvent("test")
	evt:putString("msg", "From Lua: Mouse")
	evt:putI32("x", arg.state.X.abs)
	evt:putI32("y", arg.state.Y.abs)
	getEventRouter():putEvent(evt)
	--scErrMsg(toString(arg.state.X.abs)..','..toString(arg.state.Y.abs))
end

function onMousePressed( arg )
	if arg.state:buttonDown(MouseEvent.MB_Left) then
		scErrMsg('left button down!')
	end
	if arg.state:buttonDown(MouseEvent.MB_Right) then
		scErrMsg('right button down!')
	end
end

function onKeyPressed(arg)
	if arg.key == KeyEvent.KC_F then
		scErrMsg('Key F is down!')
	end
end
