#pragma once

#include "tat.h"

#include "types.h"
#include <memory>

namespace uti
{
	namespace Input
	{
		class TAT_DEF IDeviceFrame;

		class TAT_DEF IDevice
		{
		public:
			IDevice( ) {}
			~IDevice( ) {}

			virtual void Update( ) = 0;

			virtual void GetFrame( std::shared_ptr<IDeviceFrame>& frame ) = 0;
		};
	}
}
