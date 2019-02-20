#include <cstdio>

int main(int argc, char **argv)
{
	// TODO Read column count, row count, max value, and output file from arguments
	int nCols = 200;
	int nRows = 100;
	int maxValue = 255;
	std::FILE *out = stdout;

	std::fprintf(out, "P3\n%d %d\n%d\n", nCols, nRows, maxValue);

	float blue = 0.2f;
	int intBlue = int(blue * maxValue);

	for (int row = nRows - 1; row >= 0; --row)
	{
		float green = float(row) / nRows;
		int intGreen = int(green * maxValue) + 1;

		for (int col = 0; col < nCols; ++col)
		{
			float red = float(col) / nCols;
			int intRed = int(red * maxValue);

			std::fprintf(out, "%d %d %d\n", intRed, intGreen, intBlue);
		}
	}
}
