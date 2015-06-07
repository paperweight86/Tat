#pragma once

#include "tat.h"

#include "IEventArgs.h"
//#include "EventTypes.h"

class TAT_DEF IObserver
{
public:
	IObserver( );
	virtual ~IObserver( );

	virtual void OnNotified( uti::uint32 eventType, IEventArgs* eventArgs ) = 0;
};
