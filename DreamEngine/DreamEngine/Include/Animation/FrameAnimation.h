#pragma once
#include "EngineObject.h"
#include "Texture.h"

namespace DreamEngine
{
class _EngineExport CFrameAnimation : public CEngineObject
{
	enum FileType
	{
		TP_UNKOWN,
		TP_TEXTURE_FILES,
		TP_ANIMATION_FILE,
	};
public:
	CFrameAnimation(const CString& name);
	~CFrameAnimation(void);

	virtual bool		initWithFiles(const char* pFileName, ...);
	virtual bool		initWithFilesByVaLst(const char* pFileName, va_list fileNames);
	virtual bool		initWithAnimationFile(const CString& fileName);
	CTexture*			addFrame(const char* pTextureFile);

	virtual void		update(float delay);
	void				destory(void);

	CTexture*			getCurrentTexture(void)const;
	int					getFrameIndex(void)const;
	int					getFrameNum(void)const;

protected:

	virtual void		onFrameChange(int curFrameIdx);

protected:

	CString			m_name;
	
	typedef std::vector<CTexture*> TextureLst;
	TextureLst		m_textures;
	
	int				m_frameIdx;
	int				m_frameNum;

	float			m_intervalSec;
	float			m_accumulateTime;
	FileType		m_fileType;
};
}
