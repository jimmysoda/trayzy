#ifndef TRAYZY_LAMBERTIAN_H
#define TRAYZY_LAMBERTIAN_H

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

namespace trayzy
{
	/// A Lambertian material
	template<typename T>
	class Lambertian : public Material<T>
	{
	public:
		/// Creates a new Lambertian material
		Lambertian(const Vec3<T> &albedo = Vec3<T>()) :
			mAlbedo(albedo)
		{
			// Do nothing more
		}

		// Material::scatter
		virtual bool scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
			Vec3<T> &attenuation, Ray<T> &scattered) const override;

	private:
		Vec3<T> mAlbedo;
	};
}

namespace trayzy
{
	template<typename T>
	bool Lambertian<T>::scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
		Vec3<T> &attenuation, Ray<T> &scattered) const
	{
		Vec3<T> target = intersection.p + intersection.normal + Material<T>::randomInUnitSphere();
		scattered = Ray<T>(intersection.p, target - intersection.p);
		attenuation = mAlbedo;
		return true;
	}
}

#endif