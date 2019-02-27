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
		Metal(const Vec3<T> &albedo = Vec3<T>(), T fuzz = 1) :
			mAlbedo(albedo),
			mFuzz(fuzz)
		{
			if (mFuzz > 1)
			{
				mFuzz = 1;
			}
		}

		// Material::scatter
		virtual bool scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
			Vec3<T> &attenuation, Ray<T> &scattered) const override;

	private:
		Vec3<T> mAlbedo;
		T mFuzz;
	};
}

namespace trayzy
{
	template<typename T>
	bool Metal<T>::scatter(const Ray<T> &inbound, const Intersection<T> &intersection,
		Vec3<T> &attenuation, Ray<T> &scattered) const
	{
		Vec3<T> reflected = reflect(unitVector(inbound.direction()), intersection.normal);
		scattered = Ray<T>(intersection.p, reflected + mFuzz * Material<T>::randomInUnitSphere());
		attenuation = mAlbedo;
		return dot(scattered.direction(), intersection.normal) > 0;
	}
}

#endif
