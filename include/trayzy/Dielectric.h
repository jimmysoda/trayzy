#ifndef TRAYZY_DIELECTRIC_H
#define TRAYZY_DIELECTRIC_H

#include "Intersection.h"
#include "Ray.h"
#include "Vec3.h"

namespace trayzy
{
	/**
	 * A clear material such as water, glass, or diamond.
	 * 
	 * @tparam T The data type to use for coordinates and computation factors
	 */
	template<typename T>
	class Dielectric : public Material<T>
	{
	public:
		/**
		 * Creates a new dielectric material.
		 * 
		 * @param refractionIndex The refraction index (defaults to 1 for air)
		 */
		Dielectric(T refractionIndex = T(1)) :
			mRefractionIndex(refractionIndex)
		{
			// Do nothing more 
		}

		// Material::scatter
		virtual bool scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
			Vec3<T> &attenuation, Ray<T> &scattered) const override;

	private:
		/**
		 * Computes the refraction of a vector at a point on a surface.
		 * 
		 * @param v The incoming vector
		 * @param n The normal at point on the surface
		 * @param refractionRatio The refraction index ratio between the surface's
		 *        outer and inner substances
		 * @param[out] refracted The refracted vector
		 * 
		 * @return Whether the incoming vector was refracted
		 */
		static bool refract(const Vec3<T> &v, const Vec3<T> &n,
			T refractionRatio, Vec3<T> &refracted);

	private:
		T mRefractionIndex;
	};
}

namespace trayzy
{
	/* static */
	template<typename T>
	bool  Dielectric<T>::refract(const Vec3<T> &v, const Vec3<T> &n,
			T refractionRatio, Vec3<T> &refracted)
	{
		Vec3<T> vNormalized = unitVector(v);
		Vec3<T> nNormalized = unitVector(n);

		T dt = dot(vNormalized, nNormalized);
		T discriminant = T(1)- refractionRatio * refractionRatio * (T(1) - dt * dt);
		bool isRefracted = discriminant > T(0);

		if (isRefracted)
		{
			refracted = refractionRatio * (vNormalized - nNormalized * dt)
				- nNormalized * std::sqrt(discriminant);
		}

		return isRefracted;
	}

	template<typename T>
	bool Dielectric<T>::scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
		Vec3<T> &attenuation, Ray<T> &scattered) const
	{
		Vec3<T> outwardNormal;
		Vec3<T> reflected = Material<T>::reflect(inbound.direction(), intersection.normal);
		Vec3<T> refracted;
		T refractionRatio;

		// Attenuation is always 1 since a glass surface absorbs nothing.
		attenuation = Vec3<T>(1, 1, 1);

		if (dot(inbound.direction(), intersection.normal) > T(0))
		{
			outwardNormal = -intersection.normal;
			refractionRatio = mRefractionIndex;
		}
		else
		{
			outwardNormal = intersection.normal;
			refractionRatio = T(1.0) / mRefractionIndex;
		}

		bool isScattered = refract(inbound.direction(), outwardNormal, refractionRatio, refracted);
		scattered = Ray<T>(intersection.p, (isScattered ? refracted : reflected));

		return isScattered;
	}
}

#endif