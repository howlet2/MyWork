#pragma once
#include "Color.h"
#include "EngineDefine.h"
#include "EngineObject.h"
#include <sstream>

namespace DreamEngine
{

class _EngineExport CStringHelper : public CEngineObject 
{
public:
	CStringHelper(void);
	~CStringHelper(void);

	static bool			stringToBool(const CString& vaule);
	static CString		boolToString(bool vaule);

	static Math::CColor	stringToColor(const CString& vaule);
	static CString		colorToString(const Math::CColor& color);

	static int			stringToInt(const CString& vaule);
	static CString		intToString(int vaule);

	static bool			isWord(char ch);
	static bool			isNumber(char ch);

	static void			trimString(MATH_OUT CString& str, char trim='\n');

protected:

	static	std::stringstream	m_streamHelper;
};

}