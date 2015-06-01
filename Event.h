#pragma once

#include "Callback.h"

#include <list>

namespace uti
{
	// TODO: How do we account for arguments being used by each handler?
	// Can they be forced to be managed or POD types?
	// and the fact the each handler is executed in sequence on the same thread?
	// Can it be setup to allow them to run on microthreads simultaneously?
	// This would certainly require all types to be thread safe...
	template<typename ...Arguments>
	class Event
	{
	private:
		std::list<CCallback<void, Arguments>::ptr> m_handlers;
	public:
		Event( ) {}
		~Event( ) {}

		void Add( CCallback<void, Arguments>::ptr eventHandler )
		{
			m_handlers.push_back( eventHandler );
		}
		
		void Remove(CCallback<void, Arguments>::ptr eventHandler)
		{
			m_handlers.remove( eventHandler );
		}

		void Invoke( Arguments... args )
		{
			for (auto iterHandler = m_handlers.begin(); iterHandler != m_handlers.end(); ++iterHandler)
			{
				(*iterHandler).Invoke( args );
			}
		}
	};
}
