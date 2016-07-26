#pragma once

#include "primatives.h"

namespace uti
{
	TAT_DEF bool rayVsSphere(const Ray& ray, const Sphere& sphere, float3* pos = nullptr, float3* norm = nullptr);
}
