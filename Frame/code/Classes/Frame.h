#ifndef _CHAT_FRAME_H_
#define _CHAT_FRAME_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

/**
 *  �Ի������
 *  ������,�������ʵ��setControls����,�����еĿؼ�push_back��m_controls��
 *  ����:��������λ���ڶԻ���֮�⣬�Զ����ضԻ��򣬲�ʹ���ڲ��ؼ����ɴ���
 */
class Frame : public CCObject,public CCTargetedTouchDelegate 
{
public:
	Frame();
	~Frame();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	bool isOutsideFrame(CCTouch *pTouch);

	///���öԻ����Ƿ�ɼ���ͬʱ���öԻ����еĿؼ��Ƿ�ɴ���(��ֹ�Ի��򲻿ɼ�,���ؼ����յ�������Ϣ)
	void setFrameVisble(bool bVisible);

	virtual bool init(UILayer* frameLayer,CCNode* frameBg);

	UILayer* getFrameLayer() {return m_frameLayer;}
protected:
	UILayer*   m_frameLayer;
	CCNode*    m_frameBg;
	CCSize     m_frameSize;
	CCPoint    m_anchorPoint;  ///<ê���ڱ�������ϵ������,���귶Χ��(0.0f,0.0f)��m_frameSize
	bool       m_bFrameVisible;
	std::vector<Widget*> m_controls;

	///���麯��,�������ʵ��,��m_frameLayer�����пؼ�push_back��m_controls��
	virtual void setControls() = 0;
};


class RegisterFrame : public Frame
{
public:
	bool init(UILayer* frameLayer,CCNode* frameBg);
private:
	void setControls();
};
#endif