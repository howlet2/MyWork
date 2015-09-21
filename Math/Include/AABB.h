#pragma once
#include "Materix16.h"

//////////////////////////////////////////////////////////////////////////this class not test yet
namespace Math
{

// AABB3::corner
//
// Return one of the 8 corner points.  The points are numbered as follows:
//
//            6                                7
//              ------------------------------
//             /|                           /|
//            / |                          / |
//           /  |                         /  |
//          /   |                        /   |
//         /    |                       /    |
//        /     |                      /     |
//       /      |                     /      |
//      /       |                    /       |
//     /        |                   /        |
//  2 /         |                3 /         |
//   /----------------------------/          |
//   |          |                 |          |
//   |          |                 |          |      +Y
//   |        4 |                 |          | 
//   |          |-----------------|----------|      |
//   |         /                  |         /  5    |
//   |        /                   |        /        |       +Z
//   |       /                    |       /         |
//   |      /                     |      /          |     /
//   |     /                      |     /           |    /
//   |    /                       |    /            |   /
//   |   /                        |   /             |  /
//   |  /                         |  /              | /
//   | /                          | /               |/
//   |/                           |/                ----------------- +X
//   ------------------------------
//  0                              1

class CAABB
{
public:

	CVector3	_min;
	CVector3	_max;

public:
	CAABB(void);
	CAABB(const CVector3& min, const CVector3& max);
	~CAABB(void);

	void			Empty(void);
	bool			IsEmpty(void)const;
	CVector3		Corner(int idx);
	void			AddPoint(const CVector3& point);
	
	static	void	Translation(MATH_OUT CAABB* pRes, const CAABB* pLhs, const CMatrix16* pRhs);
	static  bool	Intersect(MATH_OUT CAABB* pInterscet, const CAABB* pLhs, const CAABB* pRhs);
};

}

