#ifndef __SCROLLING_BACKGROUND_H__
#define __SCROLLING_BACKGROUND_H__

#include "cocos2d.h"
#include <list>
USING_NS_CC;

typedef std::list<CCNode*> NodeList;
typedef std::list<CCNode*>::iterator ListIter;

typedef void (CCObject::*SEL_ChangeBgBlockEvent)(CCNode* cur,CCNode* follow,CCNode* leave);
#define removeBgBlockEvent_selector(_SELECTOR) (SEL_ChangeBgBlockEvent)(&_SELECTOR)

///���������ķ���
enum ScrollDirection{SD_RIGHT_TO_LEFT,SD_LEFT_TO_RIGHT,SD_TOP_TO_BOTTOM,SD_BOTTOM_TO_TOP};

/**
 *  ��������
 *  ����addBackgroundBlock���ӻ���,���ÿ�ʼ����
 *  ������Ҫ�������������ȷ����
 */
class ScrollingBackground : public CCNode
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground();

	/**
	 * ���ӱ�������,����Ľڵ���Զ�����������Ļ,���ӵ�����β
	 * ����һ�߹���һ�����ӱ�������ڵ�,�����ǰ�ڵ�������β,��ʧ�ܲ�����false
	 */
	bool addBackgroundBlock(CCNode* bgBlock);

	///��ʼ��������
	bool beginContinuousScroll(float velocity)    {return beginScroll(velocity);}

	///�������������������ڵ��е�һ�������뿪��Ļ
	bool scrollToNextBgBlock(float velocity);

	///���ñ����ƶ��趨�ľ���
	bool setBgBlockScrollBy(float velocity,float distance);

	///��ͣ����
	void pauseScroll()  {m_isScrolling = false;}

	///�ָ�����
	void resumeScroll(float velocity);

	///�Ƴ������ڵ�,�����뱣֤�ڵ������ڵĽڵ�������2,�Ҳ����Ƴ���ǰ��ʾ����Ļ�ڵ������ڵ�
	bool removeBgBlock(CCNode* bgBlock);

	///���ñ���ȫ��������ʾ
	void setFullScreen(CCNode* bgBlock);

	void setVelocity(float velocity)   {m_velocity = velocity;}

	bool isListBack(CCNode* bgBlock)   {return bgBlock == m_bgBlockList.back();}
	bool isListFront(CCNode* bgBlock)  {return bgBlock == m_bgBlockList.front();}
	
	CCNode* getBackBgBlock()		   {return m_bgBlockList.back();}
	CCNode* getFrontBgBlock()		   {return m_bgBlockList.front();}
	CCNode* getCurBgBlock()			   {return m_curIter!=m_bgBlockList.end() ? (*m_curIter):0;}
	CCNode* getFollowBgBlock()		   {return m_followIter!=m_bgBlockList.end() ? (*m_followIter):0;}
	
	/**
	 * ��һ�����泹���뿪��Ļ��ʱ��ᷢ�������Ϣ
	 * SEL_ChangeBgBlockEvent �� CCNode ������������Ļ�ڵ�������ͼ�ڵ�
	 */
	void setChangeBgEventListener(CCObject *target, SEL_ChangeBgBlockEvent selector);

	/**
	 *  һ����̬����,���ڴ���ScrollingBackground
	 *@param type ����ģʽ
	 *@param ScrollDirection �������� 
	 */
	static ScrollingBackground* create(ScrollDirection direction);
protected:
	ScrollDirection m_direction;     ///<��������
	NodeList		m_bgBlockList;   ///<�ڵ㴢������
	ListIter		m_curIter;       ///<��ǰ��������Ļ�ϵ����������ǰһ�����������ȹ�����Ļ���Ǹ���
	ListIter		m_followIter;    ///<��ǰ��������Ļ�ϵ���������ĺ�һ�������滭�棨������������Ļ���Ǹ���
	CCSize			m_visibleSize;   ///<������Ļ�Ĵ�С,���ڽ������������ŵ�������Ļ
	bool			m_isScrolling;   ///<�Ƿ����ڹ���
	bool		    m_bScrollToNext; ///<�Ƿ������˱������������������ڵ��е�һ�������뿪��Ļ
	bool			m_bScrollBy;     ///<�Ƿ��趨��������һ������
	float           m_velocity;      ///<�������ٶ�
	float			m_distance;      ///<�趨��������ƶ�����
	CCObject*              m_eventListener;
    SEL_ChangeBgBlockEvent m_eventSelector;

	bool init(ScrollDirection direct);

	///�����ڵ㲢���ڵ�����б�
	void addListNode(CCNode* bgBlock);

	///һ������moveby��ɺ�Ļص�����
	void changeCurBgBlock();

	///ÿһ֡����һ��,���û����λ��
	void moveAction(float d);

	///���ø��滭���λ��
	void setFollowNodePosition();

	///�ж�һ�������Ƿ�����Ļ��Χ��
	bool bChangeBg(const CCPoint& posCur,const CCPoint& achorPointCur);

	///���ٶ�Ϊ����ʱ��,Ҫ��������һʱ�� m_curIter ��ָ��ı����ڵ��λ��
	void preSetCurPos();

	///������ʱ��Ĺ�������
	bool beginScroll(float velocity);
};

inline void ScrollingBackground::setChangeBgEventListener(CCObject *target, SEL_ChangeBgBlockEvent selector)
{
	m_eventListener = target;
	m_eventSelector = selector;
}

inline void ScrollingBackground::resumeScroll(float velocity) 
{
	m_velocity = velocity;
	m_isScrolling = true;
}

#endif