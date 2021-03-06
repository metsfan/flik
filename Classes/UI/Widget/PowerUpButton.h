//
//  PowerUpButton.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"

namespace flik
{
    class PowerUpButton : public cocos2d::ui::Button
    {
    public:
        static PowerUpButton* create(PowerUpType type);
        
        bool init(PowerUpType type);
        
        void setCount(int count);
        
        void update(float seconds);
        
        void onEnter();
        
    private:
        PowerUpType mType;
        int mCount;
    };
}
