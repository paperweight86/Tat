#pragma once

#include "tat.h"

#include "IObserver.h"

#include <vector>
#include <map>
#include <memory>

class TAT_DEF IObservable
{
public:
	IObservable( );
	virtual ~IObservable( );

	virtual bool AddObserver( const std::weak_ptr<IObserver>& observer, uti::uint32 type ) = 0;
protected:
	virtual void Notify( uti::uint32 eventType, IEventArgs* eventArgs ) = 0;
};

