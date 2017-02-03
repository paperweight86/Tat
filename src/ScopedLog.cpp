#include "stdafx.h"

#include "ScopedLog.h"

#include <stdarg.h>

using namespace uti;

CScopedLog::CScopedLog( tstr component )
{
	(void)component;
//	Logger.PushComponent( component );
}

CScopedLog::~CScopedLog( )
{
//	Logger.PopComponent( );
}
