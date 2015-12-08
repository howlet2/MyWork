#include "SpineSkeleton.h"
#include "FileDataStream.h"

#include "libRapidjson/document.h"
#include "libRapidjson/stringbuffer.h"

namespace DreamEngine
{
CSpineSkeleton::CSpineSkeleton(const CString& name):
m_pRootBone(MATH_NULL),
m_name(name)
{
}


CSpineSkeleton::~CSpineSkeleton(void)
{
	if (m_pRootBone != MATH_NULL)
		m_pRootBone->deleteAllNode();
	SAFE_DELETE(m_pRootBone);

	for (SpineSlotLst::iterator iter=m_slots.begin(); iter!=m_slots.end(); ++iter)
		SAFE_DELETE(*iter);
	m_slots.clear();
}

void CSpineSkeleton::setRootBone(CSpineBone* pRootBone)
{
	m_pRootBone = pRootBone;
}

static void	loadBones(const RAPIDJSON_NAMESPACE::Value& boneArray, MATH_OUT CSpineBone*& pRoot)
{
	if (boneArray.IsArray())
	{
		for (RAPIDJSON_NAMESPACE::SizeType i = 0; i<boneArray.Size(); i++)
		{
			const RAPIDJSON_NAMESPACE::Value& object = boneArray[i];

			CString name	= object["name"].GetString();
			if (name!="root" && pRoot!=MATH_NULL)
			{
				CString parent;
				if (object.HasMember("parent"))
					parent	= object["parent"].GetString();

				float length = 0.0f;
				if (object.HasMember("length"))
					length = object["length"].GetDouble();

				float x	= 0.0f;
				if (object.HasMember("x"))
					x = object["x"].GetDouble();

				float y = 0.0f;
				if (object.HasMember("y"))
					y = object["y"].GetDouble();

				float rotation = 0.0f;
				if (object.HasMember("rotation"))
					rotation = object["rotation"].GetDouble();

				float scaleX = 1.0f;
				if (object.HasMember("scaleX"))
				{
					scaleX = object["scaleX"].GetDouble();
				}

				float scaleY = 1.0f;
				if (object.HasMember("scaleY"))
				{
					scaleY = object["scaleY"].GetDouble();
				}

				CSpineBone* pBone	= new CSpineBone(name);

				CNode* pParent		= pRoot->findNode(parent);
				if (pParent != MATH_NULL)
				{
					pBone->setPosition(x, y, 0.0f);

					CQuaternion rotate;
					rotate.pitch(rotation);
					pBone->setQuaternion(rotate);
					pBone->setScale(scaleX, scaleY, 1.0f);
					pBone->setLength(length);

					pParent->addChild(pBone);
				}
			}
			else
			{
				pRoot = new CSpineBone(name);
			}
		}
	}
}
static void	loadSlots(const RAPIDJSON_NAMESPACE::Value& slotArray, MATH_OUT CSpineSkeleton::SpineSlotLst& slots)
{
	if (slotArray.IsArray())
	{
		for (RAPIDJSON_NAMESPACE::SizeType i = 0; i<slotArray.Size(); i++)
		{
			const RAPIDJSON_NAMESPACE::Value& object = slotArray[i];

			CString name		= object["name"].GetString();
			CSpineSlot* pSlot	= new CSpineSlot(name);

			CString attachment	= object["attachment"].GetString(); 
			pSlot->setAttachMent(attachment);
			CString bone		= object["bone"].GetString(); 
			pSlot->setBoneName(bone);

			slots.push_back(pSlot);
		}
	}
}

CSpineBone* CSpineSkeleton::loadFromFile(const CString& fileName)
{
	CFileDataStream fileStream;
	fileStream.open(fileName);

	if (fileStream.isOpen())
	{
		CString info;
		fileStream.readString(info, '\n');

		RAPIDJSON_NAMESPACE::Document doc;
		doc.Parse<0>(info.c_str());

		RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
		if (code==RAPIDJSON_NAMESPACE::kParseErrorNone)
		{
			if (doc.IsObject())
			{
				if (doc.HasMember("bones"))
				{
					RAPIDJSON_NAMESPACE::Value &dataArray = doc["bones"];
					loadBones(dataArray, m_pRootBone);
				}
				
				if (doc.HasMember("slots"))
				{
					RAPIDJSON_NAMESPACE::Value &slotArray = doc["slots"];
					loadSlots(slotArray, m_slots);
				}
				
			}
		}
		fileStream.close();
	}
	
	return m_pRootBone;
}

}
