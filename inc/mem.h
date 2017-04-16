#pragma once

#define UTI_DEL_SET_NULL(x) if(x != nullptr) {delete x; x = nullptr;} do {} while(false)
#define UTI_DEL_ARR_SET_NULL(x) if(x != nullptr) {delete [] x; x = nullptr;} do {} while(false)
