//
//  GameSelectRowWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include "GameSelectRowWidget.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"
#include "LevelTypes.h"
#include "LocalizedString.h"
#include "format.h"
#include "LevelTypes.h"
#include "PercentBubbleLayer.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    GameSelectRowWidget* GameSelectRowWidget::create(int level, const std::string& name)
    {
        return createWithParams<GameSelectRowWidget>(level, name);
    }
    
    bool GameSelectRowWidget::init(int level, const std::string& name)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto levelText = Fonts::createLocalizedText(LocalizedString::getString("level_name_" + name), 21.0_dp);
        levelText->setTextVerticalAlignment(TextVAlignment::CENTER);
        auto levelTextLayout = ui::RelativeLayoutParameter::create();
        levelTextLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        levelTextLayout->setMargin(ui::Margin(37.0_dp, 0, 0, 0));
        levelText->setLayoutParameter(levelTextLayout);
        addChild(levelText);
        
        auto levelStatusContainer = ui::RelativeBox::create(Size(60.0_dp, 60.0_dp));
        auto levelStatusContainerLayout = ui::RelativeLayoutParameter::create();
        levelStatusContainerLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        levelStatusContainerLayout->setMargin(ui::Margin(0, 0, 37.0_dp, 0));
        levelStatusContainer->setLayoutParameter(levelStatusContainerLayout);
        addChild(levelStatusContainer);

        auto levelStatus = ui::ImageView::create("game_select_icon.png");
        auto levelStatusLayout = ui::RelativeLayoutParameter::create();
        levelStatusLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        levelStatus->setLayoutParameter(levelStatusLayout);
        levelStatusContainer->addChild(levelStatus);
        
        setTouchEnabled(true);
        addTouchEventListener([this, level](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::BEGAN) {
                setBackGroundColor(Util::getColorFromHex("444444"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            } else {
                if (type == TouchEventType::ENDED && onTapped) {
                    onTapped(level);
                }
                
                setBackGroundColor(Util::getColorFromHex("000000"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
            }
        });
        
        float percent = LevelInfo::getInstance()->getGameCompletionPercentage(level);
        
        if (percent == 1.0) {
            auto completeImage = ui::ImageView::create("level_complete.png");
            completeImage->setAnchorPoint(Vec2(-0.1, -0.1));
            levelStatus->addChild(completeImage);
        } else {
            auto levelStatusPercentBubble = PercentBubbleLayer::create();
            levelStatusPercentBubble->setColor(kPinkColor);
            levelStatusPercentBubble->setPercent(percent);
            levelStatusPercentBubble->setContentSize(levelStatus->getContentSize());
            levelStatus->addChild(levelStatusPercentBubble);
        }

        return true;
    }
}
