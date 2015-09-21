#pragma once

namespace DreamEngine
{
#define MAX_TOKEN_LENGTH 1024

enum DreamMeshToken
{
	DMT_NONE		=	0,
	DMT_MESH		=	1,
	DMT_SUBMESH		=	2,
	DMT_VECTEX		=	3,
	DMT_TEXTURECOORD=   4,
	DMT_INDEX		=	5,

	DMT_NUM,
};

}


