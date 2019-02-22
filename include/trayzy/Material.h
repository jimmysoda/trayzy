#ifndef TRAYZY_MATERIAL_H
#define TRAYZY_MATERIAL_H

#include "Forward.h"

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
	};
}

#endif