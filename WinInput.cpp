#include "stdafx.h"
#include "WinInput.h"

#include "ScopedLog.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <tchar.h>

using namespace uti;

CWinInput::CWinInput()
{

}

CWinInput::~CWinInput()
{

}

void CWinInput::Update()
{
	ComponentLogFunc();
}

void CWinInput::GetDevices(Input::TDeviceTypes& devices)
{

}

void CWinInput::GetFrame(Input::TFrame& frame)
{

}

void CWinInput::RegisterOnConnect(Input::TConnectCB& callback)
{

}

void CWinInput::RegisterOnInput(Input::TInputCB& callback)
{

}

void CWinInput::RegisterOnInputFilter(Input::TInputCB& callback, Input::TDeviceTypes& filter)
{

}
