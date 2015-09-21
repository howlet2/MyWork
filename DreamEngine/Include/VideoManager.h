#pragma once
#include "EngineObject.h"
#include "HardwareBuffer.h"
#include "Texture.h"
#include "Singleton.h"

namespace DreamEngine
{

class _EngineExport CVideoManager : public CEngineObject, public CSingleton<CVideoManager>
{

public:

	static CVideoManager&		instance(void);
	static CVideoManager*		instancePtr(void);

	CVideoManager(void);
	virtual ~CVideoManager(void);

	virtual	void			destoryAll(void);

	virtual CIndexBuffer*	createIndexBuffer(HardwareBufferType type=TRIANGLE_LIST)=0;

	virtual CIndexBuffer*	createIndexBuffer(void* pDate,
											 m_uint16 dataCount, 
											 m_uint16 strade, 
											 HardwareBufferType type=TRIANGLE_LIST)=0;

	virtual CVertexBuffer*	createVertexBuffer(void* pDate, 
											  m_uint16 dataCount, 
											  m_uint16 strade, 
											  HardwareBufferType type=TRIANGLE_LIST)=0;

	virtual CTexture*		createTexture(const CString&	name,
										  TEX_FORMAT		texFormat, 
										  m_uint16			width, 
										  m_uint16			height, 
										  RSPOOL			pool=RSP_MANAGER,
										  m_dwrd			usage=0, 
										  m_uint16			mipLevel=0)=0;

	virtual CTexture*		createTextureFromFile(const CString&	name,
												  const CString&	fileName, 
												  TEX_FORMAT		texFormat=TF_UNKOWN, 
												  m_uint16			width=0, 
												  m_uint16			height=0,
												  RSPOOL			pool=RSP_MANAGER,
												  m_dwrd			usage=0, 
												  m_uint16			mipLevel=0)=0;
	
protected:


	typedef std::list<CIndexBuffer*> IndexBufferLst;
	IndexBufferLst		m_indexBuffers;

	typedef std::list<CVertexBuffer*> VertexBufferLst;
	VertexBufferLst		m_vertexBuffers;

	typedef std::list<CTexture*> TextureLst;
	TextureLst			m_textures;
};


template<> CVideoManager* CSingleton<CVideoManager>::m_singleton = 0;


}

