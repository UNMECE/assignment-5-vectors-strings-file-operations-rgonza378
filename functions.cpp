#include <iostream>
#include "functions.h"

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

