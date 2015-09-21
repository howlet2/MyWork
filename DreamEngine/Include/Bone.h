#pragma once
#include "Node.h"
 
namespace DreamEngine
{

class _EngineExport CBone : public CNode
{
public:
	CBone(void);
	CBone(const CString& name,
		  CNode* pParent=MATH_NULL,
		  CNode* pSibling=MATH_NULL,
		  CNode* pChild=MATH_NULL);

	~CBone(void);

	void			setSilbling(CNode* pSibling)			{m_pSibling = pSibling;}
	CNode*			getSibling(void)const					{return m_pSibling;}

	virtual void	addChild(CNode* pChild, bool isFlashMat=true);	

	void		    updateTransformation(void);


protected:

	void			_updateTransformation(CNode* pParent, const CMatrix16& matParent);

protected:

	CMatrix16		m_matInverse;
	CNode*			m_pSibling;


};

}


