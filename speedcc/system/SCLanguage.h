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



#ifndef __SPEEDCC__SCLANGUAGEH__
#define __SPEEDCC__SCLANGUAGEH__

#include "../base/SCBaseMacros.h"
#include "../base/SCString.h"
#include "../base/SCDictionary.h"

NAMESPACE_SPEEDCC_BEGIN

class SCLanguage
{
public:
    enum class ELanguageType
    {
        kEnglish = 0,
        kChinese,
        kFrench,
        kItalian,
        kGerman,
        kSpanish,
        kDutch,
        kRussian,
        kKorean,
        kJapanese,
        kHungarian,
        kPortuguese,
        kArabic,
        kNorwegian,
        kPolish,
        kTurkish,
        kUkrainian,
        kRomanian,
        kBulgarian
    };
    
public:
    SC_AVOID_CLASS_COPY(SCLanguage)
    
    static SCLanguage* getInstance();
    static void setLanguageAssetSearchPath(bool bEnable);
    static bool getLanguageAssetSearchPath();
    
    void setCacheEnable(const bool bEnable);
    void purgeCache();
    void loadCache();
    inline ELanguageType getCurrentLanguage() const {return _currentLang;}
    
    bool setCurrentLanguage(const ELanguageType);
    SCString getString(const SCString strID);
    SCString getLanguageShortName(ELanguageType) const;
    SCString getCurrentLanguageShortName() const;
    
protected:
    SCLanguage();
    void loadLanguageText(ELanguageType lang);
    
private:
    static bool                 _bEnableSearchPath;
    bool                        _bCacheEnable;
    bool                        _bLoaded;
    ELanguageType               _currentLang;
    SCDictionary                _cacheLanguageID2TextDic;
    static SCLanguage*          _pInstance;
};

NAMESPACE_SPEEDCC_END

#endif
