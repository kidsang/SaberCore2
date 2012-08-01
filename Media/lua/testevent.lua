
function toString(num)
	return string.format("%d", num)
end


--router = scEventRouter:getSingletonPtr()
function registerEntry(gw)
	scErrMsg('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11')
	router = getEventRouter()
	router:registerEvent("test", gw:getEventQueueName())
	router:registerEvent("test2", gw:getEventQueueName())
	router:registerEvent("gui_mouse_over", gw:getEventQueueName())
	scErrMsg('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11')
end

function callbackEntry(evt)
	scErrMsg(evt:getName())
	name = evt:getName()
	if name == "test" or name == "gui_mouse_over" then
		scErrMsg(evt:getString("msg")..toString(evt:getI32("x"))..","
		..toString(evt:getI32("y")))
	elseif name == "test2" then
		scErrMsg(toString(evt:getI32("time")))
	end
end
