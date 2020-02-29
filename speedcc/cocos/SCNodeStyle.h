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

#ifndef __SPEEDCC__SCNODEPROPERTY_H__
#define __SPEEDCC__SCNODEPROPERTY_H__

#include "cocos2d.h"
#include "../base/SCDictionary.h"

NAMESPACE_SPEEDCC_BEGIN

// for better search algorithm, must keep macro name match string value
#define SC_STYLE_TAG                "tag"           // int
#define SC_STYLE_X                  "x"             // float
#define SC_STYLE_Y                  "y"             // float
#define SC_STYLE_Z_ORDER            "z-order"       // int
#define SC_STYLE_ANCHOR             "anchor"        // Vec2
#define SC_STYLE_ANCHOR_ON          "anchor-on"     // bool
#define SC_STYLE_SCALE              "scale"         // float
#define SC_STYLE_SCALE_X            "scale-x"       // float
#define SC_STYLE_SCALE_Y            "scale-y"       // float
#define SC_STYLE_OPACITY            "opacity"       // float
#define SC_STYLE_VISIBLE            "visible"       // bool
#define SC_STYLE_ROTATION           "rotation"      // float
#define SC_STYLE_ROTATION_X         "rotation-x"    // float
#define SC_STYLE_ROTATION_Y         "rotation-y"    // float
#define SC_STYLE_SKEW_X             "skew-x"        // float
#define SC_STYLE_SKEW_Y             "skew-y"        // float
#define SC_STYLE_COLOR              "color"         // Color3B

#define SC_STYLE_FLIP_X             "flip-x"        // bool
#define SC_STYLE_FLIP_Y             "flip-y"        // bool
#define SC_STYLE_TEXT               "text"         // string
#define SC_STYLE_FONT_SIZE          "font-size"     // float
#define SC_STYLE_FONT_NAME          "font-name"     // string
#define SC_STYLE_TEXT_COLOR         "text-color"    // Color4B
#define SC_STYLE_IMAGE              "image"         // string
    
#define SC_STYLE_DOCK               "dock"          // SCNodeUtils::EDockType. e.g. left|top
#define SC_STYLE_X_BY               "x-by"          // float
#define SC_STYLE_Y_BY               "y-by"          // float
    
#define SC_STYLE_RADIO              "radio"         // int
    
class SCNodeStyle
{
private:
        
    enum EValueType
    {
        UNKNOWN_TYPE,
        FLOAT_TYPE,
        INT_TYPE,
        STRING_TYPE,
        BOOL_TYPE,
        VEC2_TYPE,
        COLOR3_TYPE,
        COLOR4_TYPE,
        DOCK_TYPE,
    };
        
    struct SStylePair
    {
        const char*         pszKey;
        EValueType          type;
            
        inline bool operator>(const SStylePair& pair) const
        {
            return (::strcmp(pair.pszKey,pszKey)<0);
        }
            
        inline bool operator<(const SStylePair& pair) const
        {
            return (::strcmp(pair.pszKey,pszKey)>0);
        }
    };
        
public:
    struct SFilterConfig
    {
        std::vector<SCString> keyVtr;
        bool bExclude;
            
        void setupPosition(const bool bExclude0)
        {
            bExclude = bExclude0;
            keyVtr =
            {
                SC_STYLE_X,
                SC_STYLE_Y,
                SC_STYLE_DOCK,
                SC_STYLE_X_BY,
                SC_STYLE_Y_BY
            };
        }
    };
        
public:
    static void setStyle(cocos2d::Node* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::Layer* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::Sprite* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::LayerColor* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::Menu* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::MenuItem* pNode,const SCDictionary& dic);
    static void setStyle(cocos2d::Label* pNode,const SCDictionary& dic);
        
    template<typename T>
    static void setStyle(cocos2d::Node* pNode,const SCString& strStyle,SFilterConfig* pFilterConfig=nullptr)
    {
        SCASSERT(pNode!=nullptr);
        SC_RETURN_V_IF(pNode==nullptr);
            
        SCDictionary dic;
        if(SCNodeStyle::convertString2Dic(strStyle,dic))
        {
            if(pFilterConfig!=nullptr && !pFilterConfig->keyVtr.empty())
            {
                if(pFilterConfig->bExclude)
                {
                    for(const auto& it : pFilterConfig->keyVtr)
                    {
                        dic.removeKey(it);
                    }
                }
                else
                {
                    SCDictionary dic2;
                    for(const auto& it : pFilterConfig->keyVtr)
                    {
                        if(dic.hasKey(it))
                        {
                            dic2.setValue(it,dic[it]);
                        }
                    }
                    dic = dic2;
                }
            }
            SCNodeStyle::setStyle(dynamic_cast<T*>(pNode),dic);
        }
    }
        
    static bool convertString2Dic(const SCString& strStyle,SCDictionary& dic);
    static SCString extractKey(const SCString& strKey,const SCString& strStyle);
    static SCString removeKey(const SCString& strKey,const SCString& strStyle);
    static bool isValid(const SCString& strStyle);
        
private:
    static bool scanStyle(const SCString& strStyle,
                          const bool bCheck,
                          const std::function<bool(const SCString&,EValueType type,const SCString&)>& func);
    static bool readKey(SCString& strKey,char*& pCurrent, char*& pEnd);
    static bool readValue(SCString& strValue,const EValueType type,char*& pCurrent, char*& pEnd);
    static void skipSpaces(char*& pCurrent, char*& pEnd);
    static void nextSemicolon(char*& pCurrent, char*& pEnd);
    static EValueType getKeyType(SCString& strKey);
    static bool parseValue(const EValueType type,const SCString& strValue,SCValue& value);
        
    static bool getColorByName(const SCString& strKey,cocos2d::Color3B& val);
    static bool getColorByName(const SCString& strKey,cocos2d::Color4B& val);
        
    static bool getColor3(const SCDictionary& dic,const SCString& strKey,cocos2d::Color3B& val);
    static bool getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val);
    static bool getString(const SCDictionary& dic,const SCString& strKey,SCString& val);
    static bool getFloat(const SCDictionary& dic,const SCString& strKey,float& val);
    static bool getInt(const SCDictionary& dic,const SCString& strKey,int& val);
    static bool getBool(const SCDictionary& dic,const SCString& strKey,bool& val);
    static bool getVec2(const SCDictionary& dic,const SCString& strKey,cocos2d::Vec2& array);
        
    static bool parseColor4(SCString strValue,cocos2d::Color4B& val);
    static bool parseVec2(SCString strValue,cocos2d::Vec2& vec2);
    static bool parseDock(SCString strDock,int& nDock);
        
    static bool isValidKeyChar(const char& c);
        
private:
    static SStylePair s_StylePairArray[];
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCNODEPROPERTY_H__
