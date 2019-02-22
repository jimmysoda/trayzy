#ifndef TRAYZY_METAL_H
#define TRAYZY_METAL_H

#include "Material.h"

namespace trayzy
{
	/// A metallic material
	template<typename T>
	class Metal : public Material<T>
	{
	public:
		/// Creates a new metallic material
		Metal(const Vec3<T> &albedo = Vec3<T>()) :
			mAlbedo(albedo)
		{
			// Do nothing more
		}

		// Material::scatter
		virtual bool scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
			Vec3<T> &attenuation, Ray<T> &scattered) const override;

	private:
		/// Reflects a vector at a surface with the provided normal.
		static Vec3<T> reflect(const Vec3<T> &v, const Vec3<T> &n);

	private:
		Vec3<T> mAlbedo;
	};
}

namespace trayzy
{
	template<typename T>
	bool Metal<T>::scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
		Vec3<T> &attenuation, Ray<T> &scattered) const
	{
		Vec3<T> reflected = reflect(unitVector(inbound.direction()), intersection.normal);
		scattered = Ray<T>(intersection.p, reflected);
		attenuation = mAlbedo;
		return dot(scattered.direction(), intersection.normal) > 0;
	}

	/* static */
	template<typename T>
	Vec3<T> Metal<T>::reflect(const Vec3<T> &v ,const Vec3<T> &n)
	{
		return v - T(2) * dot(v, n) * n;
	}
}

#endif
