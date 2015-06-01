#pragma once

#include "IInput.h"

namespace uti
{
	class CWinInput : public IInput
	{
	public:
		CWinInput( );
		virtual ~CWinInput( );

		virtual void Update( ) override;

		virtual void GetDevices(Input::TDeviceTypes& devices) override;
		virtual void GetFrame(Input::TFrame& frame) override;

		virtual void RegisterOnConnect(Input::TConnectCB& callback) override;
		virtual void RegisterOnInput(Input::TInputCB& callback) override;
		virtual void RegisterOnInputFilter( Input::TInputCB& callback, Input::TDeviceTypes& filter) override;
	};
}
