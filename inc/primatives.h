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
		float4  color;
		r32		radius;
	};

	struct Plane
	{
		float4 pos;
		float4 norm;
		float4 color;
	};
}