#pragma once

#include "IEventArgs.h"
#include "EventTypes.h"

class IObserver
{
public:
	IObserver( );
	virtual ~IObserver( );

	virtual void OnNotified( uint32 eventType, IEventArgs* eventArgs ) = 0;
};
