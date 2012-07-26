
function toString(num)
	return string.format("%d", num)
end

function onMouseMoved( arg )
	testPrint(toString(arg.state.X.abs)..','..toString(arg.state.Y.abs))
end
