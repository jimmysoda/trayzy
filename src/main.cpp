#include <cfloat>
#include <iostream>
#include <memory>

#include <trayzy/HittableList.h>
#include <trayzy/Ray.h>
#include <trayzy/Sphere.h>
#include <trayzy/Vec3.h>

using HittableListf = trayzy::HittableList<float>;
using Rayf = trayzy::Ray<float>;
using Spheref = trayzy::Sphere<float>;
using Vec3f = trayzy::Vec3<float>;
using Vec3i = trayzy::Vec3<int>;

template<typename T>
trayzy::Vec3<T> color(const trayzy::Ray<T> &ray, const trayzy::HittableList<T> &world)
{
	trayzy::Vec3<T> c;
	trayzy::Vec3<T> white(1, 1, 1);
	trayzy::HitRecord<T> record;

	if (world.hit(ray, T(0), T(FLT_MAX), record))
	{
		c = T(0.5) * (record.normal + white);
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
	int maxValue = 255;
	std::ostream &out = std::cout;

	out << "P3" << std::endl << nCols << " " << nRows << std::endl << maxValue << std::endl;

	Vec3f lowerLeft(-2.0f, -1.0f, -1.0f);
	Vec3f horizontal(4.0f, 0.0f, 0.0f);
	Vec3f vertical(0.0f, 2.0f, 0.0f);
	Vec3f origin(0.0f, 0.0f, 0.0f);

	HittableListf world;
	world.insert(std::make_shared<Spheref>(Vec3f(0, 0, -1), 0.5));
	world.insert(std::make_shared<Spheref>(Vec3f(0, -100.5, -1), 100));

	for (int row = nRows - 1; row >= 0; --row)
	{
		float v = float(row) / nRows;
		Vec3f verticalOffset = v * vertical;

		for (int col = 0; col < nCols; ++col)
		{
			float u = float(col) / nCols;
			Vec3f horizontalOffset = u * horizontal;
			Rayf ray(origin, lowerLeft + horizontalOffset + verticalOffset);

			Vec3f fColor = color(ray, world);
			Vec3i iColor(
				int(fColor[trayzy::R] * maxValue),
				int(fColor[trayzy::G] * maxValue),
				int(fColor[trayzy::B] * maxValue)
			);

			out << iColor << std::endl;
		}
	}
}
