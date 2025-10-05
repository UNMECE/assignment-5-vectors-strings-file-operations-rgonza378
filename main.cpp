#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "pixel.h"

using namespace std;

void average_colors(vector<Pixel> &pixel_list) {
		double r_sum = 0, g_sum = 0, b_sum = 0;
		int n = pixel_list.size();

		for (int i = 0; i < n; i++) {
				r_sum += pixel_list[i].r;
				g_sum += pixel_list[i].g;
				b_sum += pixel_list[i].b;
		}

		cout << "Average R: " << r_sum / n << endl;
		cout << "Average G: " << g_sum / n << endl;
		cout << "Average B: " << b_sum / n << endl;
}

void flip_vertically(vector<Pixel> &pixel_list) {
		int y_max = 255;
		for (int i = 0; i < pixel_list.size(); i++) {
				pixel_list[i].y = y_max - pixel_list[i].y;
		}
}

int main(int argc, char* argv[]) {
		if (argc < 2) {
				cout << "Usage: ./main pixels.dat" << endl;
				return 1;
		}

		string filename = argv[1];
		ifstream infile(filename.c_str());
		if (!infile) {
				cout << "Could not open file." << endl;
				return 1;
		}

		vector<Pixel> pixel_list;
		string line;


		while (getline(infile, line)) {
				Pixel p;

				int pos1 = line.find(',');
				int pos2 = line.find(',', pos1+1);
				int pos3 = line.find(',', pos2+1);
				int pos4 = line.find(',', pos3+1);

				string x_str = line.substr(0, pos1);
				string y_str = line.substr(pos1+1, pos2-pos1-1);
				string r_str = line.substr(pos2+1, pos3-pos2-1);
				string g_str = line.substr(pos3+1, pos4-pos3-1);
				string b_str = line.substr(pos4+1);

				p.x = atoi(x_str.c_str());
				p.y = atoi(y_str.c_str());
				p.r = atof(r_str.c_str());
				p.g = atof(g_str.c_str());
				p.b = atof(b_str.c_str());

				pixel_list.push_back(p);
		}
		infile.close();

		cout << "Pixles are loaded " << pixel_list.size() << " said pixels from the file: " << endl;

		average_colors(pixel_list);

		flip_vertically(pixel_list);

		ofstream outfile("flipped.dat");
		for (int i = 0; i < pixel_list.size(); i++) {
				outfile << pixel_list[i].x << ","
								<< pixel_list[i].y << ","
								<< pixel_list[i].r << ","
								<< pixel_list[i].g << ","
								<< pixel_list[i].b << endl;
		}
		outfile.close();

		cout << "image was flipped vertically and saved to file flipped.dat" << endl;

		return 0;
}
