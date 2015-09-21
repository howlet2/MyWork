#pragma once
#include <string>

namespace DreamEngine
{
enum RESULT
{
	RESULT_FAIL = 0,
	RESULT_OK	= 1,
};

enum VectorDirect
{
	UNIT_X	= 1,
	UNIT_Y	= 2,
	UNIT_Z	= 3,
};

enum RSPOOL
{
	RSP_UNKOWN	=	0,
	RSP_MANAGER =	1,
	RSP_DEFAULT	=	2,
};

enum IndexBufferType
{
	IBT_0		=  0,
	IBT_8		=  1,
	IBT_16		=  2,
	IBT_32		=  3,
};

enum ShaderType
{
	ST_UNKOWN	= 0,
	ST_FRAGMENT = 1,
	ST_VERTEX	= 2,
};

}