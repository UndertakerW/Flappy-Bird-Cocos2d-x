#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setGravity( Vect( 0, 0 ) );
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	// Screen parameters
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Background
	this->SetupBackground(visibleSize, origin);
    
	// Boundary
	this->SetupBoundary(visibleSize, origin);

	// Init bird
	this->bird = new Bird(this);
    
	// Init pipes
    this->schedule( schedule_selector( GameScene::SpawnPipe ), PIPE_SPAWN_FREQUENCY * visibleSize.width );
    this->scheduleUpdate( );

	// Add listeners
	this->AddListeners();
    
    return true;
}

void GameScene::SetupBackground( Size visibleSize, Vec2 origin )
{
	auto backgroundSprite = Sprite::create( BG_SPRITE );
	backgroundSprite->setPosition( Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
	this->addChild ( backgroundSprite );
}

void GameScene::SetupBoundary( Size visibleSize, Vec2 origin )
{
	auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
	edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
	edgeBody->setContactTestBitmask( true );

	auto edgeNode = Node::create();
	edgeNode->setPosition( Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

	edgeNode->setPhysicsBody( edgeBody );

	this->addChild( edgeNode );
}

void GameScene::AddListeners()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::SpawnPipe( float dt )
{
    pipe.SpawnPipe( this );
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    
    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        auto scene = GameOverScene::createScene( );
        
        Director::getInstance( )->replaceScene( scene );
    }
    
    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
    bird->Fly( );
    
    this->scheduleOnce( schedule_selector( GameScene::StopFlying ), BIRD_FLY_DURATION );
    
    return true;
}

void GameScene::StopFlying( float dt )
{
    bird->StopFlying( );
}

void GameScene::update( float dt )
{
    bird->Fall( );
}










