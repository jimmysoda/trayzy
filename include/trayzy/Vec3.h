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
	/**
	 * A three-dimensional vector.
	 * 
	 * @tparam T The coordinate data type
	 */
	template<typename T>
	class Vec3 : public std::array<T, 3>
	{
	public:
		/**
		 * Creates a new three-dimensional vector.
		 * 
		 * @param a The first coordinate value
		 * @param b The second coordinate value
		 * @param c The third coordinate value
		 */
		Vec3(T a = T(), T b = T(), T c = T()) :
			std::array<T, 3>{a, b, c}
		{
			// Do nothing more
		}

		/// Returns this three-dimensional vector.
		inline Vec3<T> &operator+() const;

		/// Returns a negated copy of this three-dimensional vector.
		inline Vec3<T> operator-() const;

		/// Performs an element-wise sum with another vector.
		inline Vec3<T> &operator+=(const Vec3<T> &v);

		/// Performs an element-wise subtraction with another vector.
		inline Vec3<T> &operator-=(const Vec3<T> &v);

		/// Performs an element-wise multiplication with another vector.
		inline Vec3<T> &operator*=(const Vec3<T> &v);

		/// Performs an element-wise division with another vector.
		inline Vec3<T> &operator/=(const Vec3<T> &v);

		/// Performs an element-wise multiplication with a scalar value.
		inline Vec3<T> &operator*=(const T &t);

		/// Performs an element-wise division with a scalar value.
		inline Vec3<T> &operator/=(const T &t);

		/// Computes the squared magnitude of this vector.
		inline T magnitudeSquared() const;

		/// Computes the magnitude of this vector.
		inline T magnitude() const;

		/// Normalizes this vector into a unit vector.
		inline Vec3<T> &normalize();
	};

	/// Reads the contents of a vector from an input stream
	template<typename T>
	inline std::istream &operator>>(std::istream &is, Vec3<T> &v);

	/// Writes the contents of a vector to an input stream
	template<typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v);

	/// Computes the element-wise sum between two vectors.
	template<typename T>
	inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes the element-wise difference between two vectors.
	template<typename T>
	inline Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes the element-wise product between two vectors.
	template<typename T>
	inline Vec3<T> operator*(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes the element-wise quotient between two vectors.
	template<typename T>
	inline Vec3<T> operator/(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes the element-wise sum between a vector and a scalar.
	template<typename T>
	inline Vec3<T> operator+(const Vec3<T> &v, const T &t);

	/// Computes the element-wise difference between a vector and a scalar.
	template<typename T>
	inline Vec3<T> operator-(const Vec3<T> &v, const T &t);

	/// Computes the element-wise product between a vector and a scalar.
	template<typename T>
	inline Vec3<T> operator*(const Vec3<T> &v, const T &t);

	/// Computes the element-wise quotient between a vector and a scalar.
	template<typename T>
	inline Vec3<T> operator/(const Vec3<T> &v, const T &t);

	/// Computes the element-wise product between a scalar and a vector.
	template<typename T>
	inline Vec3<T> operator*(const T &t, const Vec3<T> &v);

	/// Computes the dot product between two vectors.
	template<typename T>
	inline T dot(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes the cross product between two vectors.
	template<typename T>
	inline Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2);

	/// Computes unit vector equivalent of a vector.
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
		std::transform(this->cbegin(), this->cend(), this->begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, t));
		return *this;
	}

	template<typename T>
	Vec3<T> &Vec3<T>::operator/=(const T &t)
	{
		std::transform(this->cbegin(), this->cend(), this->begin(), std::bind(std::divides<T>(), std::placeholders::_1, t));
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
