#include <cstdio>
#include <trayzy/Vec3.h>
#include <trayzy/Ray.h>

int main(int argc, char **argv)
{
	// TODO Read column count, row count, max value, and output file from arguments
	int nCols = 200;
	int nRows = 100;
	int maxValue = 255;
	std::FILE *out = stdout;

	trayzy::Ray<float> ray(trayzy::Vec3<float>(), trayzy::Vec3<float>(1, 1, 1));
	trayzy::Vec3<float> pointAtT2 = ray.pointAtParameter(2);

	std::fprintf(out, "P3\n%d %d\n%d\n", nCols, nRows, maxValue);

	for (int row = nRows - 1; row >= 0; --row)
	{
		for (int col = 0; col < nCols; ++col)
		{
			trayzy::Vec3<float> color(float(col) / nCols, float(row) / nRows, 0.2f);

			std::fprintf(out, "%d %d %d\n",
				int(color[trayzy::R] * maxValue),
				int(color[trayzy::G] * maxValue),
				int(color[trayzy::B] * maxValue)
			);
		}
	}
}
