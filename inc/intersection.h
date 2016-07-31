#pragma once

#include "primatives.h"

namespace uti
{
	TAT_DEF bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos = nullptr, float4* norm = nullptr);
}
