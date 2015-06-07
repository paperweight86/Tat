#pragma once

// for __comerror
#include "comdef.h"

#define CHECK_HR_ONFAIL_LOG_RETURN(hr,estr)	if( FAILED(hr) )\
											{\
												_com_error err(hr);\
												LPCTSTR errMsg = err.ErrorMessage();\
												if(errMsg) {\
													Logger.Error(_T("%s (\"%s\")"), estr, errMsg);\
												} else {\
													Logger.Error(_T("%s (%08x)"), estr, hr);\
												}\
												return false;\
											} static_cast<void>(0)

#define CHECK_HR_ONFAIL_LOG_RETURN_VAL(hr,estr,ret)	if( FAILED(hr) )\
											{\
												_com_error err(hr);\
												LPCTSTR errMsg = err.ErrorMessage();\
												if(errMsg) {\
													Logger.Error(_T("%s (\"%s\")"), estr, errMsg);\
												} else {\
													Logger.Error(_T("%s (%08x)"), estr, hr);\
												}\
												return ret;\
											} static_cast<void>(0)

#define CHECK_HR_ONFAIL_LOG(hr,estr)	if( FAILED(hr) )\
										{\
											_com_error err(hr);\
											LPCTSTR errMsg = err.ErrorMessage();\
											if(errMsg) {\
												Logger.Error(_T("%s (\"%s\")"), estr, errMsg);\
											} else {\
												Logger.Error(_T("%s (%08x)"), estr, hr);\
											}\
										} static_cast<void>(0)

#define D2D_RELEASE(pD2DResource)		if(pD2DResource)\
										{\
											pD2DResource->Release();\
											pD2DResource=nullptr;\
										} static_cast<void>(0)

