#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe( )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Pipe::SpawnPipe( cocos2d::Layer *layer )
{
    auto topPipe = Sprite::create( PIPE_SPRITE );
    auto bottomPipe = Sprite::create( PIPE_SPRITE );

	topPipe->setScaleX( PIPE_WIDTH );
	bottomPipe->setScaleX (PIPE_WIDTH );
    
    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize( ) );
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize( ) );
    
    double random = CCRANDOM_0_1( );

	random = std::min(std::max(random, LOWER_SCREEN_PIPE_THRESHOLD), UPPER_SCREEN_PIPE_THRESHOLD);
    
    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize( ).height / 2 );
    
    topPipeBody->setDynamic( false );
    bottomPipeBody->setDynamic( false );
    
    topPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    bottomPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    topPipeBody->setContactTestBitmask( true );
    bottomPipeBody->setContactTestBitmask( true );
    
    topPipe->setPhysicsBody( topPipeBody );
    bottomPipe->setPhysicsBody( bottomPipeBody );

	auto flappyBird = Sprite::create( BIRD_SPRITE );
	flappyBird->setScale( BIRD_SCALE );
    
    topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize( ).width + origin.x, topPipePosition ) );
    bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( flappyBird->getContentSize( ).height*flappyBird->getScale() * PIPE_GAP ) - topPipe->getContentSize().height ) );
    
    layer->addChild( topPipe, 1 );
    layer->addChild( bottomPipe, 1 );
    
    auto topPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    auto bottomPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    topPipe->runAction( topPipeAction );
    bottomPipe->runAction( bottomPipeAction );
}







