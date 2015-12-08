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

enum TEX_FORMAT
{
	TF_UNKOWN	   = 0,
	TF_R8G8B8      = 1,
	TF_A8R8G8B8    = 2,
	TF_R8G8B8A8	   = 3,
	TF_X8R8G8B8    = 4,
	TF_L8          = 5,
	TF_X8L8V8U8    = 6,
};

}