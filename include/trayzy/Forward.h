#ifndef TRAYZY_FORWARD_H
#define TRAYZY_FORWARD_H

// Aliases
namespace trayzy
{
	constexpr auto X = 0;
	constexpr auto Y = 1;
	constexpr auto Z = 2;

	constexpr auto R = 0;
	constexpr auto G = 1;
	constexpr auto B = 2;
}

// Forward declarations
namespace trayzy
{
	template<typename T> class Camera;
	template<typename T> class Dielectric;
	template<typename T> class Hittable;
	template<typename T> class HittableList;
	template<typename T> struct Intersection;
	template<typename T> class Lambertian;
	template<typename T> class Material;
	template<typename T> class Metal;
	template<typename T> class Ray;
	template<typename T> class Sphere;
	template<typename T> class Vec3;

	using HittableListf = HittableList<float>;
}

#endif

