
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:foo()
	local kk
	for i = 1, 1000 do
		kk = sc.SCDateTime:create()
	end
end

function MainScene:onCreate()
    -- add background image
    -- display.newSprite("HelloWorld.png")
    --     :move(display.center)
    --     :addTo(self)
    -- self:foo()
    local value = sc.SCValue:create()
    local dt = sc.SCDateTime:create()
    local date = sc.SCDateTime.Date:create()

    value:assign(dt)
    local kk = value:getDateTime():getFormatString()--dt:getFormatString()
    dt:getTime()

    -- add HelloWorld label
    local label = cc.Label:createWithSystemFont(kk, "Arial", 40)
				    	:setTextColor(cc.c4b(255,0,0,255))
				        :move(display.cx, display.cy + 200)
				        :addTo(self)

    value:setObject(label)
    local label2 = value:getObject("cc.Label")
    label2:setString(tostring(date.year))

end

return MainScene
