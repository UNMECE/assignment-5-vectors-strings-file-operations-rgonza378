#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "pixel.h"

std::vector<Pixel> pixel_list;

void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);
void save_to_file(const std::vector<Pixel> &pixel_list, const std::string &filename);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::ifstream file(input_file);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        Pixel pixel;
        int index = 0;

        while (std::getline(iss, token, ',')) {
            switch (index) {
                case 0: pixel.x = std::stoi(token); break;
                case 1: pixel.y = std::stoi(token); break;
                case 2: pixel.r = std::stof(token); break;
                case 3: pixel.g = std::stof(token); break;
                case 4: pixel.b = std::stof(token); break;
            }
            index++;
        }

        pixel_list.push_back(pixel);
    }

    file.close();

    std::cout << "Pixels read: " << pixel_list.size() << std::endl;

    average_colors(pixel_list);
    flip_vertically(pixel_list);
    save_to_file(pixel_list, "flipped.dat");

    return 0;
}

void average_colors(std::vector<Pixel> &pixel_list) {
    float sum_r = 0, sum_g = 0, sum_b = 0;
    int count = pixel_list.size();

    for (const auto &pixel : pixel_list) {
        sum_r += pixel.r;
        sum_g += pixel.g;
        sum_b += pixel.b;
    }

    float avg_r = sum_r / count;
    float avg_g = sum_g / count;
    float avg_b = sum_b / count;

    std::cout << "Average colors:" << std::endl;
    std::cout << "R: " << avg_r << std::endl;
    std::cout << "G: " << avg_g << std::endl;
    std::cout << "B: " << avg_b << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list) {
    int height = 256;
    for (auto &pixel : pixel_list) {
        pixel.y = height - 1 - pixel.y;
    }
}

void save_to_file(const std::vector<Pixel> &pixel_list, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto &pixel : pixel_list) {
        outfile << pixel.x << "," << pixel.y << "," 
                << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
    }

    outfile.close();
    std::cout << "Flipped image saved to " << filename << std::endl;
}

