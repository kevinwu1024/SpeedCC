
#include "AppDelegate.h"
#include "cocos2d.h"
#include "SpeedCC.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "lua-support/src/native/SCLuaRegisterAll.h"


// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	WCHAR full_path[512 + 2] = { 0 };
	::GetModuleFileNameW(nullptr, full_path, SC_ARRAY_LENGTH(full_path));
	WCHAR *pUtf16DirEnd = wcsrchr(full_path, L'\\');
	char utf8ExeDir[512] = { 0 };
	::WideCharToMultiByte(CP_UTF8, 0, full_path, pUtf16DirEnd - full_path + 1, utf8ExeDir, sizeof(utf8ExeDir), nullptr, nullptr);
	auto strWritablePath = StringUtils::format("%sResources/", utf8ExeDir);
	FileUtils::getInstance()->setWritablePath(strWritablePath);
#endif
    
    // copy scripts and assets to writable directory
	
	// initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("UITest", cocos2d::Rect(0, 0, 750/2, 1334/2));
#else
        glview = GLViewImpl::create("UITest");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

	SpeedCC::SCSystem::initSpeedCC(SpeedCC::SCSystem::kResolutionBitMaskMedium);

	// 
	auto strSearchPath = StringUtils::format("%s/script/", FileUtils::getInstance()->getWritablePath().c_str());
	FileUtils::getInstance()->addSearchPath(strSearchPath, true);

	// register lua module
	auto engine = LuaEngine::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	lua_State* L = engine->getLuaStack()->getLuaState();
	::lua_module_register(L);

	register_all_packages();

	::scLuaSupportRegisterAll(L);

	engine->executeScriptFile("base/src/main.lua");

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    SCMsgDisp()->sendMessage(SpeedCC::SCID::Msg::kMsgAppEnterBackground);
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    SCMsgDisp()->sendMessage(SpeedCC::SCID::Msg::kMsgAppEnterForeground);
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
