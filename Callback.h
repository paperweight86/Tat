#pragma once

#include <memory>

namespace uti
{
	template<typename TRet, typename... Arguments>
	class CCallback
	{
	public:
		typedef TRet(*TCallbackFunc)(Arguments...);
		typedef std::shared_ptr<CCallback<TRet, Arguments...>> ptr;
	private:
		TCallbackFunc m_func;
	public:
		CCallback();
		~CCallback();

		void Initialise(TCallbackFunc func)
		{
			m_func = func;
		}

		TRet Invoke( Arguments... args )
		{
			return m_func(args);
		}
	};

	template < typename TRet, typename ...Arguments >
	typename CCallback< TRet, Arguments... >::ptr MakeCallback(TRet(*cb)(Arguments...))
	{
		typename CCallback<TRet, Arguments...>::ptr ptr
			(
				new CCallback<TRet, Arguments...>(m_func)
			);
		return ptr;
	}
}
