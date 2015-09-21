#include "CommonFunction.h"
#include "StringHelper.h"

namespace DreamEngineGLES2
{

CCommonFunction::CCommonFunction(void)
{
}


CCommonFunction::~CCommonFunction(void)
{
}

int CCommonFunction::HDBufTypeToGLES2PriType(HardwareBufferType type)
{
	switch (type)
	{
	case POINT_LIST:
		return GL_POINTS;

	case LINE_LIST:
		return GL_LINES;

	case LINE_SHRIP:
		return GL_LINE_STRIP;

	case TRIANGLE_LIST:
		return GL_TRIANGLES;

	case TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;

	case TRIANGLE_FAN:
		return GL_TRIANGLE_FAN;

	default: return -1;
	}
}

int CCommonFunction::IdxBufTypeToElemDrawType(DreamEngine::IndexBufferType idxBufType)
{
	DreamEngine::IndexBufferType type = static_cast<DreamEngine::IndexBufferType>(idxBufType);
	switch (type)
	{
	case DreamEngine::IBT_8:
		{
			return GL_UNSIGNED_BYTE;
		}break;

	case DreamEngine::IBT_16:
		{
			return GL_UNSIGNED_SHORT;
		}break;

	case DreamEngine::IBT_32:
		{
			return GL_UNSIGNED_INT;
		}break;

	default:
		return false;
	}
}

CCommonFunction::ParamTypeInfo CCommonFunction::GLES2ParamDataTypeToParamType(GLenum type)
{
	ParamTypeInfo data;
	switch (type)
	{
	case GL_FLOAT:
		{
			data.first	= CShaderParam::SPT_FLOAT;
			data.second = 1;
		}break;

	case GL_FLOAT_VEC2:
		{
			data.first	= CShaderParam::SPT_FLOAT_ARRAY;
			data.second = 2;
		}break;

	case GL_FLOAT_VEC3:
		{
			data.first	= CShaderParam::SPT_FLOAT_ARRAY;
			data.second = 3;
		}break;

	case GL_FLOAT_VEC4:
		{
			data.first	= CShaderParam::SPT_FLOAT_ARRAY;
			data.second = 4;
		}break;

	case GL_INT:
		{
			data.first	= CShaderParam::SPT_INT;
			data.second = 1;
		}break;

	case GL_INT_VEC2:
		{
			data.first	= CShaderParam::SPT_INT_ARRAY;
			data.second = 2;
		}break;
	case GL_INT_VEC3: 
		{
			data.first	= CShaderParam::SPT_INT_ARRAY;
			data.second = 3;
		}break;

	case GL_INT_VEC4:
		{
			data.first	= CShaderParam::SPT_INT_ARRAY;
			data.second = 4;
		}break;

	case GL_BOOL:
		{
			data.first	= CShaderParam::SPT_BOOL;
			data.second = 1;
		}break;

	case GL_BOOL_VEC2:
		{
			data.first	= CShaderParam::SPT_BOOL_ARRAY;
			data.second = 2;
		}break;
	case GL_BOOL_VEC3:
		{
			data.first	= CShaderParam::SPT_BOOL_ARRAY;
			data.second = 3;
		}break;
	case GL_BOOL_VEC4:
		{
			data.first	= CShaderParam::SPT_BOOL_ARRAY;
			data.second = 4;
		}break;

	case GL_FLOAT_MAT4:
		{
			data.first	= CShaderParam::SPT_MATRIX16;
			data.second = 1;
		}break;

	case GL_SAMPLER_2D:
		{
			data.first	= CShaderParam::SPT_TEXTURE;
			data.second = 1;
		}break;

	case GL_FLOAT_MAT2:
	case GL_FLOAT_MAT3:
	case GL_SAMPLER_CUBE:
		{
			data.first	= CShaderParam::SPT_UNKNOW;
			data.second = 1;
		}break;

	default:
		{
			data.first	= CShaderParam::SPT_UNKNOW;
			data.second = 1;
		}break;
	}

	return data;
} 

GLenum CCommonFunction::ParamTypeToGLES2DataType(CShaderParam::ParamType type)
{
	switch (type)
	{
	case CShaderParam::SPT_FLOAT_ARRAY:
	case CShaderParam::SPT_FLOAT :
	//case CShaderParam::SPT_VECTOR3:
		{
			return GL_FLOAT;
		}break;

	case  CShaderParam::SPT_INT:
	case  CShaderParam::SPT_INT_ARRAY:
		{
			return GL_INT;
		}break;

	case CShaderParam::SPT_BOOL :
	case CShaderParam::SPT_BOOL_ARRAY:
		{
			return GL_BOOL;
		}break;

	case CShaderParam::SPT_MATRIX16:
	case CShaderParam::SPT_MATRIX16_ARRAY:
		{
			return GL_FLOAT_MAT4;
		}break;

	case CShaderParam::SPT_TEXTURE:
		{
			return GL_SAMPLER_2D;
		}break;
	
	/*case GL_FLOAT_MAT2:
	case GL_FLOAT_MAT3:
	case GL_SAMPLER_CUBE:
		return CShaderParam::SPT_UNKNOW;*/

	default:
		break;
	}

	return GL_FLOAT;
}

int CCommonFunction::CaculateParamBufferSize(const ParamTypeInfo& paramInfo)
{
	int count = paramInfo.second;
	switch (paramInfo.first)
	{
	case CShaderParam::SPT_FLOAT_ARRAY:
	case CShaderParam::SPT_FLOAT :
	//case CShaderParam::SPT_VECTOR3:
		{
			return sizeof(GLfloat)*count;
		}break;

	case  CShaderParam::SPT_INT:
	case  CShaderParam::SPT_INT_ARRAY:
		{
			return sizeof(GLint)*count;
		}break;

	case CShaderParam::SPT_BOOL :
	case CShaderParam::SPT_BOOL_ARRAY:
		{
			return sizeof(GLboolean)*count;
		}break;
	
	case CShaderParam::SPT_MATRIX16:
	case CShaderParam::SPT_MATRIX16_ARRAY:
		return sizeof(GLfloat)*16*count;

	case CShaderParam::SPT_TEXTURE:
		return sizeof(GL_SAMPLER_2D)*count;

	/*case GL_FLOAT_MAT2:
	case GL_FLOAT_MAT3:
	case GL_SAMPLER_CUBE:
		return CShaderParam::SPT_UNKNOW;*/

	default:
		break;
	}
	return sizeof(GLfloat)*count;
}

CString CCommonFunction::UsageToGLSLAttributeName(DREAMDDECLUSAGE usage, int usageIdx/*=0*/)
{
	CString name;
	switch(usage)
	{
	case DREAMDECLUSAGE_POSITION:
		{
			name.assign("aPosition");
			name.append(CStringHelper::intToString(usageIdx));
		}break;

	case DREAMDECLUSAGE_TEXCOORD:
		{
			name.assign("aTexcoord");
			name.append(CStringHelper::intToString(usageIdx));
		}break;

	case DREAMDECLUSAGE_COLOR:
		{
			name.assign("aColor");
			name.append(CStringHelper::intToString(usageIdx));
		}break;

	case DREAMDECLUSAGE_NORMAL:
		{
			name.assign("aNormal");
			name.append(CStringHelper::intToString(usageIdx));
		}break;

	default: return "";
	};

	return name;
}

GLint CCommonFunction::TexFormatToGLES2Format(TEX_FORMAT texFormat)
{
	switch (texFormat)
	{
	case TF_R8G8B8 :   
		return GL_RGB;
	case TF_R8G8B8A8:
		return GL_RGBA;
 
	case TF_L8:       
		return GL_ALPHA;

	default:
		return GL_DEPTH_COMPONENT;
		 
	}
}

}