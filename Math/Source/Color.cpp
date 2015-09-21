#include "Color.h"

namespace Math
{

CColor::CColor(void)
{
	_color = 0;
}

CColor::CColor(m_dwrd color)
{
	setColor(color);
}

CColor::CColor(m_byte r, m_byte g, m_byte b, m_byte a/* =255 */)
{
	setRed(r); setGreen(g); setBlue(b); setAlpha(a);
}

CColor::~CColor(void)
{
}

CFColor CColor::toFColor()
{
	CFColor fColor;
	float moudle = 1.0f/255;

	fColor._r = moudle*_r;
	fColor._g = moudle*_g;
	fColor._b = moudle*_b;
	fColor._a = moudle*_a;

	return fColor;
}

CFColor::CFColor():
_r(0.0f), _g(0.0f), _b(0.0f), _a(0.0f)
{
	
}

CFColor::CFColor(float r, float g, float b, float a/* =1.0f */)
{
	setRed(r); setGreen(g); setBlue(b); setAlpha(a);
}

CFColor::~CFColor(void)
{

}

CColor CFColor::toColor()
{
	CColor color;
	float moudle = 255;

	color._r = static_cast<m_byte>(moudle*_r);
	color._g = static_cast<m_byte>(moudle*_g);
	color._b = static_cast<m_byte>(moudle*_b);
	color._a = static_cast<m_byte>(moudle*_a);

	return color;
}

}
