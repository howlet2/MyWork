#pragma once
#include "Engineobject.h"
#include "Vector2.h"
#include "Singleton.h"
using namespace Math;
using namespace DreamEngine;

class _EngineExport CTouchSystem : public CSingleton<CTouchSystem>
{
public:

enum State
{
	STATE_UP,
	STATE_DOWN,
};

struct TouchState
{
	int			x;
	int			y;
	State		state;
};

public:

	CTouchSystem(HWINDOW m_hWnd);
	~CTouchSystem(void);

	static CTouchSystem&	instance(void);
	static CTouchSystem*	instancePtr(void);

	int			getPositionX()const		{return m_touchState.x;}
	int			getPositionY()const		{return m_touchState.y;}
	CVector2	getPosition()const		{return CVector2(m_touchState.x,m_touchState.y);}

	State		getState()const			{return m_touchState.state;}

	void		update();

private:

	TouchState		m_touchState;
	HWINDOW			m_hWnd;

};
template<> CTouchSystem* CSingleton<CTouchSystem>::m_singleton = 0;
