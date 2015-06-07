#pragma once

#include "tat.h"

#include <vector>
#include <memory>

#include "Callback.h"
#include "types.h"

namespace uti
{
	namespace Input
	{
		enum TAT_DEF EDevice
		{
			eInputDevice_Keyboard,
			eInputDevice_Mouse,
			eInputDevice_Pen,
			eInputDevice_Controller
		};

		class TAT_DEF IDeviceFrame;

		typedef std::vector<EDevice>						    TDeviceTypes;
		typedef std::vector<std::shared_ptr<IDeviceFrame>>	    TFrame;
		typedef CCallback<void, EDevice, const rhandle&>        TConnectCB;
		typedef CCallback<void, std::shared_ptr<IDeviceFrame>&> TInputCB;
	}

	class TAT_DEF IInput
	{
	public:
		IInput() {}
		virtual ~IInput() {}

		virtual void Initialise(ptr hwnd) = 0;

		virtual void Update( ) = 0;

		virtual void GetDevices( Input::TDeviceTypes& devices ) = 0;
		virtual void GetFrame( Input::TFrame& frame ) = 0;

		virtual void RegisterOnConnect( Input::TConnectCB& callback ) = 0;
		virtual void RegisterOnInput( Input::TInputCB& callback ) = 0;
		virtual void RegisterOnInputFilter( Input::TInputCB& callback, 
											Input::TDeviceTypes& filter ) = 0;
	};
}
