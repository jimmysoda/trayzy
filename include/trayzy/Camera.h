#ifndef TRAYZY_CAMERA_H
#define TRAYZY_CAMERA_H

#include "Ray.h"

namespace trayzy
{
	/**
	 * A simple axis-aligned camera.
	 */
	template<typename T>
	class Camera
	{
	public:
		/**
		 * Creates a new camera.
		 * 
		 * @param origin The camera's origin
		 * @param lowerLeft The location of the canvas's lower-left location
		 * @param horizontal The horizontal component of the canvas's dimensions
		 * @param vertical The vertical component of the canvas's dimensions
		 */
		Camera(const Vec3<T> &origin = Vec3<T>(0, 0, 0), const Vec3<T> &lowerLeft = Vec3<T>(-2, -1, -1),
			const Vec3<T> &horizontal = Vec3<T>(4, 0, 0), const Vec3<T> &vertical = Vec3<T>(0, 2, 0)) :
			mHorizontal(horizontal),
			mLowerLeft(lowerLeft),
			mOrigin(origin),
			mVertical(vertical)
		{
			// Do nothing more
		}

		/**
		 * Returns a ray from this camera's origin to the provided canvas coordinates
		 * 
		 * @param u The horizontal canvas coordinate
		 * @param v The vertical canvas coordinate
		 * @return The ray from the origin to the canvas coordinates
		 */
		Ray<T> getRay(T u, T v);

		inline const Vec3<T> &origin() const;
		inline const Vec3<T> &lowerLeft() const;
		inline const Vec3<T> &horizontal() const;
		inline const Vec3<T> &vertical() const;

	private:
		Vec3<T> mOrigin;
		Vec3<T> mLowerLeft;
		Vec3<T> mHorizontal;
		Vec3<T> mVertical;
	};
}

namespace trayzy
{
	template<typename T>
	Ray<T> Camera<T>::getRay(T u, T v)
	{
		return Ray<T>(mOrigin, mLowerLeft + u * mHorizontal + v * mVertical - mOrigin);
	}

	template<typename T>
	const Vec3<T> &Camera<T>::origin() const
	{
		return mOrigin;
	}

	template<typename T>
	const Vec3<T> &Camera<T>::lowerLeft() const
	{
		return mLowerLeft;
	}

	template<typename T>
	const Vec3<T> &Camera<T>::horizontal() const
	{
		return mHorizontal;
	}

	template<typename T>
	const Vec3<T> &Camera<T>::vertical() const
	{
		return mVertical;
	}
}

#endif