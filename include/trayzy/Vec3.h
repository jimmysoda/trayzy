#ifndef TRAYZY_VEC3_H
#define TRAYZY_VEC3_H

#include "Forward.h"

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>

namespace trayzy
{
	template<typename T>
	class Vec3 : public std::array<T, 3>
	{
	public:
		Vec3(T a = T(), T b = T(), T c = T()) :
			std::array<T, 3>{a, b, c}
		{
			// Do nothing more
		}

		inline Vec3<T> &operator+() const;
		inline Vec3<T> operator-() const;
		inline Vec3<T> &operator+=(const Vec3<T> &v);
		inline Vec3<T> &operator-=(const Vec3<T> &v);
		inline Vec3<T> &operator*=(const Vec3<T> &v);
		inline Vec3<T> &operator/=(const Vec3<T> &v);
		inline Vec3<T> &operator*=(const T &t);
		inline Vec3<T> &operator/=(const T &t);

		inline T magnitudeSquared() const;
		inline T magnitude() const;
		inline Vec3<T> &normalize();
	};

	template<typename T>
	inline std::istream &operator>>(std::istream &is, Vec3<T> &v);

	template<typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v);

	template<typename T>
	inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> operator*(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> operator/(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> operator+(const Vec3<T> &v, const T &t);

	template<typename T>
	inline Vec3<T> operator-(const Vec3<T> &v, const T &t);

	template<typename T>
	inline Vec3<T> operator*(const Vec3<T> &v, const T &t);

	template<typename T>
	inline Vec3<T> operator/(const Vec3<T> &v, const T &t);

	template<typename T>
	inline Vec3<T> operator*(const T &t, const Vec3<T> &v);

	template<typename T>
	inline T dot(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2);

	template<typename T>
	inline Vec3<T> unitVector(const Vec3<T> &v);
}

// Inline implementation
namespace trayzy
{
	// Member methods

	template<typename T>
	Vec3<T> &Vec3<T>::operator+() const
	{
		return *this;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator-() const
	{
		Vec3<T> result;
		std::transform(this->cbegin(), this->cend(), result.begin(), std::negate<T>());
		return result;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &v)
	{
		std::transform(this->cbegin(), this->cend(), v.cbegin(), this->begin(), std::plus<T>());
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &v)
	{
		std::transform(this->cbegin(), this->cend(), v.cbegin(), this->begin(), std::minus<T>());
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &v)
	{
		std::transform(this->cbegin(), this->cend(), v.cbegin(), this->begin(), std::multiplies<T>());
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &v)
	{
		std::transform(this->cbegin(), this->cend(), v.cbegin(), this->begin(), std::divides<T>());
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator*=(const T &t)
	{
		std::transform(this->cbegin(), this->cend(), t->begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, t));
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator/=(const T &t)
	{
		std::transform(this->cbegin(), this->cend(), t->begin(), std::bind(std::divides<T>(), std::placeholders::_1, t));
		return *this;
	}

	template<typename T>
	T Vec3<T>::magnitudeSquared() const
	{
		return std::inner_product(this->cbegin(), this->cend(), this->cbegin(), T());
	}

	template<typename T>
	T Vec3<T>::magnitude() const
	{
		return std::sqrt(magnitudeSquared());
	}

	template<typename T>
	Vec3<T> &Vec3<T>::normalize()
	{
		*this /= magnitude();
		return *this;
	}

	// Namespace-scope methods
	template<typename T>
	std::istream &operator>>(std::istream &is, Vec3<T> &v)
	{
		for (T &t : v)
		{
			is >> t;
		}

		return is;
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &os, const Vec3<T> &v)
	{
		auto itr = v.cbegin();
		os << *itr++;

		for (; itr != v.cend(); ++itr)
		{
			os << " " << *itr;
		}

		return os;
	}

	template<typename T>
	Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		Vec3<T> result;
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), result.begin(), std::plus<T>());
		return result;
	}

	template<typename T>
	Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		Vec3<T> result;
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), result.begin(), std::minus<T>());
		return result;
	}

	template<typename T>
	Vec3<T> operator*(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		Vec3<T> result;
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), result.begin(), std::multiplies<T>());
		return result;
	}

	template<typename T>
	Vec3<T> operator/(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		Vec3<T> result;
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), result.begin(), std::divides<T>());
		return result;
	}

	template<typename T>
	Vec3<T> operator+(const Vec3<T> &v, const T &t)
	{
		Vec3<T> result;
		std::transform(v.cbegin(), v.cend(), result.begin(), std::bind(std::plus<T>(), std::placeholders::_1, t));
		return result;
	}

	template<typename T>
	Vec3<T> operator-(const Vec3<T> &v, const T &t)
	{
		Vec3<T> result;
		std::transform(v.cbegin(), v.cend(), result.begin(), std::bind(std::minus<T>(), std::placeholders::_1, t));
		return result;
	}

	template<typename T>
	Vec3<T> operator*(const Vec3<T> &v, const T &t)
	{
		Vec3<T> result;
		std::transform(v.cbegin(), v.cend(), result.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, t));
		return result;
	}

	template<typename T>
	Vec3<T> operator/(const Vec3<T> &v, const T &t)
	{
		Vec3<T> result;
		std::transform(v.cbegin(), v.cend(), result.begin(), std::bind(std::divides<T>(), std::placeholders::_1, t));
		return result;
	}

	template<typename T>
	Vec3<T> operator*(const T &t, const Vec3<T> &v)
	{
		return v * t;
	}

	template<typename T>
	T dot(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), T());
	}

	template<typename T>
	Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		return Vec3<T>(
			v1[1] * v2[2] - v1[2] * v1[1],
			v1[2] * v2[0] - v1[0] * v1[2],
			v1[0] * v2[1] - v1[1] * v2[0]
		);
	}

	template<typename T>
	Vec3<T> unitVector(const Vec3<T> &v)
	{
		return v / v.magnitude();
	}
}

#endif
