
function createScene( s )
	cam = s:addCamera("MyCamera")
	cam:setPosition(Vector3(0, 0, 80))
	cam:lookAt(Vector3(0, 0, -300))
	s:addViewport("Origin", "MyCamera")
	s:addViewport("lt", "MyCamera", 0, 0, 0.4, 0.4)
	s:addViewport("lt2", "MyCamera", 0.2, 0.2, 0.6, 0.6)
	s:addStatic("ogrehead.mesh", Vector3(0.0), Quaternion(Radian(1), Vector3(0, 1, 0)), Vector3(1.0))
	--makelove(1, 2, 3)
	--Vector3(0)
end
