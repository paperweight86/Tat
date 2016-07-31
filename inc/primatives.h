#pragma once

#include "types.h"

namespace uti
{

	TAT_DEF struct Ray
	{
		float4 origin;
		float4 dir;
	};

	TAT_DEF struct Sphere
	{
		float4	pos;
		r32		radius;
		float4  color;
	};

	TAT_DEF struct Plane
	{
		float4 pos;
		float4 norm;
		float4 color;
	};

}