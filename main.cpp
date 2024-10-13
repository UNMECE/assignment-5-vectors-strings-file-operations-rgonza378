#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];  // The input file (pixels.dat)
    std::ifstream file(filename);    // Open the file for reading

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return 1;
    }

    std::vector<Pixel> pixel_list;   // Create a vector to store Pixel structs
    std::string line;                // Variable to store each line from the file

    while (std::getline(file, line)) {
        std::stringstream ss(line);  // Create a stringstream for the line
        std::string token;           // Variable to hold each value in the line

        Pixel pixel;  // Create a Pixel object to store the values

        std::getline(ss, token, ',');
        pixel.x = std::stoi(token);  // Convert string to integer for x

        std::getline(ss, token, ',');
        pixel.y = std::stoi(token);  // Convert string to integer for y

        std::getline(ss, token, ',');
        pixel.r = std::stof(token);  // Convert string to float for r

        std::getline(ss, token, ',');
        pixel.g = std::stof(token);  // Convert string to float for g

        std::getline(ss, token, ',');
        pixel.b = std::stof(token);  // Convert string to float for b

        pixel_list.push_back(pixel);
    }

    file.close();  // Close the input file after reading

    average_colors(pixel_list);

    flip_vertically(pixel_list);

    std::ofstream outFile("flipped.dat");
    for (const auto& pixel : pixel_list) {
        outFile << pixel.x << ',' << pixel.y << ',' << pixel.r << ',' << pixel.g << ',' << pixel.b << '\n';
    }

    outFile.close();
    std::cout << "Flipped image saved to flipped.dat." << std::endl;

    return 0;
}

void average_colors(std::vector<Pixel> &pixel_list) {
    float sum_r = 0.0f, sum_g = 0.0f, sum_b = 0.0f;
    for (const auto& pixel : pixel_list) {
        sum_r += pixel.r;
        sum_g += pixel.g;
        sum_b += pixel.b;
    }

    int total_pixels = pixel_list.size();
    std::cout << "Average R: " << sum_r / total_pixels << std::endl;
    std::cout << "Average G: " << sum_g / total_pixels << std::endl;
    std::cout << "Average B: " << sum_b / total_pixels << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list) {
    int max_y = 255; // Assuming the y-length is 256 (0-255)

    for (auto& pixel : pixel_list) {
        pixel.y = max_y - pixel.y;  // Flip y-coordinate
    }
}

