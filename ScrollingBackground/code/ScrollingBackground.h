#ifndef __SCROLLING_BACKGROUND_H__
#define __SCROLLING_BACKGROUND_H__

#include "cocos2d.h"
USING_NS_CC;

typedef void (CCObject::*SEL_RemoveBgBlockEvent)();
#define removeBgBlockEvent_selector(_SELECTOR) (SEL_RemoveBgBlockEvent)(&_SELECTOR)

///���������ķ���
enum ScrollDirection{SD_RIGHT_TO_LEFT,SD_LEFT_TO_RIGHT,SD_TOP_TO_BOTTOM,SD_BOTTOM_TO_TOP};

///����������ģʽ
enum ScrollType{
	///�������������ÿ������ֻ����һ�Σ�������Ļ�����
	///���Ե���setRemoveEventListener���ûص���������һ�����汻������ٵ���addBackgroundBlock����һ���µĻ��浽�б�β��
	ST_ONE_WAY,
	
	///����ѭ�����������������һ������֮�����ص�һ������
	///��Ҫ�ڵ���beginScroll֮ǰ����addBackgroundBlock���ú�����һ������
	ST_CYCLE};


///�ڵ㴢�����Ա�ST_ONE_WAYģʽΪ������,ST_CYCLEģʽΪ����ѭ���б�
struct NodeList{
	CCNode* _pNode;
	NodeList* _next;

	NodeList():
		_pNode(0),
		_next(0)
	{}
};

/**
 *  ��������
 *  �е��������ѭ����������ģʽ
 *  ����addBackgroundBlock���ӻ���,����beginScroll��ʼ����
 *  ������Ҫ�������������ȷ����
 */
class ScrollingBackground : public CCNode
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground();

	///���ӱ�������,����Ľڵ���Զ�����������Ļ
	bool addBackgroundBlock(CCNode* bgBlock);

	///��ʼ����
	bool beginScroll();

	///��ͣ����
	void pauseScroll()  {m_isScrolling = false;}

	///�ָ�����
	void resumeScroll() {m_isScrolling = true;}

	///��ֻ��ST_ONE_WAYģʽ�����ã����ӻ��������ʱ��Ļص�����,��һ�����������Ļ֮������selector
	///��������ʱ��addBackgroundBlock�����µĻ��浽�б�β��
	void setRemoveEventListener(CCObject *target, SEL_RemoveBgBlockEvent selector);

	/**
	 *  һ����̬����,���ڴ���ScrollingBackground
	 *@param type ����ģʽ
	 *@param ScrollDirection �������� 
	 *@param velocity �������ٶ�
	 */
	static ScrollingBackground* create(ScrollType type,ScrollDirection direct,float velocity);
protected:
	ScrollDirection m_direct;        ///<��������
	ScrollType		m_type;			 ///<����ģʽ
	NodeList*		m_blockList;     ///<�ڵ㴢�����Ա�
	NodeList*		m_lastListNode;  ///<���Ա��β��
	NodeList*		m_thisListNode;  ///<��ǰ��������Ļ�ϵ����������ǰһ�����ȹ�����Ļ���Ǹ���
	CCSize			m_visibleSize;   ///<������Ļ�Ĵ�С,���ڽ������������ŵ�������Ļ
	float           m_velocity;      ///<�������ٶ�
	bool			m_isScrolling;   ///<�Ƿ����ڹ���

	CCObject*              m_eventListener;
    SEL_RemoveBgBlockEvent m_eventSelector;

	bool init(ScrollType type,ScrollDirection direct,float velocity);

	///�����ڵ㲢���ڵ�����б�
	void addListNode(CCNode* bgBlock);

	///һ������moveby��ɺ�Ļص�����
	void nodeOutEvent();

	///ÿһ֡����һ��,���û����λ��
	void moveAction(float d);

	///���õڶ��������λ��
	void setLastNodePosition();

	///�ж�һ�������Ƿ�����Ļ��Χ��
	bool isOutOfScreen(const CCPoint& pos,const CCPoint& achorPoint);
};

inline void ScrollingBackground::setRemoveEventListener(CCObject *target, SEL_RemoveBgBlockEvent selector)
{
	m_eventListener = target;
	m_eventSelector = selector;
}

#endif