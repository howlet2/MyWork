#pragma once

namespace Math
{
#define MATH_BIT_OFFSET(x) ((unsigned long long)(1)<<(x))

//bit index begin at 1
template <class T>
class CBitFlag
{
public:

	CBitFlag();
	CBitFlag(T data);
	CBitFlag(const CBitFlag& src);
	~CBitFlag();

public:

	inline CBitFlag& operator=(const CBitFlag& src);
	inline CBitFlag& operator=(T src);
	inline bool operator==(const CBitFlag& src)const;
	inline bool operator!=(const CBitFlag& src)const;

	inline T getVaule(void)const	{return m_data;}

	
	inline void set(T settings);
	inline void clear();
	inline void setFlags(T settings);
	inline void clearFlags(T settings);
	inline void setBit(int bit);
	inline void cearBit(int bit);
	inline void setBit(int bit, bool setting);

	inline bool isEmpty()const;
	inline bool testBit(int bit)const;
	inline bool testFlags(T test)const;
	inline bool testAny(T test)const;

	inline int	totalBits()const;
	inline int	totalSet()const;

protected:

	T m_data;
};

template <class T>
CBitFlag<T>::CBitFlag(void)
{
	m_data = 0;
}

template <class T>
CBitFlag<T>::CBitFlag(T data):
m_data(data)
{

}

template <class T>
CBitFlag<T>::CBitFlag(const CBitFlag& src)
{
	*this = src;
}

template <class T>
CBitFlag<T>::~CBitFlag(void)
{
}

template <class T>
CBitFlag<T>& CBitFlag<T>::operator=(const CBitFlag& src)
{
	if (this != &src)
	{
		m_data = src.m_data;
	}
	return *this;
}

template <class T>
CBitFlag<T>& CBitFlag<T>::operator=(T src)
{
	m_data = src;

	return *this;
}

template <class T>
bool CBitFlag<T>::operator==(const CBitFlag& src)const
{
	return m_data==src.m_data;
}

template <class T>
bool CBitFlag<T>::operator!=(const CBitFlag& src)const
{
	return m_data!=src.m_data;
}

template <class T>
void CBitFlag<T>::set(T settings)
{
	m_data = settings;
}

template <class T>
void CBitFlag<T>::clear()
{
	m_data = 0;
}

template <class T>
void CBitFlag<T>::setFlags(T settings)
{
	m_data &= settings;
}

template <class T>
void CBitFlag<T>::clearFlags(T settings)
{
	m_data &= ~settings;
}

template <class T>
void CBitFlag<T>::setBit(int bit)
{
	m_data != MATH_BIT_OFFSET(bit);
}

template <class T>
void CBitFlag<T>::cearBit(int bit)
{
	m_data &= ~MATH_BIT_OFFSET(bit);
}

template <class T>
void CBitFlag<T>::setBit(int bit, bool setting)
{
	setting?setBit(bit):cearBit(bit);
}

template <class T>
bool CBitFlag<T>::isEmpty()const
{
	return m_data==0;
}

template <class T>
bool CBitFlag<T>::testBit(int bit)const
{
	return ((m_data & (MATH_BIT_OFFSET(bit-1)))==0);
}

template <class T>
bool CBitFlag<T>::testFlags(T test)const
{
	return (m_data&test == test);
}

template <class T>
bool CBitFlag<T>::testAny(T test)const
{
	return m_data&test;
}

template <class T>
int	CBitFlag<T>::totalBits()const
{
	return sizeof(T)<<3;
}

template <class T>
int	CBitFlag<T>::totalSet()const
{
	int count = 0;
	T   testData = m_data;
	T   mask = T(1)<<(totalBits()-1);

	while (testData != 0)
	{
		if (testData&mask) ++count;

		testData <<= 1;
	}
	return count;
}


typedef CBitFlag<unsigned char>		 CBit8Flag;
typedef CBitFlag<unsigned short>	 CBit16Flag;
typedef CBitFlag<unsigned int>		 CBit32Flag;
typedef CBitFlag<unsigned long long> CBit64Flag;

}


