//
//  LevelSelectRowWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class LevelSelectRowWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static LevelSelectRowWidget* create(int level, int sublevel);
        
        bool init(int level, int sublevel);
        
        std::function<void(int)> onTapped;
    };
}
