//
//  Player.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;

namespace flik
{
    static Player* sPlayerInstance = nullptr;
    
    static std::string kTopScoreKey = "key_topScore";
    static std::map<PowerUpType, std::string> kPowerUpCountKeys {
        std::pair<PowerUpType, std::string>(PowerUpType::Timestop, "key_powerUpTimestopCount"),
        std::pair<PowerUpType, std::string>(PowerUpType::Target, "key_powerUpTargetCount")
    };
    static std::string kCurrencyKey = "key_currency";
    
    Player* Player::getMainPlayer()
    {
        if (sPlayerInstance == nullptr) {
            sPlayerInstance = new Player();
        }
        
        return sPlayerInstance;
    }
    
    Player::Player() :
        mCurrentScore(0)
    {
    }
    
    int Player::getTopScore(std::string key)
    {
        auto userDefaults = UserDefault::getInstance();
        return userDefaults->getIntegerForKey((kTopScoreKey + "_" + key).c_str());
    }
    
    void Player::resetScore()
    {
        mCurrentScore = 0;
    }
    
    void Player::addScore(int amount)
    {
        mCurrentScore += amount;
    }
    
    void Player::recordScore(std::string key)
    {
        int topScore = getTopScore(key);
        if (topScore < mCurrentScore) {
            UserDefault::getInstance()->setIntegerForKey((kTopScoreKey + "_" + key).c_str(), mCurrentScore);
        }
    }
    
    int Player::getPowerUpCount(PowerUpType type)
    {
        return UserDefault::getInstance()->getIntegerForKey(kPowerUpCountKeys[type].c_str(), 0);
    }
    
    void Player::consumePowerUp(PowerUpType type, int count)
    {
        int newCount = getPowerUpCount(type) - count;
        UserDefault::getInstance()->setIntegerForKey(kPowerUpCountKeys[type].c_str(), newCount);
    }
    
    void Player::addPowerUp(PowerUpType type, int count)
    {
        int newCount = getPowerUpCount(type) + count;
        UserDefault::getInstance()->setIntegerForKey(kPowerUpCountKeys[type].c_str(), newCount);
    }
    
    int Player::getCurrencyAmount()
    {
         return UserDefault::getInstance()->getIntegerForKey(kCurrencyKey.c_str(), 0);
    }
    
    void Player::addCurrency(int amount)
    {
        int newCount = getCurrencyAmount() + amount;
        UserDefault::getInstance()->setIntegerForKey(kCurrencyKey.c_str(), newCount);
    }
    
    void Player::removeCurrency(int amount)
    {
        int newCount = getCurrencyAmount() - amount;
        UserDefault::getInstance()->setIntegerForKey(kCurrencyKey.c_str(), newCount);
    }
}