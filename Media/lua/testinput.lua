
function toString(num)
	return string.format("%d", num)
end

function onMouseMoved( arg )
	scErrMsg(toString(arg.state.X.abs)..','..toString(arg.state.Y.abs))
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
