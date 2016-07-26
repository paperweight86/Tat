#pragma once

#include "types.h"

namespace uti
{

	TAT_DEF struct Ray
	{
		float3 origin;
		float3 dir;
	};

	TAT_DEF struct Sphere
	{
		float3	pos;
		r32		radius;
		float3  color;
	};

	TAT_DEF struct Plane
	{
		float3 pos;
		float3 norm;
		float3 color;
	};

}