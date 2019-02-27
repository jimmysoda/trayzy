#ifndef TRAYZY_MATERIAL_H
#define TRAYZY_MATERIAL_H

#include "Forward.h"
#include "Vec3.h"

#include <random>

namespace trayzy
{
	/**
	 * A material to represent light scattering.
	 */
	template<typename T>
	class Material
	{
	public:
		/**
		 * Scatters an inbound ray.
		 * 
		 * @param inbound The inbound ray
		 * @param intersection The properties at the intersection location
		 * @param[out] attenuation The attenuation of the scattered ray
		 * @param[out] scattered The scattered ray
		 * @return Whether the inbound ray was scattered
		 */
		virtual bool scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
			Vec3<T> &attenuation, Ray<T> &scattered) const = 0;

	protected:
		/// Returns a random vector within the unit sphere
		static Vec3<T> randomInUnitSphere();

		/// Reflects a vector at a surface with the provided normal.
		static Vec3<T> reflect(const Vec3<T> &v, const Vec3<T> &n);

	};
}

namespace trayzy
{
	/* static */
	template<typename T>
	Vec3<T> Material<T>::randomInUnitSphere()
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

	/* static */
	template<typename T>
	Vec3<T> Material<T>::reflect(const Vec3<T> &v ,const Vec3<T> &n)
	{
		return v - T(2) * dot(v, n) * n;
	}

}

#endif