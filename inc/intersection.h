#pragma once

#include "primatives.h"

namespace uti
{
	TAT_DEF bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos = nullptr, float4* norm = nullptr);

	TAT_DEF bool ray_vs_sphere(const Ray& ray, const float4& sphere_pos, float sphere_radius, float4* pos = nullptr, float4* norm = nullptr);
}
