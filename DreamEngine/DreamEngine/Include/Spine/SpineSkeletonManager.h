#pragma once
#include "EngineObject.h"
#include "ResourceFactory.h"
#include "SpineSkeleton.h"

namespace DreamEngine
{

class _EngineExport CSpineSkeletonManager : public CRosourceFactory<CSpineSkeleton>
{
public:
	CSpineSkeletonManager(void);
	~CSpineSkeletonManager(void);


	CSpineSkeleton*		createFromFile(const CString& name, const CString& fileName);
};


}