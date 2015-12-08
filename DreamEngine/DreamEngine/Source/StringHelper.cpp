#include "StringHelper.h"

namespace DreamEngine
{

std::stringstream CStringHelper::m_streamHelper;

CStringHelper::CStringHelper(void)
{
}

CStringHelper::~CStringHelper(void)
{
	m_streamHelper.str("");
}

bool CStringHelper::stringToBool(const CString& vaule)
{
	if (vaule!=CString("true") && vaule!=CString("TRUE"))
	{
		return false;
	}

	return true;
}

CString	CStringHelper::boolToString(bool vaule)
{
	CString res;

	m_streamHelper.clear();
	m_streamHelper << vaule;
	m_streamHelper >> res;

	return res;
}

Math::CColor CStringHelper::stringToColor(const CString& vaule)
{
	Math::CColor res;

	m_streamHelper.clear();
	m_streamHelper << vaule;
	m_streamHelper >> res._r >> res._g >> res._b >> res._a;

	return res;
}

CString CStringHelper::colorToString(const Math::CColor& color)
{
	CString res;

	m_streamHelper.clear();
	m_streamHelper.str("");
	m_streamHelper << color._r << " " << color._g << " " << color._b << " " << color._a;
	res.assign(m_streamHelper.str().c_str());

	return res;
}

int CStringHelper::stringToInt(const CString& vaule)
{
	m_streamHelper.clear();
	m_streamHelper.str("");

	int vRes = 0;
	m_streamHelper << vaule;
	m_streamHelper >> vRes;

	return vRes;
}

CString CStringHelper::intToString(int vaule)
{
	m_streamHelper.clear();
	m_streamHelper.str("");

	CString vRes;
	m_streamHelper << vaule;
	m_streamHelper >> vRes;

	return vRes;
}

bool CStringHelper::isWord(char ch)
{
	return ('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z');
}

bool CStringHelper::isNumber(char ch)
{
	return ('0'<=ch && ch<='9');
}

void CStringHelper::trimString(CString& str, char trim/*='\n'*/)
{
	int pos = str.find(trim, 0);
	if (pos > 0 )
		str.erase(pos, str.length()-pos);
	
}

void CStringHelper::split(MATH_OUT StringLst& stringLst, const CString& str, char split/* =' ' */)
{
	CString::size_type i;
	CString temp;
	for (i=0; i<str.length(); ++i)
	{
		if (str[i] != split)
		{
			temp.push_back(str[i]);
		}
		else
		{
			stringLst.push_back(temp);
			temp.clear();
		}
	}
	if (temp.length()>0)
		stringLst.push_back(temp);
}

// void CStringHelper::stringLstToIntLst(MATH_OUT IntLst& ints, const StringLst& strings)
// {
// 	ints.clear();
// 
// 	for (auto iter=strings.begin(); iter!=strings.end(); ++iter)
// 		ints.push_back(stringToInt(*iter));
// }

}