#include "Joystick.h"

USING_NS_CC;

Joystick* Joystick::create(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
    Joystick *joystick = new Joystick();
    if (joystick && joystick->init(fnBg,bgRadius,fnHandle,handleRadius))
    {
        joystick->autorelease();
        return joystick;
    }

    CC_SAFE_DELETE(joystick);
    return NULL;
}

bool Joystick::init(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
	//�������̾���
	m_bg = CCSprite::create(fnBg);
	if(!m_bg)
		return false;
	this->addChild(m_bg);

	//����ҡ�˾���
	m_handle = CCSprite::create(fnHandle);
	if(!m_handle)
		return false;
	this->addChild(m_handle);
	
	//��ʼ������
	m_touchEventListener = 0;
    m_touchEventSelector = 0;
	m_bgRadius     = bgRadius;
	m_handleRadius = handleRadius;
	m_handlePos    = ccp(0.0f,0.0f);

	//���õ��̵Ĵ�С
	float bgDiameter = bgRadius * 2;
	CCSize oriBgSize = m_bg->getContentSize();
	m_bg->setScaleX(bgDiameter / oriBgSize.width);
	m_bg->setScaleY(bgDiameter / oriBgSize.height);

	//����ҡ�˵Ĵ�С
	float handleDiameter = handleRadius * 2;
	CCSize oriHandleSize = m_handle->getContentSize();
	m_handle->setScaleX(handleDiameter / oriHandleSize.width);
	m_handle->setScaleY(handleDiameter / oriHandleSize.height);

	//���ö�ʱ��
	this->schedule(schedule_selector(Joystick::callHandleEvent));

	return true;

}

bool Joystick::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = this->convertTouchToNodeSpaceAR(pTouch);
	
	//�жϴ����Ƿ���ҡ����
	if(point.x*point.x+point.y*point.y < m_handleRadius*m_handleRadius)
	{
		m_bMove = true;

		CCPoint pos = m_handle->getPosition();
		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_BEGIN);
		
		return true;
	}
	else
		return false;
}

void Joystick::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//��ҡ�������ڵ��̵ķ�Χ��
	CCPoint point = this->convertTouchToNodeSpaceAR(pTouch);

	if(point.x*point.x+point.y*point.y > m_bgRadius*m_bgRadius)
	{
		point = point.normalize();
		point = point * m_bgRadius;
	}

	m_handle->setPosition(point);
}

void Joystick::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos = m_handle->getPosition();
	if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_END);

	m_handle->setPosition(ccp(0.0f,0.0f));

	m_bMove = false;
}

void Joystick::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos = m_handle->getPosition();
	if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_END);
	
	m_handle->setPosition(ccp(0.0f,0.0f));

	m_bMove = false;
}

void Joystick::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void Joystick::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void Joystick::callHandleEvent(float interval)
{
	if(m_bMove)
	{
		//����ҡ���¼���������
		CCPoint point = m_handle->getPosition();

		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(interval,point.x/m_bgRadius,point.y/m_bgRadius,JET_TOUCH_MOVE);
	}
}