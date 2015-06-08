#pragma once

#include "tat.h"

#include <memory>

namespace uti
{
	// TODO: [Paperweight86] Won't work with MVC right now...
	//template<typename TRet, typename... Arguments>
	//class TAT_DEF CCallback
	//{
	//public:
	//	typedef TRet(*TCallbackFunc)(Arguments...);
	//	typedef std::shared_ptr<CCallback<TRet, Arguments...>> ptr;
	//private:
	//	bool m_isInitialised;
	//	TCallbackFunc m_func;
	//public:
	//	CCallback() : m_isInitialised(false)
	//	~CCallback();

	//	void Initialise(TCallbackFunc func);

	//	TRet Invoke(Arguments... args);

	//	bool IsInitialised();
	//};

	//template<typename TRet, typename... Arguments>
	//void CCallback::Initialise(TCallbackFunc func)
	//{
	//	m_func = func;
	//	m_isInitialised = true;
	//}

	//template<typename TRet, typename... Arguments>
	//TRet CCallback::Invoke(Arguments... args)
	//{
	//	return m_func(args);
	//}

	//template<typename TRet, typename... Arguments>
	//bool CCallback::IsInitialised()
	//{
	//	return m_isInitialised;
	//}

	//template < typename TRet, typename ...Arguments >
	//typename CCallback< TRet, Arguments... >::ptr MakeCallback(TRet(*cb)(Arguments...))
	//{
	//	typename CCallback<TRet, Arguments...>::ptr ptr
	//		(
	//			new CCallback<TRet, Arguments...>(m_func)
	//		);
	//	return ptr;
	//}
}
