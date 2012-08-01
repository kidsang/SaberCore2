
function toString(num)
	return string.format("%d", num)
end

function onKeyGetFocus(sender, old)
	--scErrMsg(sender:getName()..' get key focus')
end

function onKeyLoseFocus(sender, new)
	--scErrMsg(sender:getName()..' lose key focus')
end

function onKeyPressed(sender, key, ch)
	--scErrMsg(sender:getName()..' key '..toString(key)..' pressed')
end

function onKeyReleased(sender, key)
	--scErrMsg(sender:getName()..' key '..toString(key)..' released')
end

function onMouseGetFocus(sender, old)
	--scErrMsg(sender:getName()..' get mouse focus')
end

function onMouseLoseFocus(sender, new)
	--scErrMsg(sender:getName()..' lose mouse focus')
end

function onMouseMove(sender, left, top)
	--scErrMsg(sender:getName()..' move at '..toString(left)..','..toString(top))
	evt = scEvent("gui_mouse_over")
	evt:putString("msg", "Gui "..sender:getName().." mouse over:")
	evt:putI32("x", left)
	evt:putI32("y", top)
	getEventRouter():putEvent(evt)
end

function onMouseDrag(sender, left, top, id)
	--scErrMsg(sender:getName()..' drag at '..toString(left)..','..toString(top))
end

function onMousePressed(sender, left, top, id)
	--scErrMsg(sender:getName()..' pressed at '..toString(left)..','..toString(top))
end

function onMouseReleased(sender, left, top, id)
	--scErrMsg(sender:getName()..' released at '..toString(left)..','..toString(top))
end

function onMouseClick(sender)
	--scErrMsg(sender:getName()..' clicked')
end

function onMouseDoubleClick(sender)
	--scErrMsg(sender:getName()..' double clicked')
end

