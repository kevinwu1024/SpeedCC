
function scN2SViewControllerOnCreate(viewController, parameter)
	if(viewController == nil) then
		return
	end

	if(viewController.onCreate ~= nil) then
		viewController:onCreate(parameter)
	end
end

function scN2SViewControllerOnSCMessageProcess(viewController, parameter)
	if(viewController == nil) then
		return
	end

	if(viewController.onSCMessageProcess ~= nil) then
		return viewController:onSCMessageProcess(parameter)
	end

	return true
end


