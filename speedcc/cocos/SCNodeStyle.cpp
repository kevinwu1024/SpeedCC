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

#include "SCNodeStyle.h"
#include "SCNodeUtils.h"
#include "SCNodeAttachment.h"
#include "../system/SCSystem.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

// keep order by alphabet, so that it can apply binary search
// go to http://textmechanic.com/Sort-Text-Lines.html for sorting
SCNodeStyle::SStylePair SCNodeStyle::s_StylePairArray[] =
{
    {SC_STYLE_ANCHOR,       VEC2_TYPE},
    {SC_STYLE_ANCHOR_ON,    BOOL_TYPE},
    {SC_STYLE_COLOR,        COLOR3_TYPE},
    {SC_STYLE_DOCK,         DOCK_TYPE},
    {SC_STYLE_FLIP_X,       BOOL_TYPE},
    {SC_STYLE_FLIP_Y,       BOOL_TYPE},
    {SC_STYLE_FONT_NAME,    STRING_TYPE},
    {SC_STYLE_FONT_SIZE,    FLOAT_TYPE},
    {SC_STYLE_IMAGE,        STRING_TYPE},
    {SC_STYLE_OPACITY,      INT_TYPE},
    {SC_STYLE_RADIO,        INT_TYPE},
    {SC_STYLE_ROTATION,     FLOAT_TYPE},
    {SC_STYLE_ROTATION_X,   FLOAT_TYPE},
    {SC_STYLE_ROTATION_Y,   FLOAT_TYPE},
    {SC_STYLE_SCALE,        FLOAT_TYPE},
    {SC_STYLE_SCALE_X,      FLOAT_TYPE},
    {SC_STYLE_SCALE_Y,      FLOAT_TYPE},
    {SC_STYLE_SKEW_X,       FLOAT_TYPE},
    {SC_STYLE_SKEW_Y,       FLOAT_TYPE},
    {SC_STYLE_TAG,          INT_TYPE},
    {SC_STYLE_TEXT,         STRING_TYPE},
    {SC_STYLE_TEXT_COLOR,   COLOR4_TYPE},
    {SC_STYLE_VISIBLE,      BOOL_TYPE},
    {SC_STYLE_X,            FLOAT_TYPE},
    {SC_STYLE_X_BY,         FLOAT_TYPE},
    {SC_STYLE_Y,            FLOAT_TYPE},
    {SC_STYLE_Y_BY,         FLOAT_TYPE},
    {SC_STYLE_Z_ORDER,      INT_TYPE},
};
    
    
void SCNodeStyle::setStyle(Node* pNode,const SCDictionary& dic)
{
    SCASSERT(pNode!=nullptr);
    SC_RETURN_V_IF(pNode==nullptr);
        
    int nValue;
    float fValue;
    bool bValue;
    Color3B crValue;
    Vec2 vec2;
        
    if(SCNodeStyle::getInt(dic,SC_STYLE_TAG,nValue))
    {
        pNode->setTag(nValue);
    }
        
    if(SCNodeStyle::getColor3(dic,SC_STYLE_COLOR, crValue))
    {
        pNode->setColor(crValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_X,fValue) && pNode->getParent())
    {
        auto pos = SCNodeUtils::posP2A(Vec2(fValue,0),pNode->getParent()->getContentSize());
        pNode->setPositionX(pos.x);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_Y,fValue) && pNode->getParent())
    {
        auto pos = SCNodeUtils::posP2A(Vec2(0,fValue),pNode->getParent()->getContentSize());
        pNode->setPositionY(pos.y);
    }
        
    if(SCNodeStyle::getInt(dic,SC_STYLE_Z_ORDER,nValue))
    {
        pNode->setLocalZOrder(nValue);
    }
        
    if(SCNodeStyle::getVec2(dic,SC_STYLE_ANCHOR,vec2))
    {
        pNode->setAnchorPoint(vec2);
    }
        
    if(SCNodeStyle::getBool(dic,SC_STYLE_ANCHOR_ON,bValue))
    {
        pNode->setIgnoreAnchorPointForPosition(bValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_SCALE,fValue))
    {
        pNode->setScale(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_SCALE_X,fValue))
    {
        pNode->setScaleX(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_SCALE_Y,fValue))
    {
        pNode->setScaleY(fValue);
    }
        
    if(SCNodeStyle::getInt(dic,SC_STYLE_OPACITY,nValue))
    {
        pNode->setOpacity((GLubyte)nValue);
    }
        
    if(SCNodeStyle::getBool(dic,SC_STYLE_VISIBLE,bValue))
    {
        pNode->setVisible(bValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_ROTATION,fValue))
    {
        pNode->setRotation(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_ROTATION_X,fValue))
    {
        pNode->setRotationSkewX(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_ROTATION_Y,fValue))
    {
        pNode->setRotationSkewY(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_SKEW_X,fValue))
    {
        pNode->setSkewX(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_SKEW_Y,fValue))
    {
        pNode->setSkewY(fValue);
    }
        
    if(SCNodeStyle::getInt(dic, SC_STYLE_DOCK, nValue))
    {
        SCNodeUtils::setDock(pNode, nValue);
    }
        
    if(SCNodeStyle::getFloat(dic, SC_STYLE_X_BY, fValue))
    {
        SCNodeUtils::setPositionBy(pNode, fValue, 0);
    }
        
    if(SCNodeStyle::getFloat(dic, SC_STYLE_Y_BY, fValue))
    {
        SCNodeUtils::setPositionBy(pNode, 0, fValue);
    }
        
    if(SCNodeStyle::getInt(dic, SC_STYLE_RADIO, nValue))
    {
        SCNodeAttach(pNode)->setRadioID(nValue);
    }
}
    
void SCNodeStyle::setStyle(Layer* pNode,const SCDictionary& dic)
{
    SCASSERT(pNode!=nullptr);
    SC_RETURN_V_IF(pNode==nullptr);
        
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}
    
void SCNodeStyle::setStyle(Sprite* pNode,const SCDictionary& dic)
{
    float fValue;
    SCString strValue;
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_FLIP_X,fValue))
    {
        pNode->setFlippedX(fValue);
    }
        
    if(SCNodeStyle::getFloat(dic,SC_STYLE_FLIP_Y,fValue))
    {
        pNode->setFlippedY(fValue);
    }
        
    if(SCNodeStyle::getString(dic, SC_STYLE_IMAGE, strValue))
    {
        auto pSprite = Sprite::create(strValue.c_str());
        pNode->setSpriteFrame(pSprite->getSpriteFrame());
    }
        
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}
    
void SCNodeStyle::setStyle(LayerColor* pNode,const SCDictionary& dic)
{
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}
    
void SCNodeStyle::setStyle(Menu* pNode,const SCDictionary& dic)
{
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}
    
void SCNodeStyle::setStyle(MenuItem* pNode,const SCDictionary& dic)
{
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}
    
void SCNodeStyle::setStyle(Label* pNode,const SCDictionary& dic)
{
    SCString strValue;
    Color4B crValue;
    float fValue;
        
    if(SCNodeStyle::getString(dic, SC_STYLE_TEXT, strValue))
    {
        pNode->setString(strValue.c_str());
    }
        
    if(SCNodeStyle::getColor4(dic,SC_STYLE_TEXT_COLOR, crValue))
    {
        pNode->setTextColor(crValue);
    }
        
    if(SCNodeStyle::getString(dic, SC_STYLE_FONT_NAME, strValue))
    {
        pNode->setSystemFontName(strValue.c_str());
    }
        
    if(SCNodeStyle::getFloat(dic, SC_STYLE_FONT_SIZE, fValue))
    {
        pNode->setSystemFontSize(fValue);
    }
        
    SCNodeStyle::setStyle(dynamic_cast<Node*>(pNode),dic);
}

bool SCNodeStyle::isValid(const SCString& strStyle)
{
    return SCNodeStyle::scanStyle(strStyle,true,nullptr);
}
    
///-------------- convert string to dictionary
bool SCNodeStyle::convertString2Dic(const SCString& strStyle,SCDictionary& dic)
{
    dic.removeAllKeys();
    SC_RETURN_IF(strStyle.isEmpty(), true);
        
    bool bResult = true;
        
    bool bRet = SCNodeStyle::scanStyle(strStyle,false,[strStyle,&dic,&bResult](const SCString& strKey,
                                                            EValueType type,
                                                            const SCString& strValue) -> bool
                                    {
                                        SCValue data;
                                        if(!SCNodeStyle::parseValue(type,strValue,data))
                                        {
                                            SCLog("style: ========== '%s' value parse failed in '%s' ========== ",strValue.c_str(),strStyle.c_str());
                                            SCASSERT(false);
                                            bResult = false;
                                            return false;
                                        }
                                        dic.setValue(strKey, data);
                                        return true;
                                    });
        
    bRet = (bRet && bResult);
        
    return bRet;
}
    
SCString SCNodeStyle::extractKey(const SCString& strKey,const SCString& strStyle)
{
    SC_RETURN_IF(strKey.isEmpty() || strStyle.isEmpty(), "");
        
    SCString strRet;
    SCString strValue = "";
    SCNodeStyle::scanStyle(strStyle,false,[strKey,&strValue](const SCString& strKey0,
                                                        EValueType type,
                                                        const SCString& strValue0) -> bool
                                    {
                                        if(strKey==strKey0)
                                        {
                                            strValue = strValue0;
                                            return false;
                                        }
                                         
                                        return true;
                                    });
        
    if(!strValue.isEmpty())
    {
        strRet = strKey + "=" + strValue + ";";
    }
        
    return strRet;
}
    
SCString SCNodeStyle::removeKey(const SCString& strKey,const SCString& strStyle)
{
    SCString strRet;
    SCNodeStyle::scanStyle(strStyle,false,[strKey,&strRet](const SCString& strKey0,
                                                                EValueType type,
                                                                const SCString& strValue0) -> bool
                                    {
                                        if(strKey!=strKey0)
                                        {
                                            strRet += strKey0 + "=" + strValue0 + ";";
                                        }
                                         
                                        return true;
                                    });
        
    return strRet;
}
    
bool SCNodeStyle::scanStyle(const SCString& strStyle,
                            const bool bCheck,
                            const std::function<bool(const SCString&,EValueType type,const SCString&)>& func)
{
    SCASSERT(func!=nullptr);
    SC_RETURN_IF(strStyle.isEmpty() || func==nullptr,true);
        
    bool bRet = true;
    auto pCurrent = (char*)strStyle.c_str();
    auto pEnd = pCurrent + strStyle.getLength();
    SCString strKey;
    SCString strValue;
        
    int n = 1;
    while(pCurrent != pEnd)
    {
        do
        {
            if(!SCNodeStyle::readKey(strKey,pCurrent,pEnd))
            {
                SCLog("style: ========== No.%d key read failed in '%s' ==========",n,strStyle.c_str());
                SC_RETURN_IF(bCheck, false);
                SCASSERT(false);
                SCNodeStyle::nextSemicolon(pCurrent,pEnd);
                bRet = false;
                break;
            }
            strKey.makeLower();

            auto valueType = SCNodeStyle::getKeyType(strKey);

            if(valueType==UNKNOWN_TYPE)
            {
                SCLog("style: ========== No.%d key parse failed in '%s' ========== ",n,strStyle.c_str());
                SC_RETURN_IF(bCheck, false);
                SCASSERT(false);
                SCNodeStyle::nextSemicolon(pCurrent,pEnd);
                bRet = false;
                break;
            }
                
            if(!SCNodeStyle::readValue(strValue,valueType,pCurrent,pEnd))
            {
                SCLog("style: ========== No.%d value read failed in '%s' ========== ",n,strStyle.c_str());
                SC_RETURN_IF(bCheck, false);
                SCASSERT(false);
                SCNodeStyle::nextSemicolon(pCurrent,pEnd);
                bRet = false;
                break;
            }
            
            if(func)
            {
                SC_RETURN_IF(!func(strKey,valueType,strValue),true);
            }
        }
        while(0);
            
        SCNodeStyle::skipSpaces(pCurrent,pEnd);
        ++n;
    }
        
    return bRet;
}
    
SCNodeStyle::EValueType SCNodeStyle::getKeyType(SCString& strKey)
{
    SStylePair pair = {strKey,UNKNOWN_TYPE};
    auto it = std::lower_bound(s_StylePairArray,s_StylePairArray+SC_ARRAY_LENGTH(s_StylePairArray),pair);
    if(it!=s_StylePairArray+SC_ARRAY_LENGTH(s_StylePairArray) && strKey==(*it).pszKey)
    {
        return (*it).type;
    }
    return UNKNOWN_TYPE;
}
    
bool SCNodeStyle::readKey(SCString& strKey,char*& pCurrent, char*& pEnd)
{
    bool bRet = false;
        
    SCNodeStyle::skipSpaces(pCurrent,pEnd);
        
    char* pBegin = pCurrent;
        
    do
    {
        SC_BREAK_IF(pCurrent==pEnd);
        SC_BREAK_IF(!SCNodeStyle::isValidKeyChar(*pCurrent));
        ++pCurrent;
    }
    while(1);
        
    char* pEnd2 = pCurrent;
    SCNodeStyle::skipSpaces(pCurrent,pEnd);
        
    if(pEnd2>pBegin && *pCurrent=='=' && pCurrent!=pEnd)
    {
        char szBuf[64+1] = {0};
            
        if(pEnd2-pBegin<sizeof(szBuf))
        {
            memcpy(szBuf,pBegin,pEnd2-pBegin);
            strKey = szBuf;
            strKey.makeLower();
            bRet = true;
        }
    }
        
    if(pEnd>pCurrent)
    {
        ++pCurrent; // skip '=' or invalide char
    }
        
    return bRet;
}
    
bool SCNodeStyle::readValue(SCString& strValue,const EValueType type,char*& pCurrent, char*& pEnd)
{
    bool bRet = false;
        
    SCNodeStyle::skipSpaces(pCurrent,pEnd);
        
    char* pBegin = pCurrent;
        
    if(type==STRING_TYPE)
    {
        const char cQuote = '\'';
        int nQuoteStack = 0;
        char* pBeginQuote = nullptr;
        char* pEndQuote = nullptr;
            
        do
        {
            SC_BREAK_IF(pCurrent==pEnd);
            if(nQuoteStack>1)
            {
                SC_BREAK_IF(*pCurrent==';');
            }
                
            if(nQuoteStack==0 && *pCurrent==cQuote)
            {// enter quote
                nQuoteStack = 1;
                pBeginQuote = pCurrent;
            }
            else if(nQuoteStack==1 && *pCurrent==cQuote && pEnd>pCurrent && *(pCurrent+1)!=cQuote)
            {// leave quote
                nQuoteStack = 2;
                pEndQuote = pCurrent;
            }
                
            ++pCurrent;
        }
        while(1);
            
        char szBuf[64+1] = {0};
            
        if(pBeginQuote!=nullptr && pEndQuote-pBeginQuote<sizeof(szBuf))
        {
            memcpy(szBuf,pBeginQuote+1,pEndQuote-pBeginQuote-1);
            strValue = szBuf;
            while(!strValue.isEmpty() && strValue.find("''")>=0)
            {
                strValue.replace("''", "'");
            }
            bRet = true;
        }
            
        while(pEnd>pBegin && *pCurrent==';')
        {
            ++pCurrent; // skip ';'
        }
    }
    else
    {
        do
        {
            SC_BREAK_IF(pCurrent==pEnd);
            SC_BREAK_IF(*pCurrent==';');
            ++pCurrent;
        }
        while(1);
            
        char* pEnd2 = pCurrent;
        SCNodeStyle::skipSpaces(pCurrent,pEnd);
            
        if(pEnd2>pBegin && *pCurrent==';')
        {
            ++pCurrent; // skip ';'
            char szBuf[64+1] = {0};
                
            while(*(pEnd2-1)==' ' && pEnd2>pBegin)
            {--pEnd2;}
                
            if(pEnd2-pBegin<sizeof(szBuf))
            {
                memcpy(szBuf,pBegin,pEnd2-pBegin);
                strValue = szBuf;
                bRet = true;
            }
        }
    }
        
    return bRet;
}
    
void SCNodeStyle::skipSpaces(char*& pCurrent, char*& pEnd)
{
    do
    {
        SC_BREAK_IF(pCurrent==pEnd);
        const char& c = *pCurrent;
        SC_BREAK_IF(c!=' ' && c!='\t' && c!='\r' && c!='\n');
            
        ++pCurrent;
    }
    while(1);
}
    
void SCNodeStyle::nextSemicolon(char*& pCurrent, char*& pEnd)
{
    do
    {
        CC_BREAK_IF(pCurrent==pEnd);
        CC_BREAK_IF(*pCurrent==';');
        ++pCurrent;
    }
    while(1);
}
    
bool SCNodeStyle::parseValue(const EValueType type,const SCString& strValue,SCValue& value)
{
    bool bRet = false;
        
    try
    {
        switch(type)
        {
            case UNKNOWN_TYPE: break;
                    
            case FLOAT_TYPE:
                value.setFloat(strValue.asFloat());
                bRet = true;
                break;
                    
            case INT_TYPE:
                value.setInt(strValue.asInt());
                bRet = true;
                break;
            case STRING_TYPE:
                value.setString(strValue);
                bRet = true;
                break;
            case BOOL_TYPE:
                value.setBool(strValue.asBool());
                bRet = true;
                break;
            case VEC2_TYPE:
            {
                Vec2 vec;
                if(SCNodeStyle::parseVec2(strValue,vec))
                {
                    value.setObject(vec);
                    bRet = true;
                }
            }
                break;
                    
            case COLOR3_TYPE:
            {
                Color4B cr;
                if(SCNodeStyle::parseColor4(strValue,cr))
                {
                    value.setObject(Color3B(cr));
                    bRet = true;
                }
            }
                break;
                    
            case COLOR4_TYPE:
            {
                Color4B cr;
                if(SCNodeStyle::parseColor4(strValue,cr))
                {
                    value.setObject(cr);
                    bRet = true;
                }
            }
                break;
                    
            case DOCK_TYPE:
            {
                int nDock = 0;
                if(SCNodeStyle::parseDock(strValue, nDock))
                {
                    value.setInt(nDock);
                    bRet = true;
                }
            }
                break;
        }
            
    }catch(...){}
        
    return bRet;
}
    
/////-------------------
bool SCNodeStyle::isValidKeyChar(const char& c)
{
    return ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='-' || c=='_');
}
    
bool SCNodeStyle::getInt(const SCDictionary& dic,const SCString& strKey,int& val)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
    const auto value = dic.getValue(strKey);
    SC_RETURN_IF(value.getType()!=SCValue::kTypeInt, false);
    val = value.getInt();
    return true;
}
    
bool SCNodeStyle::getBool(const SCDictionary& dic,const SCString& strKey,bool& val)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
    const auto value = dic.getValue(strKey);
    SC_RETURN_IF(value.getType()!=SCValue::kTypeBool, false);
    val = value.getBool();
    return true;
}
    
bool SCNodeStyle::getFloat(const SCDictionary& dic,const SCString& strKey,float& val)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
    const auto value = dic.getValue(strKey);
    SC_RETURN_IF(value.getType()!=SCValue::kTypeFloat, false);
    val = value.getFloat();
    return true;
}
    
bool SCNodeStyle::getVec2(const SCDictionary& dic,const SCString& strKey,Vec2& vec)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
    auto value = dic.getValue(strKey);
        
    if(value.getType()==SCValue::kTypeObject && value.isValidObject<Vec2>())
    {
        vec = value.getObject<Vec2>();
        return true;
    }

    return false;
}
    
bool SCNodeStyle::getString(const SCDictionary& dic,const SCString& strKey,SCString& val)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
    const auto value = dic.getValue(strKey);
    SC_RETURN_IF(value.getType()!=SCValue::kTypeString, false);
    val = value.getString();
    return true;
}
    
bool SCNodeStyle::getColorByName(const SCString& strKey,Color3B& val)
{
    struct STemStruct
    {
        const char*     pszName;
        Color3B         crValue;
            
        inline bool operator>(const STemStruct& pair) const
        {
            return (strcmp(pair.pszName,pszName)<0);
        }
            
        inline bool operator<(const STemStruct& pair) const
        {
            return (strcmp(pair.pszName,pszName)>0);
        }
    };
        
    // keep order by alphabet
    const STemStruct colorTableArray[] =
    {
        {"black",Color3B(0,0,0)},
        {"blue",Color3B(0,0,255)},
        {"gray",Color3B(166,166,166)},
        {"green",Color3B(0,255,0)},
        {"magenta",Color3B(255,0,255)},
        {"orange",Color3B(255,127,0)},
        {"red",Color3B(255,0,0)},
        {"white",Color3B(255,255,255)},
        {"yellow",Color3B(255,255,0)}
    };
        
    STemStruct pair = {strKey,Color3B(0,0,0)};
    bool bRet = false;
    auto it = std::lower_bound(colorTableArray,colorTableArray+SC_ARRAY_LENGTH(colorTableArray),pair);
    if(it!=colorTableArray+SC_ARRAY_LENGTH(colorTableArray) && strKey==(*it).pszName)
    {
        val = (*it).crValue;
        bRet = true;
    }
    return bRet;
}
    
bool SCNodeStyle::getColorByName(const SCString& strKey,Color4B& val)
{
    Color3B cr;
    if(getColorByName(strKey,cr))
    {
        val.set(cr.r, cr.g, cr.b, 255);
        return true;
    }
        
    return false;
}
    
bool SCNodeStyle::getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val)
{
    SC_RETURN_IF(!dic.hasKey(strKey), false);
        
    bool bRet = false;
    auto value = dic.getValue(strKey);
    if(value.getType()==SCValue::kTypeObject)
    {
        if(value.isValidObject<Color3B>())
        {
            val = Color4B(value.getObject<Color3B>());
            bRet = true;
        }
        else if(value.isValidObject<Color4B>())
        {
            val = value.getObject<Color4B>();
            bRet = true;
        }
    }
        
    return bRet;
}
    
bool SCNodeStyle::getColor3(const SCDictionary& dic,const SCString& strKey,Color3B& val)
{
    Color4B cr;
    SC_RETURN_IF(!SCNodeStyle::getColor4(dic,strKey,cr),false);
    val = Color3B(cr);
    return true;
}
    
    
///----------- parse
    
bool SCNodeStyle::parseVec2(SCString strValue,cocos2d::Vec2& vec2)
{
    bool bRet = false;
    if(strValue.getLength()>=5 &&
        ((strValue[0]=='(' && strValue[strValue.getLength()-1]==')') || (strValue[0]=='{' && strValue[strValue.getLength()-1]=='}')))
    {// {?,?} or (?,?)
        strValue.trimLeft('(');
        strValue.trimLeft('{');
        strValue.trimRight(')');
        strValue.trimRight('}');
            
        auto sl = strValue.split(",");
            
        if(sl.size()==2)
        {
            try
            {
                vec2.x = sl[0].asFloat();
                vec2.y = sl[1].asFloat();
                bRet = true;
            }
            catch(...){}
        }
    }
        
    return bRet;
}
    
bool SCNodeStyle::parseColor4(SCString strValue,Color4B& val)
{
    SC_RETURN_IF(strValue.isEmpty(), false);
        
    bool bRet = false;
        
    SC_RETURN_IF(SCNodeStyle::getColorByName(strValue,val), true);
        
    if(strValue.getLength()>1 && strValue.getLength()<=9 && strValue[0]=='#')
    {// #AARRGGBB
        strValue.format("0x%s",strValue.c_str()+1);
            
        char* p = nullptr;
        uint32_t uv=0;
        uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
            
        val.b = (uv&0x000000ff);
        val.g = ((uv&0x0000ff00)>>8);
        val.r = ((uv&0x00ff0000)>>16);
        val.a = ((uv&0xff000000)>>24);
        bRet = true;
    }
    else if(strValue.getLength()>2 && strValue.getLength()<=10 && strValue[0]=='0' && strValue[1]=='x')
    {// 0xAARRGGBB
        char* p = nullptr;
        uint32_t uv=0;
        uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
            
        val.b = (uv&0x000000ff);
        val.g = ((uv&0x0000ff00)>>8);
        val.r = ((uv&0x00ff0000)>>16);
        val.a = ((uv&0xff000000)>>24);
        bRet = true;
    }else if(strValue.getLength()>6 &&
                ((strValue[0]=='(' && strValue[strValue.getLength()-1]==')') || (strValue[0]=='{' && strValue[strValue.getLength()-1]=='}')))
    {// {r,g,b,a} or (r,g,b,a)
        strValue.trimLeft('(');
        strValue.trimLeft('{');
        strValue.trimRight(')');
        strValue.trimRight('}');
            
        auto sl = strValue.split(",");
            
        if(sl.size()>=3)
        {
            try
            {
                sl[0].trimLeft(' ');
                sl[0].trimRight(' ');
                sl[1].trimLeft(' ');
                sl[1].trimRight(' ');
                sl[2].trimLeft(' ');
                sl[2].trimRight(' ');
                    
                if(sl.size()==4)
                {
                    sl[3].trimLeft(' ');
                    sl[3].trimRight(' ');
                }
                    
                val.r = sl[0].asInt();
                val.g = sl[1].asInt();
                val.b = sl[2].asInt();
                val.a = (sl.size()==4) ? sl[3].asInt() : 255;
                bRet = true;
            }
            catch(...){}
        }
    }
        
    return bRet;
}
    
bool SCNodeStyle::parseDock(SCString strDock,int& nDock)
{
    nDock = 0;
    SC_RETURN_IF(strDock.isEmpty(), true);
    strDock.trimLeft('\'');
    strDock.trimRight('\'');
    strDock.makeLower();
        
    auto stringVtr = strDock.split("|");
        
    struct STemStruct
    {
        const char*     pszName;
        int             dock;
            
        inline bool operator>(const STemStruct& pair) const
        {
            return (strcmp(pair.pszName,pszName)<0);
        }
            
        inline bool operator<(const STemStruct& pair) const
        {
            return (strcmp(pair.pszName,pszName)>0);
        }
    };
        
    // keep order by alphabet
    const STemStruct dockTableArray[] =
    {
        {"bottom",SCNodeUtils::kDockBottom},
        {"center",SCNodeUtils::kDockCenter},
        {"left",SCNodeUtils::kDockLeft},
        {"mid-x",SCNodeUtils::kDockMiddleX},
        {"mid-y",SCNodeUtils::kDockMiddleY},
        {"right",SCNodeUtils::kDockRight},
        {"top",SCNodeUtils::kDockTop},
    };
        
    for(auto strKey : stringVtr)
    {
        strKey.trimRight(' ');
        strKey.trimLeft(' ');
            
        STemStruct pair = {strKey,0};
        auto it = std::lower_bound(dockTableArray,dockTableArray+SC_ARRAY_LENGTH(dockTableArray),pair);
        if(it!=dockTableArray+SC_ARRAY_LENGTH(dockTableArray) && strKey==(*it).pszName)
        {
            nDock |= (*it).dock;
        }
        else
        {
            SCLog("Unknown dock value: %s",strKey.c_str());
            SCASSERT(false);
        }
    }
        
    return true;
}
    
NAMESPACE_SPEEDCC_END

