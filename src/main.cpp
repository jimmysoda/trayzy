#include <cfloat>
#include <iostream>
#include <memory>
#include <random>

#include <trayzy/Camera.h>
#include <trayzy/HittableList.h>
#include <trayzy/Ray.h>
#include <trayzy/Sphere.h>
#include <trayzy/Vec3.h>

using Cameraf = trayzy::Camera<float>;
using HittableListf = trayzy::HittableList<float>;
using Rayf = trayzy::Ray<float>;
using Spheref = trayzy::Sphere<float>;
using Vec3f = trayzy::Vec3<float>;
using Vec3i = trayzy::Vec3<int>;

std::random_device rd;
std::default_random_engine engine(rd());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

template<typename T>
trayzy::Vec3<T> randomInUnitSphere()
{
	trayzy::Vec3<T> ijk(T(1.0), T(1.0), T(1.0));
	trayzy::Vec3<T> p;

	do
	{
		p = T(2.0) * trayzy::Vec3<T>(distribution(engine), distribution(engine), distribution(engine)) - ijk;
	} while (p.magnitudeSquared() >= T(1.0));

	return p;
}

template<typename T>
trayzy::Vec3<T> color(const trayzy::Ray<T> &ray, const trayzy::HittableList<T> &world)
{
	trayzy::Vec3<T> c;
	trayzy::Vec3<T> white(1, 1, 1);
	trayzy::HitRecord<T> record;

	if (world.hit(ray, T(0), T(FLT_MAX), record))
	{
		trayzy::Vec3<T> target = record.p + record.normal + randomInUnitSphere<T>();
		c = T(0.5) * color(trayzy::Ray<T>(record.p, target - record.p), world);
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

	HittableListf world;
	world.insert(std::make_shared<Spheref>(Vec3f(0.0f, 0.0f, -1.0f), 0.5f));
	world.insert(std::make_shared<Spheref>(Vec3f(0.0f, -100.5f, -1.0f), 100.0f));
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
				fColor += color(ray, world);
			}

			fColor /= float(nSamples);

			Vec3i iColor(
				int(fColor[trayzy::R] * maxValue),
				int(fColor[trayzy::G] * maxValue),
				int(fColor[trayzy::B] * maxValue)
			);

			out << iColor << std::endl;
		}
	}
}
