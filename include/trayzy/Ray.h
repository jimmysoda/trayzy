#ifndef TRAYZY_RAY_H
#define TRAYZY_RAY_H

#include "Vec3.h"

namespace trayzy
{
	/**
	 * A direction bounded by a starting location.
	 * 
	 * @tparam T The coordinate data type
	 */
	template <typename T>
	class Ray
	{
	public:
		/// Creates a new ray at the origin with zero direction.
		Ray() = default;

		/**
		 * Creates a new ray.
		 * 
		 * @param origin The starting location
		 * @param direction The outgoing direction
		 */
		Ray(const Vec3<T> &origin, const Vec3<T> &direction) :
			mDirection(direction),
			mOrigin(origin)
		{
			// Do nothing more
		}

		/// Returns the ray's origin
		inline const Vec3<T> &origin() const;

		/// Returns the ray's dimension
		inline const Vec3<T> &direction() const;

		/** 
		 * Returns the point at the provided parametric coordinate.
		 * 
		 * @param t The parametric coordinate
		 * @return The point at the parametric coordinate
		 */
		inline Vec3<T> pointAtParameter(T t) const;

	private:
		Vec3<T> mOrigin;
		Vec3<T> mDirection;
	};
}

// Inline implementation
namespace trayzy
{
	template <typename T>
	const Vec3<T> &Ray<T>::origin() const
	{
		return mOrigin;
	}

	template <typename T>
	const Vec3<T> &Ray<T>::direction() const
	{
		return mDirection;
	}

	template <typename T>
	Vec3<T> Ray<T>::pointAtParameter(T t) const
	{
		return mOrigin + t * mDirection;
	}
}

#endif
