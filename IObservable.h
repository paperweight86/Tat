#pragma once

#include "IObserver.h"

#include <vector>
#include <map>
#include <memory>

class IObservable
{
public:
	IObservable( );
	virtual ~IObservable( );

	virtual bool AddObserver( const std::weak_ptr<IObserver>& observer, uint32 type ) = 0;
protected:
	virtual void Notify( uint32 eventType, IEventArgs* eventArgs ) = 0;
};

