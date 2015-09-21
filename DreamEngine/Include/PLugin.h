#pragma once
#include "EngineObject.h"

namespace DreamEngine
{
class _EngineExport CPLugin : public CEngineObject
{
public:
	CPLugin(void);
	virtual ~CPLugin(void);

	virtual const CString&	getName() const = 0;
	virtual void			install() = 0;
	virtual void			initialise() = 0;
	virtual void			uninstall() = 0;
};
}


