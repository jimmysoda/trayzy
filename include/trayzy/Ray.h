#ifndef TRAYZY_RAY_H
#define TRAYZY_RAY_H

#include "Vec3.h"

namespace trayzy
{
	template <typename T>
	class Ray
	{
	public:
		Ray(const Vec3<T> &origin, const Vec3<T> &direction) :
			mDirection(direction),
			mOrigin(origin)
		{
			// Do nothing more
		}

		inline Vec3<T> &origin() const;
		inline Vec3<T> &direction() const;
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
	Vec3<T> &Ray<T>::origin() const
	{
		return mOrigin;
	}

	template <typename T>
	Vec3<T> &Ray<T>::direction() const
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
