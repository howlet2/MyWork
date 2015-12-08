#pragma once
#include "EngineObject.h"

namespace DreamEngine
{

//copy from d3d9
enum DREAMDDECLUSAGE
{
	DREAMDECLUSAGE_POSITION = 0,
	DREAMDECLUSAGE_BLENDWEIGHT,   // 1
	DREAMDECLUSAGE_BLENDINDICES,  // 2
	DREAMDECLUSAGE_NORMAL,        // 3
	DREAMDECLUSAGE_PSIZE,         // 4
	DREAMDECLUSAGE_TEXCOORD,      // 5
	DREAMDECLUSAGE_TANGENT,       // 6
	DREAMDECLUSAGE_BINORMAL,      // 7
	DREAMDECLUSAGE_TESSFACTOR,    // 8
	DREAMDECLUSAGE_POSITIONT,     // 9
	DREAMDECLUSAGE_COLOR,         // 10
	DREAMDECLUSAGE_FOG,           // 11
	DREAMDECLUSAGE_DEPTH,         // 12
	DREAMDECLUSAGE_SAMPLE,        // 13
	DREAMDECLUSAGE_UNSUED = 99,		 //99
};

enum DREAMDDECLMETHOD
{
	DREAMDECLMETHOD_DEFAULT = 0,
	DREAMDECLMETHOD_PARTIALU,
	DREAMDECLMETHOD_PARTIALV,
	DREAMDECLMETHOD_CROSSUV,				
	DREAMDECLMETHOD_UV,
	DREAMDECLMETHOD_LOOKUP,             
	DREAMDECLMETHOD_LOOKUPPRESAMPLED,     
};

enum DREAMDECLTYPE
{
	DREAMDECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
	DREAMDECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
	DREAMDECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
	DREAMDECLTYPE_FLOAT4    =  3,  // 4D float
	DREAMDECLTYPE_COLOR		=  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
	// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
	DREAMDECLTYPE_UBYTE4    =  5,  // 4D unsigned byte
	DREAMDECLTYPE_SHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
	DREAMDECLTYPE_SHORT4    =  7,  // 4D signed short

	// The following types are valid only with vertex shaders >= 2.0


	DREAMDECLTYPE_UBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
	DREAMDECLTYPE_SHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
	DREAMDECLTYPE_SHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
	DREAMDECLTYPE_USHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
	DREAMDECLTYPE_USHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
	DREAMDECLTYPE_UDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
	DREAMDECLTYPE_DEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
	DREAMDECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
	DREAMDECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values
	DREAMDECLTYPE_UNUSED    = 17,  // When the type field in a decl is unused.
};


class _EngineExport CVertexElement : public CEngineObject
{
public:

	CVertexElement(	m_uint16 stream, 
					m_uint16 offset, 
					m_byte type, 
					m_byte method,
					m_byte usage, 
					m_byte usageIndex);
	CVertexElement(void);
	~CVertexElement(void);

	void		toEndDeclElement(void);

	m_uint16    m_stream;     // Stream index
	m_uint16    m_offset;     // Offset in the stream in bytes
	m_byte		m_type;       // Data type
	m_byte		m_method;     // Processing method
	m_byte		m_usage;      // Semantics
	m_byte		m_usageIndex; // Semantic index, like POSITION1 is 1, POSITION0 is 0

};


}


