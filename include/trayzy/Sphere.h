#ifndef TRAYZY_SPHERE_H
#define TRAYZY_SPHERE_H

#include "Hittable.h"
#include "Intersection.h"
#include "Ray.h"

#include <memory>

namespace trayzy
{
	/**
	 * The surface composed from all points equidistant from a common origin.
	 */
	template<typename T>
	class Sphere : public Hittable<T>
	{
	public:
		Sphere(const Vec3<T> &center = Vec3<T>(), T radius = T(),
			std::shared_ptr<Material<T>> material = nullptr) :
			mCenter(center),
			mMaterial(material),
			mRadius(radius)
		{
			// Do nothing more
		}

		// Hittable::hit
		virtual bool hit(const Ray<T> &ray, T tMin, T tMax, Intersection<T> &intersection) const override;

	private:
		Vec3<T> mCenter;
		T mRadius;
		std::shared_ptr<Material<T>> mMaterial;
	};
}

namespace trayzy
{
	template<typename T>
	bool Sphere<T>::hit(const Ray<T> &ray, T tMin, T tMax, Intersection<T> &intersection) const
	{
		Vec3<T> oc = ray.origin() - mCenter;

		// Note that the magnitude squared of a vector is equal to the dot product with itself
		T a = ray.direction().magnitudeSquared();
		T b = 2 * dot(oc, ray.direction());
		T c = oc.magnitudeSquared() - mRadius * mRadius;

		T discriminant = b * b - 4 * a * c;
		bool hasHit = false;

		if (discriminant > 0)
		{
			T sqrtDiscriminant =  std::sqrt(discriminant);

			for (T sign : {T(-1), T(1)})
			{
				T root = (-b + sign * sqrtDiscriminant) / (2 * a);

				if (root < tMax && root > tMin)
				{
					intersection.t = root;
					intersection.p = ray.pointAtParameter(intersection.t);
					intersection.normal = (intersection.p - mCenter) / mRadius;
					intersection.material = mMaterial;
					hasHit = true;
					break;
				}
			}
		}

		return hasHit;
	}
}

#endif
