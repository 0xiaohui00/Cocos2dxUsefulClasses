#include "FragmentEffect.h"

GLfloat transformMatrix[][16] = 
{
	{
		1.0, 0.0, 0.0, 0.0,						
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	},

	{
		0.299, 0.587, 0.184, 0.0,
		0.299, 0.587, 0.184, 0.0,
		0.299, 0.587, 0.184, 0.0,
		0.0,   0.0,   0.0,   1.0
	},

	{
		0.299, 0.587, 0.184, 0.3137,
		0.299, 0.587, 0.184, 0.1686,
		0.299, 0.587, 0.184,-0.0901,
		0.0,   0.0,   0.0,   1.0
	},

	{
		-1.0, 0.0, 0.0, 1.0,
		0.0,-1.0, 0.0, 1.0,
		0.0, 0.0,-1.0, 1.0,
		0.0, 0.0, 0.0, 1.0
	},

	{
		1.0,  0.0, 0.0, 0.0,
		0.0,  0.6, 0.0, 0.0,
		0.0,  0.0, 0.6, 0.0,
		1.0,  0.0, 0.0, 1.0
	},

	{
		0.6, 0.0, 0.0, 0.0,
		0.0,  1.0, 0.0, 0.0,
		0.0,  0.0, 0.6, 0.0,
		0.0,  1.0, 0.0, 1.0
	},

	{
		0.6,  0.0, 0.0, 0.0,
		0.0,  0.6, 0.0, 0.0,
		0.0,  0.0, 1.0, 0.0,
		0.0,  0.0, 1.0, 1.0
	}
};

bool FragmentEffect::setShaderProgram(CCNode* pNode)
{
	do
	{
		m_program = new CCGLProgram();
		GLchar* pszFragSource =
				"#ifdef GL_ES													  \n \
				precision mediump float;										  \n \
				#endif															  \n \
				uniform sampler2D u_texture;									  \n \
				varying vec2 v_texCoord;										  \n \
				varying vec4 v_fragmentColor;									  \n \
				uniform mat4 matrixEffect;										  \n \
				void main(void)													  \n \
				{																  \n \
					gl_FragColor = texture2D(u_texture, v_texCoord)*matrixEffect; \n \
				}";

		m_program->initWithVertexShaderByteArray(ccPositionTextureColor_vert, //������ɫ��,�����������Դ���
												 pszFragSource);              //������ɫ��,�������Լ�д��

		//�����ɵ�shader���򴫸�CCSprite��
		pNode->setShaderProgram(m_program);
		
		//Ҫreleaseһ��,�������setShaderProgram��pProgram�йܸ�CCSprite
		//setShaderProgramֻ������pProgram->retain(),û��release(),����pProgram��m_uReference��2
		m_program->release();
		
		CHECK_GL_ERROR_DEBUG();
		
		//���ö�����ɫ����attribute���������ꡢ�������ꡢ��ɫ ,ȥ������һ�����������ܹ���
		m_program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		m_program->addAttribute(kCCAttributeNameColor,    kCCVertexAttrib_Color);
		m_program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		
		CHECK_GL_ERROR_DEBUG();

		//�Զ�����ɫ������
		m_program->link();
		CHECK_GL_ERROR_DEBUG();

		// �����ƶ������š���ת����  
		m_program->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		m_program->use();
		m_matrixEffect =  m_program->getUniformLocationForName("matrixEffect");
		m_program->setUniformLocationWithMatrix4fv(m_matrixEffect,transformMatrix[0],1);

		return true;

	} while (0);
	
	return false;
}

///ѡ��Ч��
void FragmentEffect::setEffect(int sel)
{
	m_program->use();
	m_program->setUniformLocationWithMatrix4fv(m_matrixEffect,transformMatrix[sel],1);
}

///ѡ��Ч��
void FragmentEffect::setEffect(EffectSelect sel)
{
	m_program->use();
	m_program->setUniformLocationWithMatrix4fv(m_matrixEffect,transformMatrix[sel],1);
}