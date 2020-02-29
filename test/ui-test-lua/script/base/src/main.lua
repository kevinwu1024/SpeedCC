
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath(cc.FileUtils:getInstance():getWritablePath() .. "script/base/res/")
cc.FileUtils:getInstance():addSearchPath(cc.FileUtils:getInstance():getWritablePath() .. "script/base/src/")

require "config"
require "cocos.init"

local function main()
    require("app.MyApp"):create():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end

