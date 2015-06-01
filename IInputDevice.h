#pragma once

#include "types.h"
#include <memory>

namespace uti
{
	namespace Input
	{
		class IDeviceFrame;

		class IDevice
		{
		public:
			IDevice( ) {}
			~IDevice( ) {}

			virtual void Update( ) = 0;

			virtual void GetFrame( std::shared_ptr<IDeviceFrame>& frame ) = 0;
		};
	}
}
