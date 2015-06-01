#pragma once

#include <climits>
#include <cfloat>

#ifndef UTI_NO_STL
#include <string>
#endif

namespace uti
{
	// Instruction Set
	#if defined(_M_AMD64)
	#define __ARCX64
	#elif defined(_M_IX86)
	#define __ARCX86
	#endif

	#if defined(__ARCX64) || defined(__ARCX86)
		#define __SSE
	#endif
	
	// The usual typedefs
	typedef char int8;
	typedef unsigned char uint8;
	typedef short int16;
	typedef unsigned short uint16;
	typedef __int32 int32;
	typedef unsigned __int32 uint32;
	typedef __int64 int64;
	typedef unsigned __int64 uint64;
	typedef float    real;
	typedef void* voidptr;
	typedef void* evilptr;

	struct float2 
	{ 
		float x, y; 
		float2():x(0.0f),y(0.0f){};
		float2(float _x, float _y):x(_x),y(_y){}; 
	};

	struct float3 
	{ 
		float x, y, z; 
		float3() : x(0.0f), y(0.0f), z(0.0f) {}
		float3( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
		float3( float2 xy ) : x(xy.x), y(xy.y), z(0.0f) {}
		private:
			float pad;
	};

	#ifdef __SSE
		typedef __m128 vector4;
	#else
		typedef struct vector4
		{
			float x,y,z,h;
		} vector4;
	#endif

	//!< Vector 4
	struct float4
	{
		union
		{
			vector4 v;
			float   a[4];
#ifdef __SSE
			struct
			{
				float x,y,z,h;
			};
#endif
		};
	};

	//!< Matrix 4x4
	struct float44
	{
		float4 m[4];
	};
	
	// Integer Ranges
	#define uint64_max  _UI64_MAX
	#define int64_max    _I64_MAX
	#define uint32_max  _UI32_MAX
	#define int32_max    _I32_MAX
	#define uint16_max  _UI16_MAX
	#define int16_max    _I16_MAX
	#define uint8_max    _UI8_MAX
	#define int8_max      _I8_MAX
	#define int64_min    _I64_MIN
	#define int32_min    _I32_MIN
	#define int16_min    _I16_MIN
	#define int8_min      _I8_MIN

	// Float Ranges
	#define float_max      FLT_MAX
	#define float_min      FLT_MIN
	#define float_epsilon  FLT_EPSILON
	#define double_max     DBL_MAX
	#define double_min     DBL_MIN
	#define double_epsilon DBL_EPSILON

	//!< Pointer Sized Type
#if   defined(__ARCX64)
	typedef uint64 ptr;
#else
	typedef uint32 ptr;
#endif

	// resource handle, split into 32bits for unique ID, 32bits for type
	typedef uint64 rhandle;
	const rhandle nullrhandle = (uint64)uint32_max | ((uint64)uint32_max << 32);
	// proposal:
	// 2b - type	// e.g. mesh, texture, shader etc.
	// 2b - subtype // e.g. terrain, skinned, 2D, RenderTarget, Pixel, Vertex, Compute
	// 4b - UID     // 1,2,3,4,5...etc
	#define MAKE_RHANDLE( id, type ) (uint64)id | ((uint64)type << 32)
	#define GET_RHANDLE_ID( handle ) (uint32)handle
	#define GET_RHANDLE_TYPE( handle ) (uint32)(handle >> 32)

	// strings
	typedef const wchar_t* wstr;
	typedef const char*    cstr;
#ifdef UNICODE
	typedef const wchar_t* tstr;
	typedef wchar_t tchar;
	#ifndef UTI_NO_STL
	typedef std::wstring tstring;
	#endif
#else
	typedef const char* tstr;
	typedef char tchar;
	#ifndef UTI_NO_STL
	typedef std::string tstring;
	#endif
#endif

	// debugging macros
#ifdef UNICODE
	#define __FUNCTIONT__ __FUNCTIONW__
	#define __FILET__ _STR2WSTR(__FILE__)
#else
	#define __FUNCTIONT__ __FUNCTION__
	#define __FILET__ __FILE__
#endif
	
	// compile-time warnings/errors
	//#ifdef _CPPRTTI // Run-time type information is being generated
	//#pragma message( "warning: RTTI is enabled which can be slow, if unused disable it." )
	//#endif
	#if !defined(__ARCX64) && !defined(__ARCX86)
	#pragma error( "Unknown architecture" )
	#endif
}
