#ifndef TRAYZY_HITTABLELIST_H
#define TRAYZY_HITTABLELIST_H

#include "Hittable.h"
#include "Intersection.h"

#include <memory>
#include <vector>

namespace trayzy
{
	/**
	 * A list of pointers to hittable items.
	 * 
	 * @tparam T The coordinate data type
	 */
	template<typename T>
	class HittableList : public Hittable<T>
	{
	public:
		/// Creates an empty hittable list
		HittableList() = default;

		/**
		 * Creates a hittable list by copying the provided collection of pointers to hittable items.
		 * 
		 * @param hittables The collection of pointers to hittable items
		 */
		HittableList(const std::vector<std::shared_ptr<Hittable<T>>> &hittables) :
			mHittables(hittables)
		{
			// Do nothing more
		}

		/**
		 * Creates a hittable list by moving the provided collection of pointers to hittable items.
		 * 
		 * @param hittables The collection of pointers to hittable items
		 */
		HittableList(std::vector<std::shared_ptr<Hittable<T>>> &&hittables) :
			mHittables(std::move(hittables))
		{
			// Do nothing more
		}

		/**
		 * Inserts a pointer to a hittable item to this list.
		 * 
		 * @param hittable The pointer to the hittable item
		 */
		void insert(std::shared_ptr<Hittable<T>> hittable);

		/**
		 * @copydoc Hittable::hit
		 * 
		 * The intersection will set to the hit against the closest item in the list.
		 */
		virtual bool hit(const Ray<T> &ray, T tMin, T tMax, Intersection<T> &intersection) const override;

	private:
		std::vector<std::shared_ptr<Hittable<T>>> mHittables;
	};
}

namespace trayzy
{
	template<typename T>
	void HittableList<T>::insert(std::shared_ptr<Hittable<T>> hittable)
	{
		mHittables.push_back(hittable);
	}

	template<typename T>
	bool HittableList<T>::hit(const Ray<T> &ray, T tMin, T tMax, Intersection<T> &intersection) const
	{
		Intersection<T> intermediateIntersection;
		bool hitAnything = false;
		T tClosest = tMax;

		for (auto hittable : mHittables)
		{
			if (hittable->hit(ray, tMin, tClosest, intermediateIntersection))
			{
				intersection = intermediateIntersection;
				tClosest = intersection.t;
				hitAnything = true;
			}
		}

		return hitAnything;
	}
}

#endif