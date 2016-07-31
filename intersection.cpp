#include "stdafx.h"

#include "intersection.h"
#include "primatives.h"
#include "float4.h"

namespace uti
{
	bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos, float4* normal)
	{
		//float4 dif = ray.dir - ray.origin;

		//float a = uti::dot(dif, dif).get_h();
		//float4 dif2 = ray.dir - sphere.pos;
		//float4 b_ = dif2;
		//b_ = b_ * 2.0f;
		//b_ = uti::dot(dif, dif2);
		//float b = b_.get_h();
		//float c = (uti::dot(sphere.pos, sphere.pos) + uti::dot(ray.origin, ray.origin) +
		//	-2 * uti::dot(sphere.pos, ray.origin)).get_h() - sphere.radius*sphere.radius;

		//float dis = b*b - 4 * a * c;

		//if (dis < 0)
		//	return false;
		//else if (pos == nullptr && normal == nullptr)
		//	return true;

		//float t = (-b - sqrt(dis)) / 2.0f * a;

		//float4 tD =  t * dif;

		//*pos = ray.origin + tD;
		//*normal = (*pos - sphere.pos) / sphere.radius;
		//*normal = uti::norm(*normal);

		//return true;

		float x0 = ray.origin.get_x();
		float y0 = ray.origin.get_y();
		float z0 = ray.origin.get_z();
		float x1 = ray.dir.get_x();
		float y1 = ray.dir.get_y();
		float z1 = ray.dir.get_z();
		float cx = sphere.pos.get_x();
		float cy = sphere.pos.get_y();
		float cz = sphere.pos.get_z();
		float R = sphere.radius;
		float dx = x1 - x0;
		float dy = y1 - y0;
		float dz = z1 - z0;

		float a = dx*dx + dy*dy + dz*dz;
		float b = 2 * dx*(x0 - cx) + 2 * dy*(y0 - cy) + 2 * dz*(z0 - cz);
		float c = cx*cx + cy*cy + cz*cz + x0*x0 + y0*y0 + z0*z0 +
			-2 * (cx*x0 + cy*y0 + cz*z0) - R*R;

		float dis = b*b - 4 * a * c;

		if (dis < 0)
			return false;
		else if (pos == nullptr && normal == nullptr)
			return true;

		float t = (-b - sqrt(dis)) / 2.0f * a;

		float x = x0 + t * dx;
		float y = y0 + t * dy;
		float z = z0 + t * dz;

		*pos = float4(x, y, z);
		*normal = (*pos - sphere.pos) / sphere.radius;
		*normal = uti::norm(*normal);

		return true;
	}
}
