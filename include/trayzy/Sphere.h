#ifndef TRAYZY_SPHERE_H
#define TRAYZY_SPHERE_H

#include "Hittable.h"

namespace trayzy
{
	/**
	 * The surface composed from all points equidistant from a common origin.
	 */
	template<typename T>
	class Sphere : public Hittable<T>
	{
	public:
		Sphere(const Vec3<T> &center = Vec3<T>(), T radius = T()) :
			mCenter(center),
			mRadius(radius)
		{
			// Do nothing more
		}

		virtual bool hit(const Ray<T> &ray, T tMin, T tMax, HitRecord<T> &record) const override;

	private:
		Vec3<T> mCenter;
		T mRadius;
	};
}

namespace trayzy
{
	template<typename T>
	bool Sphere<T>::hit(const Ray<T> &ray, T tMin, T tMax, HitRecord<T> &record) const
	{
		Vec3<T> oc = ray.origin() - mCenter;

		// Note that the magnitude squared of a vector is equal to the dot product with itself
		T a = ray.direction().magnitudeSquared();
		T b = 2 * dot(oc, ray.direction());
		T c = oc.magnitudeSquared() - mRadius * mRadius;

		T discriminant = b * b - 4 * a * c;
		bool hasHit = false;

		if (discriminant > T(0))
		{
			T sqrtDiscriminant =  std::sqrt(discriminant);

			for (T sign : {T(-1), T(1)})
			{
				T root = (-b + sign * sqrtDiscriminant) / (2 * a);

				if (root < tMax && root > tMin)
				{
					record.t = root;
					record.p = ray.pointAtParameter(record.t);
					record.normal = (record.p - mCenter) / mRadius;
					hasHit = true;
					break;
				}
			}
		}

		return hasHit;
	}
}

#endif
