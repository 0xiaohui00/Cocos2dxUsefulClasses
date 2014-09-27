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
 * �ȵ��� setEffect ��������shader���룬�ٵ��� setEffect ѡ��Ч��
 */
class FragmentEffect
{
public:
	///����shader����
	bool setShaderProgram(CCNode*);

	///ѡ��Ч��
	void setEffect(int sel)
	{
		m_program->use();
		m_program->setUniformLocationWith1i(m_maxSel,sel);
	}

	///ѡ��Ч��
	void setEffect(EffectSelect sel)
	{
		m_program->use();
		m_program->setUniformLocationWith1i(m_maxSel,sel);
	}

private:
	GLint		 m_maxSel;
	CCGLProgram* m_program;
};

#endif
