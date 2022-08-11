#include<iostream>

using namespace std;

int main() {
	const int width = 256;
	const int height = 256;

	cout << "P3" << endl;
	cout << width << " " << height << endl;
	cout << "255" << endl;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int r = x, g = y, b = 0;
			cout << r << " " << g << " " << b << endl;
		}
		int percent = (int)(100.0 * y / (height - 1));
		cerr << "\rRendering " << percent << "%" << flush;
	}

}
