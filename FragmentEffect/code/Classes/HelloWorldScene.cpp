#include "HelloWorldScene.h"




CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	//���ǲ˵����ã����Բ���
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
	
	CCMenuItemFont* MIF0 = CCMenuItemFont::create("ES_NONE");
	MIF0->setColor(ccRED);
	MIF0->setTag(0);
	CCMenuItemFont* MIF1 = CCMenuItemFont::create("ES_BLACK_AND_WHITE");
	MIF1->setColor(ccRED);
	MIF1->setTag(0);
	CCMenuItemFont* MIF2 = CCMenuItemFont::create("ES_OLD_PHOTOS");
	MIF2->setColor(ccRED);
	MIF2->setTag(0);
	CCMenuItemFont* MIF3 = CCMenuItemFont::create("ES_INVERT");
	MIF3->setColor(ccRED);
	MIF3->setTag(0);
	CCMenuItemFont* MIF4 = CCMenuItemFont::create("ES_BURNS");
	MIF4->setColor(ccRED);
	MIF4->setTag(0);
	CCMenuItemFont* MIF5 = CCMenuItemFont::create("ES_POISONING");
	MIF5->setColor(ccRED);
	MIF5->setTag(0);
	CCMenuItemFont* MIF6 = CCMenuItemFont::create("ES_COLD");
	MIF6->setColor(ccRED);
	MIF6->setTag(0);
	m_sel = CCMenuItemToggle::createWithTarget(this,
											menu_selector(HelloWorld::toggleCallback),
											MIF0,MIF1,MIF2,MIF3,MIF4,MIF5,MIF6,
											NULL);
	m_sel->setTag(0);
	m_sel->setAnchorPoint(ccp(0.5f,1.0f));
	m_sel->setPosition(ccp(visibleSize.width/2, visibleSize.height-7));
	
	CCMenuItemImage* last = CCMenuItemImage::create("lastNor.png","lastCli.png",0,this,menu_selector(HelloWorld::toggleCallback));
	last->setTag(-1);
	last->setAnchorPoint(ccp(0.5f,1.0f));
	last->setPosition(ccp(visibleSize.width/10*1, visibleSize.height));
	CCMenuItemImage* next = CCMenuItemImage::create("nextNor.png","nextCli.png",0,this,menu_selector(HelloWorld::toggleCallback));
	next->setTag(1);
	next->setAnchorPoint(ccp(0.5f,1.0f));
	next->setPosition(ccp(visibleSize.width/10*9, visibleSize.height));


    CCMenu* pMenu = CCMenu::create(pCloseItem,m_sel,last,next,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


    CCSprite* sprite= CCSprite::create("HelloWorld.png");
    sprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite, 0);
	
	//���ع�������
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Hero0.png","Hero0.plist","Hero.ExportJson");
	CCArmature *armature = CCArmature::create("Hero");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(visibleSize.width/2, 0.0f));
	armature->setAnchorPoint(ccp(0.5f,0.0f));
	this->addChild(armature,1);

	//�����������Ч���ģ�toggleCallback��������Ҳ��
	m_spriteEffect.setShaderProgram(armature);

    return true;
	
}

void HelloWorld::toggleCallback(CCObject* pSender)
{
	
	int sel = m_sel->getSelectedIndex();

	int tag = ((CCNode*)pSender)->getTag();

	if(tag<0)
	{
		sel--;
		if(sel<0)
			sel = 6;

		m_sel->setSelectedIndex(sel);
	}
	else if(tag>0)
	{
		sel++;
		sel%=7;

		m_sel->setSelectedIndex(sel);
	}

	m_spriteEffect.setEffect(sel);
	
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
