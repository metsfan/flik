//
//  GamePiece.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#include "GamePiece.h"
#include "SideRailNode.h"
#include "MainGameScene.h"
#include "Physics.h"
#include "Player.h"
#include "Events.h"
#include "Literals.h"
#include "SpawnRandomizer.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    static std::string PieceSprites[] = {
        "piece_red.png",
        "piece_blue.png",
        "piece_pink.png",
        "piece_yellow.png"
    };
    
    static const float kDeceleration = 0.7;
    
    static const float kVelocityEpsilon = 20.0f;
    
    GamePiece* GamePiece::create(const cocos2d::Vec2& position, GamePieceType pieceType)
    {
        return createWithParams<GamePiece>(position, pieceType);
    }
    
    bool GamePiece::init(const Vec2& position, GamePieceType pieceType)
    {
        if (!Node::init())
        {
            return false;
        }
        
        //setGlobalZOrder(0);
        setContentSize(Size(50.0_dp, 50.0_dp));
        setPosition(position);
        setAnchorPoint(Vec2(0.5, 0.5));
        ignoreAnchorPointForPosition(false);
        
        if (pieceType == GamePieceType::RandomPiece) {
            pieceType = (GamePieceType) SpawnRandomizer::getInstance()->getRandomId();
        }
        
        auto sprite = Sprite::create(PieceSprites[(int)pieceType]);
        sprite->setAnchorPoint(Vec2(0, 0));
        //sprite->setGlobalZOrder(0);
        
        addChild(sprite);
        
        auto physicsBody = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
        physicsBody->setGravityEnable(false);
        physicsBody->setRotationEnable(false);

        physicsBody->setCollisionBitmask(collision::PieceCollisionMasks[(int)pieceType]);
        physicsBody->setContactTestBitmask(collision::PieceContactMasks[(int)pieceType]);
        physicsBody->setCategoryBitmask(collision::PieceCategoryMasks[(int)pieceType]);
        setPhysicsBody(physicsBody);
        mPhysicsBody = physicsBody;
        
        mType = physicsBody->getCategoryBitmask();
        
        this->scheduleUpdate();
        

        return true;
    }
    
    void GamePiece::update(float delta)
    {
        Node::update(delta);
        
        auto velocity = mPhysicsBody->getVelocity();
        if (fabsf(velocity.x) < kVelocityEpsilon && fabsf(velocity.y) < kVelocityEpsilon) {
            mPhysicsBody->setVelocity(Vec2());
        } else {
            auto deltaVelocity = velocity * (delta * kDeceleration);
            mPhysicsBody->setVelocity(velocity - deltaVelocity);
        }
    }
    
    bool GamePiece::onContactBegin(PhysicsContact& contact)
    {
        return true;
    }
    
    void GamePiece::onPostContactSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    {
        if (contact.getShapeA() == mPhysicsBody->getShape(0) ||
            contact.getShapeB() == mPhysicsBody->getShape(0)) {
            mPhysicsBody->setVelocity(Vec2(0, 0));
        }
    }
    
    Rect GamePiece::getTouchBoundingBox()
    {
        auto bb = getBoundingBox();
        double padding = 20.0_dp;
        bb.setRect(bb.origin.x - padding, bb.origin.y - padding, bb.size.width + (padding * 2), bb.size.height + (padding * 2));
        return bb;
    }
}