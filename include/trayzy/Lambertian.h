#ifndef TRAYZY_LAMBERTIAN_H
#define TRAYZY_LAMBERTIAN_H

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

#include <random>

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
		/// Returns a random vector within the unit sphere
		static Vec3<T> randomInUnitSphere();

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
		Vec3<T> target = intersection.p + intersection.normal + randomInUnitSphere();
		scattered = Ray<T>(intersection.p, target - intersection.p);
		attenuation = mAlbedo;
		return true;
	}

	/* static */
	template<typename T>
	Vec3<T> Lambertian<T>::randomInUnitSphere()
	{
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_real_distribution<T> distribution(T(0.0), T(1.0));

		Vec3<T> ijk(T(1.0), T(1.0), T(1.0));
		Vec3<T> p;

		do
		{
			p = T(2.0) * Vec3<T>(distribution(engine), distribution(engine), distribution(engine)) - ijk;
		} while (p.magnitudeSquared() >= T(1.0));

		return p;
	}
}

#endif