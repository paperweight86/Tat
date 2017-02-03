#pragma once

#include "tat.h"

#include "log.h"

namespace uti
{

	/*
		Simple class which pushes a component name onto the logggers component stack on 
		construction and then pops it on destruction. Simplifies enter/exit components/functions.
	*/
	class TAT_DEF CScopedLog
	{
	public:
		CScopedLog( tstr component );
		~CScopedLog( );
	};

	/*
		This class simplifies use of the singleton by adding a CScopedLogger to your main function
		it will automatically Create and Destroy the singleton.
	*/
	class TAT_DEF CScopedLogger
	{
	public:
		CScopedLogger( ) { /*Logger.PushComponent(_T("main")); Logger.Info(_T("Go..."));*/ }
		~CScopedLogger( ) { /*Logger.Info(_T("fin.")); CLogger::DestroyInstance();*/ }
	};

	#define ComponentLog(component) CScopedLog __ScopedComponent (component)
	#define ComponentLogFunc( ) CScopedLog __ScopedComponent (__FUNCTIONT__)
	#define CreateScopedLogger( ) CScopedLogger __ScopedLogger
}
