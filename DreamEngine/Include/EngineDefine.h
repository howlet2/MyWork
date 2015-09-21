#pragma once
#include <string>

namespace DreamEngine
{

#pragma warning( disable : 4251 )

#define		_EngineExport	__declspec( dllexport )
#define		DynLibHandle	void*

#ifndef		SAFE_DELETE
#define		SAFE_DELETE(p)       { if(p) {delete (p);(p)=MATH_NULL;}}
#endif

#ifndef		SAFE_DELETE_ARRY
#define		SAFE_DELETE_ARRY(p)  { if(p) {delete []p; p=MATH_NULL;}}
#endif

#ifndef		SAFE_RELEASE
#define		SAFE_RELEASE(p)		 { if(p) {p->Release();}}
#endif

#define		FLAG_TO_STRING(vaule) #vaule
#define     FLAG_LINK_FLAG_STRING(pre, vaule) #pre###vaule
#define     TWO_VAULE_LINK(vaule1, vaule2) vaule1##vaule2

typedef std::string CString;
typedef void (*DLL_PLUGIN_FUNC)(void);

#ifdef WIN32

#define HWINDOW							HWND
#define LoadLib(strName)				::LoadLibrary(strName)
#define FreeLib(hInst)					::FreeLibrary(HMODULE(hInst))
#define GetLibSymbol(hInst, strName)	::GetProcAddress(HMODULE(hInst), strName )

#endif 

}