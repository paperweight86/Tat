#pragma once

#include <climits>
#include <cfloat>

#ifndef UTI_NO_STL
#include <string>
#include <tchar.h>
#endif

#include <mmintrin.h>

namespace uti
{
	// Instruction Set
#if defined(_M_AMD64)
#define __ARCX64
#elif defined(_M_IX86)
#define __ARCX86
#endif

	// Platform & Config
#ifdef _MSC_VER
	#if defined(_WIN32) || defined(_WIN64)
		#define TAT_WINDOWS
	#endif
#endif
#ifdef _DEBUG
	#define TAT_DEBUG
#else
	#define TAT_RELEASE
#endif

#if defined(__ARCX64) || defined(__ARCX86)
#define __SSE
#endif

	// POD types
	typedef char int8;
	typedef unsigned char uint8;
	typedef short int16;
	typedef unsigned short uint16;
	typedef __int32 int32;
	typedef unsigned __int32 uint32;
	typedef __int64 int64;
	typedef unsigned __int64 uint64;
	typedef float real32;
	typedef float real64;
#ifdef TAT_REAL64
	typedef real64 real;
#else
	typedef real32 real;
#endif
	typedef void* voidptr;
	typedef void* evilptr;

	// concise POD types
	typedef char i8;
	typedef unsigned char u8;
	typedef short i16;
	typedef unsigned short u16;
	typedef __int32 i32;
	typedef unsigned __int32 u32;
	typedef __int64 i64;
	typedef unsigned __int64 u64;
	typedef real32 r32;
	typedef real32 r64;

	// Compound PODs
	struct float2
	{
		float x, y;
		float2() :x(0.0f), y(0.0f){};
		float2(float _x, float _y) :x(_x), y(_y){};
	};

	struct float3
	{
		float x, y, z;
		float3() : x(0.0f), y(0.0f), z(0.0f) {}
		float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		float3(float2 xy) : x(xy.x), y(xy.y), z(0.0f) {}
#ifndef TAT_FLOAT3_NO_PAD
	private:
		float pad;
#endif
	};

#ifdef __SSE
	typedef __m128 vector4;
	struct matrix44 { float m[16]; };
#else
	typedef struct vector4
	{
		float x,y,z,h;
	} vector4;
#endif

	//!< Vector 4
	typedef vector4 float4;
	typedef matrix44 float44;
//	struct float4
//	{
//	private:
//		float4() { _mm_set1_ps(0.0f); }
//		float4(__m128 _v) { v = _v; }
//		float4(float _x, float _y, float _z) { v = _mm_set_ps(_z, _y, _x, 1.0f); }
//		float4(float _x, float _y, float _z, float _h) { v = _mm_set_ps(_z, _y, _x, _h); }
//	public:
//		static float4 create(float _x, float _y, float _z) {   }
//		r32 get_x() const { return (*this)[1]; }
//		r32 get_y() const { return (*this)[2]; }
//		r32 get_z() const { return (*this)[3]; }
//		r32 get_h() const { return (*this)[0]; }
//		float operator[](u32 i) const
//		{
////#ifdef __SSE4_1__
//#if 0
//			float h = 0.0f;
//			switch (i)
//			{
//			case 0:
//				h = (float)_mm_extract_ps(v, 0);
//				return h;
//			case 1:
//				return (float)_mm_extract_ps(v, 1);
//			case 2:
//				return (float)_mm_extract_ps(v, 2);
//			case 3:
//				return (float)_mm_extract_ps(v, 3);
//			default:
//				return 0.0f;
//			}
//#else
//			switch (i)
//			{
//				case 0:
//					return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((0) << 6) | ((0) << 4) | ((0) << 2) | ((0)))));
//				case 1:
//					return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((1) << 6) | ((1) << 4) | ((1) << 2) | ((1)))));
//				case 2:
//					return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((2) << 6) | ((2) << 4) | ((2) << 2) | ((2)))));
//				case 3:
//					return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((3) << 6) | ((3) << 4) | ((3) << 2) | ((3)))));
//				default:
//					return 0.0f;
//			}
//#endif
//		}
//		union
//		{
//			__m128 v;
////			r32     a[4];
////#ifdef __SSE
//			struct
//			{
//				r32 h, x, y, z;
//			};
////#endif
//		};
//	};

	//!< Matrix 4x4
	//struct float44
	//{
	//	float4 m[4];
	//};

	// Super compact real vector types
	typedef float2 rv2;
	typedef float3 rv3;
	typedef float4 rv4;

	struct size
	{
		r32 w, h;
	};

	// Basic shapes
	struct rect
	{
		r32 x, y, w, h;
	};

	struct circle
	{
		r32 x, y, r;
	};

	struct triangle
	{
		r32 p0x, p0y,
			p1x, p1y,
			p2x, p2y;
	};

	struct margin
	{
		r32 l, t, r, b;
	};

	// Colour
	struct color
	{
		float r, g, b, a;

		bool const operator==(const color &other) const
		{
			return r == other.r
				&& g == other.g
				&& b == other.b
				&& a == other.a;
		}
	};

	inline void CreateColourFromRGB(color& col, u32 rgba)
	{
		col.r = ((float)(u8)(rgba >> 24)) / 255.0f;
		col.g = ((float)(u8)(rgba >> 16)) / 255.0f;
		col.b = ((float)(u8)(rgba >> 8)) / 255.0f;
		col.a = ((float)(u8)(rgba)) / 255.0f;
	}
	
	// Integer Ranges
	#define uint64_max  _UI64_MAX
	#define u64_max  _UI64_MAX
	#define int64_max    _I64_MAX
	#define i64_max    _I64_MAX
	#define uint32_max  _UI32_MAX
	#define u32_max  _UI32_MAX
	#define int32_max    _I32_MAX
	#define i32_max    _I32_MAX
	#define uint16_max  _UI16_MAX
	#define u16_max  _UI16_MAX
	#define int16_max    _I16_MAX
	#define i16_max    _I16_MAX
	#define uint8_max    _UI8_MAX
	#define u8_max    _UI8_MAX
	#define int8_max      _I8_MAX
	#define i8_max      _I8_MAX
	#define int64_min    _I64_MIN
	#define i64_min    _I64_MIN
	#define int32_min    _I32_MIN
	#define i32_min    _I32_MIN
	#define int16_min    _I16_MIN
	#define i16_min    _I16_MIN
	#define int8_min      _I8_MIN
	#define i8_min      _I8_MIN

	// Float Ranges
	#define float_max      FLT_MAX
	#define float_min      FLT_MIN
	#define float_epsilon  FLT_EPSILON
	#define double_max     DBL_MAX
	#define double_min     DBL_MIN
	#define double_epsilon DBL_EPSILON
	#define real32_max float_max
	#define real32_min float_min
	#define real64_max double_max
	#define real64_min double_min

#ifdef UTI_REAL64
	#define real_max real64_max
	#define real_min real64_min
#else
	#define real_max real32_max
	#define real_min real32_min
#endif

	template<typename T>
	inline T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	inline T max(T a, T b)
	{
		return a > b ? a : b;
	}

	//!< Pointer Sized Type
#if   defined(__ARCX64)
	typedef u64 ptr;
#else
	typedef u32 ptr;
#endif

	// resource handle, split into 32bits for unique ID, 32bits for type
	typedef u64 rhandle;
	const rhandle nullrhandle = (u64)uint32_max | ((u64)uint32_max << 32);
	// proposal:
	// 2b - type	// e.g. mesh, texture, shader etc.
	// 2b - subtype // e.g. terrain, skinned, 2D, RenderTarget, Pixel, Vertex, Compute
	// 4b - UID     // 1,2,3,4,5...etc
	#define MAKE_RHANDLE( id, type ) (u64)id | ((u64)type << 32)
	#define GET_RHANDLE_ID( handle ) (u32)handle
	#define GET_RHANDLE_TYPE( handle ) (u32)(handle >> 32)

	// strings
	typedef const wchar_t* wstr;
	typedef const char*    cstr;
#ifdef UNICODE
	typedef wchar_t* mstr;
	typedef const wchar_t* tstr;
	typedef wchar_t tchar;
	#ifndef UTI_NO_STL
	typedef std::wstring tstring;
	#endif
	#define TSTR_TO_FLOAT(str) _wtof(str)
#else
	typedef char* mstr;
	typedef const char* tstr;
	typedef char tchar;
	#ifndef UTI_NO_STL
	typedef std::string tstring;
	#endif
	#define TSTR_TO_FLOAT(str) atof(str)
#endif

	// reflection
	union UValue
	{
		uti::r32 real32;
		uti::r64 real64;
		
		uti::i32 int32;
		uti::i64 int64;

		uti::u32 uint32;
		uti::u64 uint64;
	};

	enum UValueType
	{
		eReal32,
		eReal64,
		eInt32,
		eInt64,
		eUInt32,
		eUInt64
	};

	// debugging macros
#define UTI_STRINGIZE(x) UTI_STRINGIZE2(x)
#define UTI_STRINGIZE2(x) #x
#ifdef UNICODE
	#define __FUNCTIONT__ __FUNCTIONW__
	#define __FILET__ _STR2WSTR(__FILE__)
	#define __LINET__ _STR2WSTR(UTI_STRINGIZE(__LINE__))
#else
	#define __FUNCTIONT__ __FUNCTION__
	#define __FILET__ __FILE__
	#define __LINET__ UTI_STRINGIZE(__LINE__)
#endif
	
	// compile-time warnings/errors
	//#ifdef _CPPRTTI // Run-time type information is being generated
	//#pragma message( "warning: RTTI is enabled which can be slow, if unused disable it." )
	//#endif
	#if !defined(__ARCX64) && !defined(__ARCX86)
	#pragma error( "Unknown architecture" )
	#endif
}
