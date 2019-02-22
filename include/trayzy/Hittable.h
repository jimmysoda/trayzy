#ifndef TRAYZY_HITTABLE_H
#define TRAYZY_HITTABLE_H

#include "Forward.h"

namespace trayzy
{
	/**
	 * An item that may be hit by a ray trace.
	 * 
	 * @tparam T The coordinate data type
	 */
	template<typename T>
	class Hittable
	{
	public:
		/**
		 * Determines if a ray hits this item within the provided parametric coordinate range.
		 * 
		 * @param ray The ray to test against this hittable item
		 * @param tMin The minimum parametric coordinate value
		 * @param tMax The maximum parametric coordinate value
		 * @param[out] instersection The details about the ray hit
		 * @return Whether the ray hit this item within the allowed parametric coordinate range
		 */
		virtual bool hit(const Ray<T> &ray, T tMin, T tMax, Intersection<T> &intersection) const = 0;
	};
}

#endif