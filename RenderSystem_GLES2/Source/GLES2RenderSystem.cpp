#include "GLES2RenderSystem.h"
#include "CommonFunction.h"
#include "GLES2IndexBuffer.h"
#include "GLES2GLSLProgram.h"

namespace DreamEngineGLES2
{


CGLES2RenderSystem::CGLES2RenderSystem(void):
m_pEglView(MATH_NULL)
{
}


CGLES2RenderSystem::~CGLES2RenderSystem(void)
{
	
}

Error CGLES2RenderSystem::initialize()
{
	m_pEglView = new CEGLView;
	
	return ERROR_OK;
}

Error CGLES2RenderSystem::shutDown()
{
	SAFE_DELETE(m_pEglView)
	
	return ERROR_OK;
}

CRenderWindow* CGLES2RenderSystem::createRenderWindow(const CString& name,\
	m_uint16 width, m_uint16 heigth, bool isSetActive/*=true*/)
{
	CGLES2RenderWindow* pRenderWindow = new CGLES2RenderWindow(name);
	pRenderWindow->initialize(width, heigth);

	m_renderWindows.push_back(pRenderWindow);

	if (isSetActive != MATH_NULL)
	{
		m_pActiveWindow = pRenderWindow;

		if (m_pEglView != MATH_NULL)
		{
			m_pEglView->shutDown();
			m_pEglView->initializeEGL(m_pActiveWindow->getWindowModule());
		}
	}
	
	return pRenderWindow;
}

void CGLES2RenderSystem::beginFrame()
{
	CViewport* pViewport = m_pActiveWindow->getViewport();
	if (pViewport!=MATH_NULL && pViewport->isChanged())
	{
		_setViewport(pViewport);
		pViewport->setChanged(false);
	}

	glClearColor(0,1,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void CGLES2RenderSystem::endFrame()
{
	if (m_pEglView != MATH_NULL)
	{
		m_pEglView->swapBuffers();
	}
}

GLint LoadShader(GLenum type, const char* shader)
{
	GLint  glShader = glCreateShader(type);							//1.����������ɫ��
	glShaderSource(glShader, 1, &shader, NULL);						//2.ָ����ɫ��Դ
	glCompileShader(glShader);										//3.������ɫ��

	/*GL_COMPILE_STATUS
	GL_DELETE_STATUS
	GL_INFO_LOG_LENGTH
	GL_SHADER_SOURCE_LENGTH
	GL_SHADER_TYPE
	*/
	GLint compiler;
	glGetShaderiv(glShader, GL_SHADER_COMPILER, &compiler);			//4.��ȡ������
	if (!compiler)
	{
		GLint infoLen;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &infoLen);		//5.��ȡ������־����
		if (infoLen > 0)
		{
			char* info = new char[infoLen];
			glGetShaderInfoLog(glShader, infoLen, NULL, info);		//6.��ȡ������־
			std::cout << info << std::endl;
			delete []info;
		}
		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}

//////////////////////////////////////////////////////////////////////////������Ŀ
GLuint CreateProgram(GLint vShader, GLint fShader)
{
	GLuint program = glCreateProgram();							//1.������Ŀ
	glAttachShader(program, vShader);							//2.�󶨶�����ɫ��
	glAttachShader(program, fShader);							//3.��Ƭ����ɫ��
	glLinkProgram(program);										//4.ʹ��������������Ŀ

	
	/*GL_ACTIVE_ATTRIBUTES
		GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
		GL_ACTIVE_UNIFORMS
		GL_ACTIVE_UNIFORM_MAX_LENGTH
		GL_ATTACHED_SHADERS
		GL_DELETE_STATUS
		GL_INFO_LOG_LENGTH
		GL_LINK_STATUS
		GL_VALIDATE_STATUS*/
	int link;
	glGetProgramiv(program, GL_LINK_STATUS, &link);				//5.��ȡ������Ϣ
	if (!link)
	{
		int len; 
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		if (len>0)
		{
			char* info = new char[len];
			glGetProgramInfoLog(program, NULL, &len, info);
			delete[]info;

			glDetachShader(program, vShader);
			glDetachShader(program, fShader);
			glDeleteProgram(program);
			return 0;
		}
	}
	return program;
}

void CGLES2RenderSystem::render(CRenderData* pRenderData)
{
  	if (pRenderData==MATH_NULL || pRenderData->isEmpty()) return;

  	_setRenderState(pRenderData->m_pMaterial);
 	_bulidDeclaration(pRenderData);
  	_activeVertexBuffer(pRenderData);
  	_updateShaderProgram(pRenderData->m_pMaterial);
	_draw(pRenderData);
	_endDraw(pRenderData);
}


void CGLES2RenderSystem::_setViewport(CViewport* pViewport)
{
	if (pViewport==MATH_NULL)return;

	glViewport(0, 0, pViewport->getWidth(), pViewport->getHeight());	
}

void CGLES2RenderSystem::_setRenderState(CMaterial* pMaterial)
{
	if (pMaterial==MATH_NULL)return;

	//glFrontFace(GL_CW);				//1.�趨�޳������淽��      Ĭ����CCW(��ʱ�룩
	//glCullFace(GL_FRONT);
// 	LPDIRECT3DDEVICE9 pDevice = GetActiveDevice()->GetD3DDevice();
// 	pDevice->SetRenderState(D3DRS_ZENABLE, pMaterial->GetZTestEnble());
// 	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL(pMaterial->GetCullMode()));	
// 	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE(pMaterial->GetFillMode()));
}

void CGLES2RenderSystem::_activeVertexBuffer(CRenderData* pRenderData)
{
	if (pRenderData==MATH_NULL)return;

	CRenderData::VertexStream::iterator iter;
	for (iter=pRenderData->m_vertexStream.begin(); 
		iter!=pRenderData->m_vertexStream.end(); ++iter)
	{
		iter->second->active(iter->first);
	}
}

void CGLES2RenderSystem::_updateShaderProgram(CMaterial* pMaterial)
{
	if (pMaterial==MATH_NULL) return;

	CGLES2GLSLProgram* pGpuProgram = static_cast<CGLES2GLSLProgram*>(pMaterial->getGpuProgram());
	glUseProgram(pGpuProgram->getGLESProgram());
	if (pGpuProgram != MATH_NULL)
		pGpuProgram->update();
}

void CGLES2RenderSystem::_bulidDeclaration(CRenderData* pRenderData)
{
	CGLES2GLSLProgram* pGpuProgram = static_cast<CGLES2GLSLProgram*>(pRenderData->m_pMaterial->getGpuProgram());
	CShaderParamTable* pAttributeParamTable = pGpuProgram->getAttributeParamTable();

	const CRenderData::ElementLst& elemLst = pRenderData->getElementLst();
	for (m_byte loc=0; loc<elemLst.size(); ++loc)
	{
		const CVertexElement& paramVaule = elemLst[loc]; 
		CString paramName = CCommonFunction::UsageToGLSLAttributeName(DREAMDDECLUSAGE(paramVaule.m_usage),
																	  paramVaule.m_usageIndex);
	//	glBindAttribLocation(pGpuProgram->GetGLESProgram(), loc, paramName.c_str());
		
		CShaderParamTable::ParamIter paramiter = pAttributeParamTable->getParamIter();
		while (paramiter.hasMore())
		{
			CShaderParam* pParam = paramiter.current();
			if (pParam->getName()==paramName) 
			{
				GLenum   paramType	= CCommonFunction::ParamTypeToGLES2DataType(pParam->getType());

				CVertexBuffer* pVertexBuffer = pRenderData->getVertexBuffer(0);
				if (pVertexBuffer!=MATH_NULL)
				{
					m_byte*  pBuffData =  static_cast<m_byte*>(pVertexBuffer->getBufferData());

					glVertexAttribPointer(loc, pParam->getElemCount(), paramType,
						GL_FALSE, pVertexBuffer->getStrade(), pBuffData+paramVaule.m_offset);

					glEnableVertexAttribArray(loc);
				}
			}
			paramiter.Next();
		}
	}
}

void CGLES2RenderSystem::_draw(CRenderData* pRenderData)
{
	if (pRenderData==MATH_NULL || pRenderData->isEmpty())return;

	if (!pRenderData->isUseIndexBuffer())				//��ʹ����������
	{
		int priType = CCommonFunction::HDBufTypeToGLES2PriType(pRenderData->getRenderType(0));
		m_uint16 dataCount = pRenderData->getVertexBuffer(0)->dataCount();
		glDrawArrays(priType, 0, dataCount);
	}
	else
	{
		for (m_uint16 i=0; i<pRenderData->getPatch(); ++i)
		{
			CGLES2IndexBuffer* pIdxBuf = static_cast<CGLES2IndexBuffer*>(pRenderData->getIndexBuffer(i));
			if (pIdxBuf != MATH_NULL)
			{
				pIdxBuf->active();

				int priType		= CCommonFunction::HDBufTypeToGLES2PriType(pRenderData->getRenderType(i));
				int idxBufType	= CCommonFunction::IdxBufTypeToElemDrawType(pIdxBuf->getBufferType());

				glDrawElements(priType,		pIdxBuf->dataCount(),
							   idxBufType,	pIdxBuf->getBufferData());
			}
			
		}
	}
}

void CGLES2RenderSystem::_endDraw(CRenderData* pRenderData)
{
	CGLES2GLSLProgram* pGpuProgram = static_cast<CGLES2GLSLProgram*>(pRenderData->m_pMaterial->getGpuProgram());
	CShaderParamTable* pAttributeParamTable = pGpuProgram->getAttributeParamTable();
	if (pAttributeParamTable != MATH_NULL)
	{
		CShaderParamTable::ParamIter paramiter = pAttributeParamTable->getParamIter();
		while (paramiter.hasMore())
		{
			CShaderParam* pParam = paramiter.current();
			GLuint local = pGpuProgram->getAttributeLocal(pParam->getName());
			glDisableVertexAttribArray(local);

			paramiter.Next();
		}
	}
	glUseProgram(0);
}
}