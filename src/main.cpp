#include <cfloat>
#include <iostream>
#include <memory>
#include <random>

#include <trayzy/Camera.h>
#include <trayzy/HittableList.h>
#include <trayzy/Lambertian.h>
#include <trayzy/Metal.h>
#include <trayzy/Ray.h>
#include <trayzy/Sphere.h>
#include <trayzy/Vec3.h>

using Cameraf = trayzy::Camera<float>;
using HittableListf = trayzy::HittableList<float>;
using Lambertianf = trayzy::Lambertian<float>;
using Metalf = trayzy::Metal<float>;
using Rayf = trayzy::Ray<float>;
using Spheref = trayzy::Sphere<float>;
using Vec3f = trayzy::Vec3<float>;
using Vec3i = trayzy::Vec3<int>;

std::random_device rd;
std::default_random_engine engine(rd());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

template<typename T>
trayzy::Vec3<T> color(const trayzy::Ray<T> &ray, const trayzy::HittableList<T> &world, int depth)
{
	trayzy::Vec3<T> c(0, 0, 0);
	trayzy::Vec3<T> white(1, 1, 1);
	trayzy::Intersection<T> intersection;
	
	int maxDepth = 50;
	T hitEpsilon(0.001f);

	if (world.hit(ray, hitEpsilon, T(FLT_MAX), intersection))
	{
		trayzy::Ray<T> scattered;
		trayzy::Vec3<T> attenuation;

		if (depth < maxDepth && intersection.material &&
			intersection.material->scatter(ray, intersection, attenuation, scattered))
		{
			c = attenuation * color(scattered, world, ++depth);
		}
	}
	else
	{
		// Perform a linear blend (a.k.a. linear interpolation or "lerp")
		// from pure white to "Maya blue"
		trayzy::Vec3<T> unitDirection = trayzy::unitVector(ray.direction());
		T t = T(0.5) * (unitDirection[trayzy::Y] + T(1.0));

		trayzy::Vec3<T> mayaBlue(T(0.5), T(0.7), T(1.0));
		c = (T(1.0) - t) * white + t * mayaBlue;
	}

	return c;
}

int main(int argc, char **argv)
{
	// TODO Read column count, row count, max value, and output file from arguments
	int nCols = 200;
	int nRows = 100;
	int nSamples = 100;
	int maxValue = 255;
	std::ostream &out = std::cout;

	out << "P3" << std::endl << nCols << " " << nRows << std::endl << maxValue << std::endl;

	trayzy::HittableListf world;

	world.insert(std::make_shared<Spheref>(
		Vec3f(0.0f, 0.0f, -1.0f), 0.5f,
		std::make_shared<Lambertianf>(Vec3f(0.8f, 0.3f, 0.3f))));

	world.insert(std::make_shared<Spheref>(
		Vec3f(0.0f, -100.5f, -1.0f), 100.0f,
		std::make_shared<Lambertianf>(Vec3f(0.8f, 0.8f, 0.0f))));

	world.insert(std::make_shared<Spheref>(
		Vec3f(1.0f, 0.0f, -1.0f), 0.5f,
		std::make_shared<Metalf>(Vec3f(0.8f, 0.6f, 0.2f))));

	world.insert(std::make_shared<Spheref>(
		Vec3f(-1.0f, 0.0f, -1.0f), 0.5f,
		std::make_shared<Metalf>(Vec3f(0.8f, 0.8f, 0.8f))));

	Cameraf cam;

	for (int j = nRows - 1; j >= 0; --j)
	{
		for (int i = 0; i < nCols; ++i)
		{
			Vec3f fColor;

			for (int s = 0; s < nSamples; ++s)
			{
				float u = (i + distribution(engine)) / nCols;
				float v = (j + distribution(engine)) / nRows;
				Rayf ray = cam.getRay(u, v);
				fColor += color(ray, world, 0);
			}

			fColor /= float(nSamples);

			// Use gamma 2, i.e., raise color to the power 1/gamma which is square root
			fColor = Vec3f(std::sqrt(fColor[trayzy::R]), std::sqrt(fColor[trayzy::G]), std::sqrt(fColor[trayzy::B]));

			Vec3i iColor(
				int(fColor[trayzy::R] * maxValue),
				int(fColor[trayzy::G] * maxValue),
				int(fColor[trayzy::B] * maxValue)
			);

			out << iColor << std::endl;
		}
	}
}
