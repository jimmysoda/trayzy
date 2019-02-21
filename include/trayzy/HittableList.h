#ifndef TRAYZY_HITTABLELIST_H
#define TRAYZY_HITTABLELIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

namespace trayzy
{
	template<typename T>
	class HittableList : public Hittable<T>
	{
	public:
		HittableList() = default;

		HittableList(const std::vector<std::shared_ptr<Hittable<T>>> &hittables) :
			mHittables(hittables)
		{
			// Do nothing more
		}

		HittableList(std::vector<std::shared_ptr<Hittable<T>>> &&hittables) :
			mHittables(std::move(hittables))
		{
			// Do nothing more
		}

		void insert(std::shared_ptr<Hittable<T>> hittable);

		virtual bool hit(const Ray<T> &ray, T tMin, T tMax, HitRecord<T> &record) const override;

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
	bool HittableList<T>::hit(const Ray<T> &ray, T tMin, T tMax, HitRecord<T> &record) const
	{
		HitRecord<T> tempRecord;
		bool hitAnything = false;
		T tClosest = tMax;

		for (auto hittable : mHittables)
		{
			if (hittable->hit(ray, tMin, tClosest, tempRecord))
			{
				record = tempRecord;
				tClosest = record.t;
				hitAnything = true;
			}
		}

		return hitAnything;
	}
}

#endif