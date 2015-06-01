#pragma once

#include "types.h"

#include <istream>

namespace uti
{
	namespace Input
	{
		class IDeviceFrame
		{
		public:
			IDeviceFrame( ) {}
			~IDeviceFrame( ) {}

			virtual bool GetButtonState(rhandle button) = 0;
			virtual bool GetButtonState(const char* button) = 0;
			 
			virtual float GetAxisValue(rhandle axis) = 0;
			virtual float GetAxisValue(const char* button) = 0;

			//virtual std::istream GetDataStream(rhandle stream) = 0;
			//virtual std::istream GetDataStream(const char* stream) = 0;
		};
	}
}
