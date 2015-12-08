#pragma once
#include "EngineObject.h"
#include "Singleton.h"
#include "MS3DMeshLoader.h"
#include "OgreMeshLoader.h"
#include "DreamMeshLoader.h"

namespace DreamEngine
{

class CMeshManager : public CEngineObject, public CSingleton<CMeshManager>
{
public:
	CMeshManager(void);
	~CMeshManager(void);

	static CMeshManager&	instance(void);
	static CMeshManager*	instancePtr(void);

	CMesh*		create(const CString& name);
	CMesh*		createFromFile(const CString& name, const CString& fileName);

	void		destory(const CString& name);
	void		destroyAll(void);

protected:

	CMeshLoader*	m_pMeshLoader;

	typedef	std::vector<CMesh*>	MeshLst;
	MeshLst			m_meshs;

	typedef std::map<CString, CMesh*> FileMeshLst;
	FileMeshLst		m_filesOfMeshs;
};

template<> CMeshManager* CSingleton<CMeshManager>::m_singleton = 0;
}

