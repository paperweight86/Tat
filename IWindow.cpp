#include "stdafx.h"
#include "IWindow.h"

using namespace uti;

IWindow::IWindow( )
{
	++m_numInstances;
}


IWindow::~IWindow( )
{
}


int32 IWindow::m_numInstances = 0;