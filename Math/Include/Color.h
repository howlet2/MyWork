#pragma once
#include "MathDefine.h"

namespace Math
{
class CFColor;

class CColor
{
public:
	union
	{
		struct
		{			
			m_byte _r;
			m_byte _g;
			m_byte _b;
			m_byte _a;
		};
		m_dwrd _color;
	};

public:
	CColor(void);
	CColor(m_dwrd color);
	CColor(m_byte r, m_byte g, m_byte b, m_byte a=255);
	~CColor(void);

	m_byte		getAlpha(void)const			{return _a;}
	void		setAlpha(m_byte alpha)		{_a=alpha;}

	m_byte		getRed(void)const			{return _r;}
	void		setRed(m_byte red)			{_r=red;}

	m_byte		getGreen(void)const			{return _g;}
	void		setGreen(m_byte green)		{_g=green;}

	m_byte		getBlue(void)const			{return _b;}
	void		setBlue(m_byte blue)		{_b=blue;}

	m_dwrd		getColor(void)const			{return _color;}
	void		setColor(m_dwrd color)		{this->_color = color;}
	
	CFColor		toFColor(void);
};

class CFColor
{
public:

	float _a, _r, _g, _b;

public:

	CFColor();
	CFColor(float r, float g, float b, float a=1.0f);
	~CFColor(void);

public:

	float		getAlpha(void)const			{return _a;}
	void		setAlpha(float alpha)		{_a=alpha;}

	float		getRed(void)const			{return _r;}
	void		setRed(float red)			{_r=red;}

	float		getGreen(void)const			{return _g;}
	void		setGreen(float green)		{_g=green;}

	float		getBlue(void)const			{return _b;}
	void		setBlue(float blue)			{_b=blue;}


	CColor		toColor(void);
};

}


