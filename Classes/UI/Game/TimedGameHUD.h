//
//  TimedGameHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#pragma once

#include "MainGameHUD.h"

namespace flik
{
    class TimedGameHUD : public MainGameHUD
    {
    public:
        CREATE_FUNC(TimedGameHUD);
        
        ~TimedGameHUD();
        
        virtual bool init();
        
        void update(float time);
        
    protected:
        cocos2d::ui::Layout* mTimerBar;
    };
}