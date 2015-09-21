#pragma once
#include "MathEngine.h"

namespace DreamEngine
{

#define MAX_VERTICES					65534
#define MAX_TRIANGLES					65534
#define MAX_GROUPS						255
#define MAX_MATERIALS					128
#define MAX_JOINTS						128
#define MAX_TEXTURE_FILENAME_SIZE		128

#define SELECTED						1
#define HIDDEN							2
#define SELECTED2						4
#define DIRTY							8
#define ISKEY							16
#define NEWLYCREATED					32
#define MARKED							64

#define SPHEREMAP						0x80
#define HASALPHA						0x40
#define COMBINEALPHA					0x20

#define TRANSPARENCY_MODE_SIMPLE					0
#define TRANSPARENCY_MODE_DEPTHSORTEDTRIANGLES		1
#define TRANSPARENCY_MODE_ALPHAREF					2

#include <vector>

#pragma pack(1)

struct MS3DHeader
{
	char			signature[10];		// must be 'MS3D000000'
	int				version;			// file format version (3 or 4)
};

struct MS3DVertex
{
	char			flags;				// editor flags  SELECTED | SELECTED2 | HIDDEN
	float			pos[3];				// world coordinates
	signed char		boneID;				// -1 = no bone
	unsigned char	referenceCount;     // bone reference count
};

struct MS3DFace
{
	unsigned short	flags;               // editor flags SELECTED | SELECTED2 | HIDDEN
	unsigned short	vertexIndices[3];    // three vertex indices
	float			vertexNormals[3][3]; // three vertex normals
	float			u[3];                // three texture u coordinates
	float			v[3];                // three texture v coordinates
	unsigned char	smoothingGroup;      // smoothing group,1 - 32
	unsigned char	groupIndex;          // group index
};

struct MS3DGroup
{
	struct 
	{
		char					flags;				// editor flags SELECTED | SELECTED2 | HIDDEN
		char					name[32];			// name of group
		unsigned short			numFaces;			// # faces in group
	} Header;
	unsigned short				*pIndices;			// face indices
	char						material;			// -1 = no material

	MS3DGroup()  {pIndices = MATH_NULL;   }
	~MS3DGroup() {delete [] pIndices;}
};

struct MS3DMaterial
{
	char  name[32];									// Material name
	float ambient[4];								// Ambient colors
	float diffuse[4];								// Diffuse colors
	float specular[4];								// Specular colors
	float emissive[4];								// Emissive colors
	float shininess;								// Shininess strength
	float transparency;								// Transparency amount
	char  mode;										// Mode 0-3
	char  texture[128];								// Texture map .bmp filename
	char  alphamap[128];							// Alpha map .bmp filename
} ;

struct MS3DKeyFrame
{
	float time;										// Time of key frame
	float value[3];									// key frame values (position, rotation)
};

struct MS3DBone 
{
	struct 
	{
		char			flags;						// Editor flags
		char			name[32];					// Bone name
		char			parent[32];					// Parent bone name
		float			rotation[3];				// Rotation of bone
		float			position[3];				// Position of bone
		m_uint16		numRotFrames;				// # of rotation key frames
		m_uint16		numPosFrames;				// # of position key frames
	} Header;
	MS3DKeyFrame		*pRotKeyFrames;				// Rotation key frames
	MS3DKeyFrame		*pPosKeyFrames;				// Position key frames

	MS3DBone()  { pRotKeyFrames=MATH_NULL; pPosKeyFrames=MATH_NULL;}
	~MS3DBone() { delete []pRotKeyFrames; delete []pPosKeyFrames;}
};

//struct MS3DMeshVertex
//{
//	float		x,  y,  z;								// Coordinates of vertex
//	float		nx, ny, nz;								// Vertex normals
//	float		u,  v;									// Texture coordinates
//	m_uint32	boneNum;								// Bone connected to
//};
//
//struct MS3DBoneContainer
//{
//	char				name[32];
//	CMatrix16			matRotation;
//	CMatrix16			matTranslation;
//
//	CMatrix16			matTransformation;
//	CMatrix16			matCombined;
//	CMatrix16			matInvCombined;
//
//	MS3DBoneContainer	*pSibling;
//	MS3DBoneContainer	*pChild;
//
//	MS3DBoneContainer() { pSibling = MATH_NULL; pChild = MATH_NULL; }
//};

 
#pragma pack()
}
