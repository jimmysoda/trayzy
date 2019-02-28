#ifndef TRAYZY_CAMERA_H
#define TRAYZY_CAMERA_H

#include "Forward.h"
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
		 * Creates a new camera with the provided camera characteristics.
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
		 * Creates a new camera.
		 *
		 * @param lookFrom The camera location
		 * @param lookAt The observed location
		 * @param up The upward direction
		 * @param verticalFovDegrees The vertical field of view in degrees
		 * @param aspectRatio The ratio between the horizontal and vertical draw plane axis lengths
		 */
		Camera(const Vec3<T> &lookFrom, const Vec3<T> &lookAt, const Vec3<T> &up,
			T verticalFovDegrees, T aspectRatio) :
			mOrigin(lookFrom)
		 {
		 	// Convert the vertical field of view to radians
			T theta = verticalFovDegrees * T(M_PI) / 180;
			T halfHeight = std::tan(theta / 2);
			T halfWidth = aspectRatio * halfHeight;

			// Compute the horizontal and vertical axes of the draw plane
			Vec3<T> w = unitVector(lookFrom - lookAt);
			Vec3<T> u = unitVector(cross(up, w));
			Vec3<T> v = cross(w, u);

			mLowerLeft = mOrigin - halfWidth * u - halfHeight * v - w;
			mHorizontal = 2 * halfWidth * u;
			mVertical = 2 * halfHeight * v;
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