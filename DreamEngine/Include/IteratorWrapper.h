#pragma once

template <class IteratorType, class ValType>
class CIteratorWrapper
{
private:

	CIteratorWrapper(void);

public:

	CIteratorWrapper(IteratorType begin, IteratorType end):
	  m_begin(begin), m_current(begin), m_end(end){}
	~CIteratorWrapper(void){}
	


	bool					hasMore(void)const		{return m_current!=m_end;}
	const IteratorType&		begin(void)const		{return m_begin;}
	const IteratorType&		end(void)const			{return m_end;}
	ValType&				current(void)const		{return *m_current;}
	void					moveToBegin(void)		{m_current = m_begin;}


	
	void Next()
	{
		if (hasMore())++m_current;
	}



	void set(IteratorType begin, IteratorType end)
	{
		m_current = m_begin = begin;
		m_end  = end;
	}

protected:

	IteratorType		m_begin;
	IteratorType		m_end;
	IteratorType		m_current;
};

