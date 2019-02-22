#ifndef TRAYZY_INTERSECTION_H
#define TRAYZY_INTERSECTION_H

#include "Forward.h"
#include "Vec3.h"

#include <memory>

namespace trayzy
{
	/**
	 * A record for a ray trace hit.
	 * 
	 * @tparam T The coordinate data type
	 */
	template<typename T>
	struct Intersection
	{
		/// The parametric coordinate of the hit
		T t;

		/// The location of the hit
		Vec3<T> p;

		/// The normal at the hit location
		Vec3<T> normal;

		/// A pointer to the material at the hit point
		std::shared_ptr<Material<T>> material;
	};
}

#endif