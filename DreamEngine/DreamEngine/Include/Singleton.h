
#pragma once
namespace DreamEngine
{
	template <class T> class CSingleton
	{
	public:

		CSingleton()
		{
			m_singleton = static_cast< T* >( this );
		}

		~CSingleton(void)
		{  
			m_singleton = 0;  
		}

		static T& instance(void)
		{	
			return *instancePtr(); 
		}

		static T* instancePtr(void)
		{ 
// 			if (m_singleton==MATH_NULL)
// 				m_singleton=new T;
			return m_singleton; 
		}

	protected:

		static T* m_singleton;

	private:
		CSingleton& operator=(const CSingleton&) {return *this;}
		CSingleton(const CSingleton&) {}
	};
	//template <class T> T* CSingleton<T>::m_singleton = 0;
}


