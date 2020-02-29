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

#ifndef __SPEEDCC__SCVIEWMACROS_H__
#define __SPEEDCC__SCVIEWMACROS_H__

NAMESPACE_SPEEDCC_BEGIN

// root
#define SC_BEGIN_PARENT_ROOT(_builder_,_style_,_size_) \
{\
    SCViewBuilder::Ptr ptrSCTemUIBuilder = SCViewBuilder::create();\
    ptrSCTemUIBuilder->beginParentRoot(0.5,0.5,(_style_),(_size_),this->getView(),dynamic_cast<cocos2d::Ref*>(this)); \
    SCViewBuilder::assign(_builder_,ptrSCTemUIBuilder);


#define SC_BEGIN_PARENT_ROOT_EX(_builder_,_style_,_size_,_parent_,_ref_) \
{\
    SCViewBuilder::Ptr ptrSCTemUIBuilder = SCViewBuilder::create();\
    ptrSCTemUIBuilder->beginParentRoot(kSCPositionIgnore,kSCPositionIgnore,(_style_),(_size_),(_parent_),(_ref_)); \
    SCViewBuilder::assign(_builder_,ptrSCTemUIBuilder);

#define SC_END_PARENT \
    ptrSCTemUIBuilder->popParentStack(); \
}

// sprite
#define SC_INSERT_SPRITE(_node_,_style_,_image_) \
    ptrSCTemUIBuilder->insertSprite((_node_),0,0,(_style_),(_image_));

#define SC_BEGIN_PARENT_SPRITE(_node_,_style_,_image_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertSprite((_node_),0,0,(_style_),(_image_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// layer
#define SC_INSERT_LAYER(_node_,_style_,_size_) \
    ptrSCTemUIBuilder->insertLayer((_node_),0,0,(_style_),(_size_));

#define SC_BEGIN_PARENT_LAYER(_node_,_style_,_size_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLayer((_node_),0,0,(_style_),(_size_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_LAYER_COLOR(_node_,_style_,_size_,_color_) \
    ptrSCTemUIBuilder->insertLayerColor((_node_),0,0,(_style_),(_size_),(_color_));

#define SC_BEGIN_PARENT_LAYER_COLOR(_node_,_style_,_size_,_color_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLayerColor((_node_),0,0,(_style_),(_size_),(_color_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// label
#define SC_INSERT_LABEL(_node_,_style_,_string_,_font_,_size_)\
    ptrSCTemUIBuilder->insertLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\

#define SC_BEGIN_PARENT_LABEL(_node_,_style_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_LABEL_TTF(_node_,_style_,_string_,_font_,_size_)\
    ptrSCTemUIBuilder->insertLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_));

#define SC_BEGIN_PARENT_LABEL_TTF(_node_,_style_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_LABEL_BMFONT(_node_,_style_,_string_,_file_)\
    ptrSCTemUIBuilder->insertLabelBMFont((_node_),0,0,(_style_),(_string_),(_file_));

#define SC_BEGIN_PARENT_LABEL_BMFONT(_node_,_style_,_string_,_file_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabelBMFont((_node_),0,0,(_style_),(_string_),(_file_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// user node
#define SC_INSERT_USER_NODE(_node_,_style_) \
    ptrSCTemUIBuilder->insertUserNode((_node_),0,0,(_style_));

#define SC_BEGIN_PARENT_USER_NODE(_node_,_style_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertUserNode((_node_),0,0,(_style_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// node
#define SC_INSERT_NODE(_node_,_style_,_size_) \
    ptrSCTemUIBuilder->insertNode((_node_),0,0,(_style_),(_size_));

#define SC_BEGIN_PARENT_NODE(_node_,_style_,_size_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertNode((_node_),0,0,(_style_),(_size_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// button
#define SC_INSERT_BUTTON(_node_,_style_,_image_,_func_)\
    ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_),(_image_),(_image_),(_func_));

#define SC_BEGIN_PARENT_BUTTON(_node_,_style_,_image_,_func_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_),(_image_),(_image_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON3(_node_,_style_,_image_normal_,_image_select_,_image_disable_,_func_)\
    ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_normal_),(_image_select_),(_image_disable_),(_func_));

#define SC_BEGIN_PARENT_BUTTON3(_node_,_style_,_image_normal_,_image_select_,_image_disable_,_func_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_normal_),(_image_select_),(_image_disable_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL(_node_,_style_,_string_,_font_,_size_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_PARENT_BUTTON_LABEL(_node_,_style_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_TTF(_node_,_style_,_string_,_font_,_size_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_PARENT_BUTTON_LABEL_TTF(_node_,_style_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_BMFONT(_node_,_style_,_string_,_font_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabelBMFont((_node_),0,0,(_style_),(_string_),(_font_),(_func_));

#define SC_BEGIN_PARENT_BUTTON_LABEL_BMFONT(_node_,_style_,_string_,_font_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabelBMFont((_node_),0,0,(_style_),(_string_),(_font_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON_SWITCH(_node_,_style_,_true_image_,_false_image_,_value_,_func_) \
    ptrSCTemUIBuilder->insertButtonSwitch((_node_),0,0,(_style_),(_true_image_),(_false_image_),(_value_),(_func_));

#define SC_BEGIN_PARENT_BUTTON_SWITCH(_node_,_style_,_true_image_,_false_image_,_value_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonSwitch((_node_),0,0,(_style_),(_true_image_),(_false_image_),(_value_),(_func_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_BUTTON_RADIO(_node_,_style_,_true_image_,_false_image_,_group_,_id_,_func_) \
    ptrSCTemUIBuilder->insertButtonRadio((_node_),0,0,(_style_),(_true_image_),(_false_image_),(_group_),(_id_),(_func_));

#define SC_BEGIN_PARENT_BUTTON_RADIO(_node_,_style_,_true_image_,_false_image_,_group_,_id_,_func_) \
{\
auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonRadio((_node_),0,0,(_style_),(_true_image_),(_false_image_),(_group_),(_id_),(_func_)); \
ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);


// progress bar
#define SC_INSERT_PROGRESS_BAR(_node_,_style_,_image_back_,_image_front_,_value_,_is_hor_,_is_l2r_or_b2t_)\
    ptrSCTemUIBuilder->insertProgressBar((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_l2r_or_b2t_));

#define SC_BEGIN_PARENT_PROGRESS_BAR(_node_,_style_,_image_back_,_image_front_,_value_,_is_hor_,_is_left_or_bottom_)\
{\
auto pSCContainerNode = ptrSCTemUIBuilder->insertProgressBar((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_left_or_bottom_));\
ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

#define SC_INSERT_PROGRESS_RADIAL(_node_,_style_,_image_back_,_image_front_,_value_,_ccw_)\
    ptrSCTemUIBuilder->insertProgressRadial((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_ccw_));

#define SC_BEGIN_PARENT_PROGRESS_RADIAL(_node_,_style_,_image_back_,_image_front_,_value_,_ccw_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertProgressRadial((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_ccw_));\
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// layout
#define SC_BEGIN_PARENT_ALIGNMENT(_node_,_style_,_is_hor_,_padding_,_dock_) \
{\
    ptrSCTemUIBuilder->parentAlignment((_node_),0,0,(_style_),(_is_hor_),(_padding_),(_dock_));\

// scrollview
#define SC_BEGIN_PARENT_SCROLLVIEW(_node_,_style_,_is_hor_,_view_size_,_container_size_,_callback_) \
{\
    ptrSCTemUIBuilder->parentScrollView((_node_),0,0,(_style_),(_is_hor_),(_view_size_),(_container_size_),(_callback_));

// pageview
#define SC_BEGIN_PARENT_PAGEVIEW(_node_,_style_,_dir_,_size_,_page_index_,_callback_) \
{\
    ptrSCTemUIBuilder->parentPageView((_node_),0,0,(_style_),(_dir_),(_size_),(_page_index_),(_callback_));

#define SC_BEGIN_PARENT_PAGE(_node_,_size_) \
{\
    ptrSCTemUIBuilder->parentPage((_node_),(_size_));

// editbox
#define SC_INSERT_EDITBOX(_node_,_style_,_size_,_image_,_callback_) \
    ptrSCTemUIBuilder->insertEditBox((_node_),0,0,(_style_),(_size_),(_image_),(_callback_));

// slider
#define SC_INSERT_SLIDER(_node_,_style_,_background_image_,_front_image_,_handle_image_,_value_) \
    ptrSCTemUIBuilder->insertSlider((_node_),0,0,(_style_),(_background_image_),(_front_image_),(_handle_image_),(_value_));

#define SC_BEGIN_PARENT_SLIDER(_node_,_style_,_background_image_,_front_image_,_handle_image_,_value_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertSlider((_node_),0,0,(_style_),(_background_image_),(_front_image_),(_handle_image_),(_value_)); \
ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// Scale9Sprite
#define SC_INSERT_9SPRITE(_node_,_style_,_image_,_size_) \
    ptrSCTemUIBuilder->insertScale9Sprite((_node_),0,0,(_style_),(_image_),(_size_));

#define SC_BEGIN_PARENT_9SPRITE(_node_,_style_,_image_,_size_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertScale9Sprite((_node_),0,0,(_style_),(_image_),(_size_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);

// ClippingNode / Mask
#define SC_BEGIN_PARENT_CROP(_node_,_style_,_size_) \
{\
    ptrSCTemUIBuilder->parentCrop((_node_),0,0,(_style_),(_size_)); \

// ClippingNode Stencil
#define SC_INSERT_STENCIL(_node_,_style_,_image_,_is_invert_,_threshold_) \
    ptrSCTemUIBuilder->insertCropStencil((_node_),0,0,(_style_),(_image_),(_is_invert_),(_threshold_));

#define SC_BEGIN_PARENT_STENCIL(_node_,_style_,_image_,_is_invert_,_threshold_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertCropStencil((_node_),0,0,(_style_),(_image_),(_is_invert_),(_threshold_)); \
    ptrSCTemUIBuilder->pushParentStack(pSCContainerNode);


///---------- build-in
#define SC_INSERT_OPTION_MUSIC(_node_,_style_,_true_item_,_false_item_) \
do{\
    auto ptrMusic = SpeedCC::SCSetting::getInstance()->getMusicWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_style_),(_true_item_),(_false_item_),ptrMusic,nullptr) \
}while(0);

#define SC_INSERT_OPTION_SOUND(_node_,_style_,_true_item_,_false_item_) \
do{\
    auto ptrSound = SpeedCC::SCSetting::getInstance()->getSoundWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_style_),(_true_item_),(_false_item_),ptrSound,nullptr) \
}while(0);

// context parent node
#define SCViewContextParent (ptrSCTemUIBuilder->getContextParent())

NAMESPACE_SPEEDCC_END

#endif  // __SPEEDCC__SCVIEWMACROS_H__
