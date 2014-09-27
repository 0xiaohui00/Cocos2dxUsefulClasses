#ifndef __SIMPLE_EFFECT_H__
#define __SIMPLE_EFFECT_H__

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"

USING_NS_CC;

enum EffectSelect{ES_NONE              = 0,  //û����Ч
				  ES_BLACK_AND_WHITE   = 1,  //�ڰ׻�
				  ES_OLD_PHOTOS        = 2,  //����Ƭ
				  ES_INVERT            = 3,  //����
				  ES_BURNS			   = 4,  //���ˣ�ƫ�죩
				  ES_POISONING		   = 5,  //�ж���ƫ�̣�
				  ES_COLD			   = 6}; //���䣨ƫ����

/**
 * �򵥵�Ƭ����ȾЧ��
 * �ȵ��� setEffect ��������ڵ�����shader���룬�ٵ��� setEffect ѡ��Ч��
 */
class FragmentEffect
{
public:
	///����shader����
	bool setShaderProgram(CCNode*);

	///ѡ��Ч��
	void setEffect(int sel);

	///ѡ��Ч��
	void setEffect(EffectSelect sel);

private:
	CCGLProgram* m_program;
	GLint		 m_matrixEffect;
};

#endif
