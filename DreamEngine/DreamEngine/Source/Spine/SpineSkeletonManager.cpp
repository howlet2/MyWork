#include "SpineSkeletonManager.h"


namespace DreamEngine
{

CSpineSkeletonManager::CSpineSkeletonManager(void)
{
}


CSpineSkeletonManager::~CSpineSkeletonManager(void)
{
}


CSpineSkeleton* CSpineSkeletonManager::createFromFile(const CString& name, const CString& fileName)
{
	CSpineSkeleton* pSkeleton = new CSpineSkeleton(name);
	pSkeleton->loadFromFile(fileName);
	return pSkeleton;
}

}