--router = scEventRouter:getSingletonPtr()
function registerEntry(gw)
	scErrMsg('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11')
	router = getEventRouter()
	router:registerEvent("evt1", gw:getEventQueueName())
	router:registerEvent("evt2", gw:getEventQueueName())
	router:registerEvent("evt3", gw:getEventQueueName())
	router:registerEvent("evt4", gw:getEventQueueName())
	router:registerEvent("evt5", gw:getEventQueueName())
	router:registerEvent("evt6", gw:getEventQueueName())
	router:unregisterEvent("evt3")
	router:unregisterEvents(gw:getEventQueueName())
	scErrMsg('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11')
end

function callbackEntry(evt)

end
