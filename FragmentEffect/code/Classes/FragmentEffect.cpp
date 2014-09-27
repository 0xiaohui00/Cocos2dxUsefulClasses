#include "FragmentEffect.h"

const GLchar* pszFragSource =
				"#ifdef GL_ES													\n \
				precision mediump float;										\n \
				#endif															\n \
				uniform sampler2D u_texture;									\n \
				uniform int sel;												\n \
				varying vec2 v_texCoord;										\n \
				varying vec4 v_fragmentColor;									\n \
				const mat4 m[7] = {mat4(1.0, 0.0, 0.0, 0.0,						\n \
										0.0, 1.0, 0.0, 0.0,						\n \
										0.0, 0.0, 1.0, 0.0,						\n \
										0.0, 0.0, 0.0, 1.0),					\n \
																				\n \
								   mat4(0.299, 0.587, 0.184, 0.0,				\n \
										0.299, 0.587, 0.184, 0.0,				\n \
										0.299, 0.587, 0.184, 0.0,				\n \
										0.0,   0.0,   0.0,   1.0),				\n \
																				\n \
							       mat4(0.299, 0.587, 0.184, 0.3137,			\n \
										0.299, 0.587, 0.184, 0.1686,			\n \
										0.299, 0.587, 0.184,-0.0901,			\n \
										0.0,   0.0,   0.0,   1.0),				\n \
																				\n \
								   mat4(-1.0, 0.0, 0.0, 1.0,				    \n \
										 0.0,-1.0, 0.0, 1.0,				    \n \
										 0.0, 0.0,-1.0, 1.0,				    \n \
										 0.0, 0.0, 0.0, 1.0),			        \n \
																				\n \
								   mat4(1.0,  0.0, 0.0, 0.0,				    \n \
										0.0,  0.6, 0.0, 0.0,				    \n \
										0.0,  0.0, 0.6, 0.0,				    \n \
										1.0,  0.0, 0.0, 1.0),			        \n \
																				\n \
								   mat4(0.6, 0.0, 0.0, 0.0,				        \n \
										0.0,  1.0, 0.0, 0.0,				    \n \
										0.0,  0.0, 0.6, 0.0,				    \n \
										0.0,  1.0, 0.0, 1.0),			        \n \
																				\n \
								   mat4(0.6,  0.0, 0.0, 0.0,				    \n \
										0.0,  0.6, 0.0, 0.0,				    \n \
										0.0,  0.0, 1.0, 0.0,				    \n \
										0.0,  0.0, 1.0, 1.0)};			        \n \
				void main(void)													\n \
				{																\n \
					gl_FragColor = mul(texture2D(u_texture, v_texCoord),m[sel]);\n \
				}";

bool FragmentEffect::setShaderProgram(CCNode* pNode)
{
	do
	{
		m_program = new CCGLProgram();
		
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
		m_maxSel =  m_program->getUniformLocationForName("sel");
		m_program->setUniformLocationWith1i(m_maxSel,0);

		return true;

	} while (0);
	
	return false;
}

