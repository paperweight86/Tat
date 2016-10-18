#pragma once

#include "types.h"

namespace uti
{
	struct Ray
	{
		float4 origin;
		float4 dir;
	};

	struct Sphere
	{
		float4	pos;
		r32		radius;
		float4  color;
	};

	struct Plane
	{
		float4 pos;
		float4 norm;
		float4 color;
	};
}