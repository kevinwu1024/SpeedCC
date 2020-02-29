/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "SCLanguage.h"
#include "SCSystem.h"
#include "../base/SCBaseMacros.h"
#include "../stage/SCMessageDispatch.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

SCLanguage* SCLanguage::_pInstance = NULL;
bool SCLanguage::_bEnableSearchPath = false;

SCLanguage::SCLanguage()
:_currentLang(ELanguageType::kEnglish)
,_bCacheEnable(true)
,_bLoaded(false)
{
}

SCLanguage* SCLanguage::getInstance()
{
    if(_pInstance==NULL)
    {
        _pInstance = new SCLanguage();
    }
    
    return _pInstance;
}

void SCLanguage::setLanguageAssetSearchPath(bool bEnable)
{
    SCLanguage::_bEnableSearchPath = bEnable;
}

bool SCLanguage::getLanguageAssetSearchPath()
{
    return SCLanguage::_bEnableSearchPath;
}

void SCLanguage::setCacheEnable(const bool bEnable)
{
    SC_RETURN_V_IF(bEnable==_bCacheEnable);
    
    if(bEnable)
    {
        this->loadLanguageText(_currentLang);
    }
    else
    {
        _cacheLanguageID2TextDic.removeAllKeys();
    }
    
    _bCacheEnable = bEnable;
}

void SCLanguage::purgeCache()
{
    _cacheLanguageID2TextDic.removeAllKeys();
}

bool SCLanguage::setCurrentLanguage(const ELanguageType language)
{
    SC_RETURN_IF(_currentLang==language, true);
    
    auto preLanguage = _currentLang;
    _currentLang = language;
    _cacheLanguageID2TextDic.removeAllKeys();
    _bLoaded = false;
    if(_bCacheEnable)
    {
        this->loadLanguageText(language);
    }
    
    // spawn language changed message
    SCMessage::Ptr ptrMsg = SCMessage::create();
    
    ptrMsg->nMsgID = SCID::Msg::kMsgLanguageChanged;
    ptrMsg->parameters.setValue(SC_KEY_LANGUAGE_PRE,preLanguage);
    ptrMsg->parameters.setValue(SC_KEY_LANGUAGE_CUR,_currentLang);
    
    SCMsgDisp()->postMessage(ptrMsg);
    
    return true;
}

void SCLanguage::loadCache()
{
    this->loadLanguageText(_currentLang);
}

void SCLanguage::loadLanguageText(ELanguageType lang)
{
    _cacheLanguageID2TextDic.removeAllKeys();
    auto strLangFolder = SCSystem::getSpeedCCOption(SC_OPTION_KEY_FOLDEROFLANGUAGE).getString();
    
    SCString strLangFileName = strLangFolder + "/" + this->getLanguageShortName(lang) + ".json";
    auto strFile = FileUtils::getInstance()->fullPathForFilename(strLangFileName.c_str());
    if(!FileUtils::getInstance()->isFileExist(strFile.c_str()))
    {
        SCLog("cannot found file: %s",strLangFileName.c_str());
        return;
    }
       
    auto data = FileUtils::getInstance()->getDataFromFile(strFile.c_str());
    SCString str(data.getBytes(),(int)data.getSize());
    _cacheLanguageID2TextDic.loadFromJsonString(str);
    _bLoaded = true;
}

SCString SCLanguage::getString(const SCString strID)
{
    if(!_bLoaded)
    {
        this->loadLanguageText(_currentLang);
    }
    auto value = _cacheLanguageID2TextDic[strID];
    if(value.getType() == SCValue::kTypeString)
    {
        return value.getString();
    }
    
    return "";
}

SCString SCLanguage::getLanguageShortName(const ELanguageType language) const
{
    switch(language)
    {
        case ELanguageType::kEnglish:      return "ENU";
        case ELanguageType::kChinese:      return "CHN";
        case ELanguageType::kFrench:       return "FRA";
        case ELanguageType::kItalian:      return "ITA";
        case ELanguageType::kGerman:       return "DEU";
        case ELanguageType::kSpanish:      return "ESP";
        case ELanguageType::kDutch:        return "DUT";
        case ELanguageType::kRussian:      return "RUS";
        case ELanguageType::kKorean:       return "KOR";
        case ELanguageType::kJapanese:     return "JPN";
        case ELanguageType::kHungarian:    return "HUN";
        case ELanguageType::kPortuguese:   return "PRT";
        case ELanguageType::kArabic:       return "SAU";
        case ELanguageType::kNorwegian:    return "NOR";
        case ELanguageType::kPolish:       return "POL";
        default: SCASSERT(false);  return "";
    }
    return "";
}

SCString SCLanguage::getCurrentLanguageShortName() const
{
    return this->getLanguageShortName(_currentLang);
}


NAMESPACE_SPEEDCC_END
