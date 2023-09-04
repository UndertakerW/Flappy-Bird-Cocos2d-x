#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
	// Sprite
    sprite = Sprite::create( BIRD_SPRITE );
    sprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
	sprite->setScale( BIRD_SCALE );
	layer->addChild( sprite, 2 );
    
	// Physics
	auto physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    physicsBody->setCollisionBitmask( BIRD_COLLISION_BITMASK );
    physicsBody->setContactTestBitmask( true );
    sprite->setPhysicsBody( physicsBody );
    
    isFalling = true;
}

void Bird::Fall( )
{
    if ( true == isFalling )
    {
        sprite->setPositionX( visibleSize.width / 2 + origin.x );
        sprite->setPositionY( sprite->getPositionY() - ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
    else
    {
        sprite->setPositionX( visibleSize.width / 2 + origin.x );
        sprite->setPositionY( sprite->getPositionY() + ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
}




