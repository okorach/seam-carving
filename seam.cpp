#include <cassert>
#include <limits>
#include <tgmath.h>
#include <vector>

#include "seam.h"

using namespace std;

// ***********************************
// TASK 1: COLOR
// ***********************************

// Returns red component (in the scale 0.0-1.0) from given RGB color.
// 110100001 10101111 10001110 01111010

double get_red(int rgb)
{
    return ((rgb >> 16) & 0xff) / 255.0;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb)
{
    int green((rgb >> 8) & 0xff);
    return green / 255.0;
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb)
{
    return (rgb & 0xff) / 255.0;
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb)
{
    return (get_blue(rgb) + get_red(rgb) + get_green(rgb)) / 3;
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue)
{
    int rgb;
    rgb = ((int(red * 255)) << 16) + ((int(green * 255)) << 8) + int(blue * 255);
    return rgb;
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray)
{
    int grayint(gray * 255);
    grayint = (grayint << 16) + (grayint << 8) + grayint;
    return grayint;
}

// Converts  RGB image to grayscale double image.
GrayImage to_gray(const RGBImage &cimage)
{
    GrayImage gray;
    vector<double> line;
    for (size_t i(0); i < cimage.size(); ++i)
    {
        line.clear();
        for (size_t j(0); j < cimage[i].size(); ++j)
        {
            line.push_back(get_gray(cimage[i][j]));
        }
        gray.push_back(line);
    }

    return {gray}; // TODO MODIFY AND COMPLETE
}

// Converts grayscale double image to an RGB image.
RGBImage to_RGB(const GrayImage &gimage)
{
    RGBImage color;
    vector<int> line;
    for (size_t i(0); i < gimage.size(); ++i)
    {
        line.clear();
        for (size_t j(0); j < gimage[i].size(); ++j)
        {
            line.push_back(get_RGB(gimage[i][j]));
        }
        color.push_back(line);
    }

    return {color}; // TODO MODIFY AND COMPLETE
}

// ***********************************
// TASK 2: FILTER
// ***********************************

// Get a pixel without accessing out of bounds
// return nearest valid pixel color
long clamp(long val, long max)
{
    if (val < 0)
    {
        val = 0;
    }
    if (val > max)
    {
        val = max;
    }
    return val;
}

// Convolve a single-channel image with the given kernel.
GrayImage filter(const GrayImage &gray, const Kernel &kernel)
{
    GrayImage filtered;
    vector<double> line;
    long max_i(gray.size());
    long max_j(gray[0].size());
    for (long i(0); i < max_i; ++i)
    {
        line.clear();
        for (long j(0); j < max_j; ++i)
        {
            long val = kernel[0][0] * gray[clamp(i - 1, max_i)][clamp(j - 1, max_j)] +
            kernel[0][1] * gray[clamp(i - 1,max_i)][j] + 
            kernel[0][2] * gray[clamp(i - 1,max_i)][clamp(j + 1, max_j)];
            val = val + kernel[1][0] * gray[clamp(i, max_i)][clamp(j - 1, max_j)] +
            kernel[1][1] * gray[clamp(i,max_i)][j] + 
            kernel[1][2] * gray[clamp(i,max_i)][clamp(j + 1, max_j)];
            val = val + kernel[2][0] * gray[clamp(i+1, max_i)][clamp(j - 1, max_j)] +
            kernel[2][1] * gray[clamp(i+1,max_i)][j] + 
            kernel[2][2] * gray[clamp(i+1,max_i)][clamp(j + 1, max_j)];
            line.push_back(val);

        }
        filtered.push_back(line);
    }
    return filtered;
}

// Smooth a single-channel image
GrayImage smooth(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute horizontal Sobel filter

GrayImage sobelX(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute vertical Sobel filter

GrayImage sobelY(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Compute the magnitude of combined Sobel filters

GrayImage sobel(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// ************************************
// TASK 3: SEAM
// ************************************

Graph create_graph(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Return shortest path from Node from to Node to
// The path does NOT include the from and to Node
Path shortest_path(Graph &graph, size_t from, size_t to)
{

    return {}; // TODO MODIFY AND COMPLETE
};

Path find_seam(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// ***********************************
// TASK 3 provided functions
// Highlight or remove seam from RGB or gray image
// ***********************************

// Draw a seam on a gray image
// return a new gray image with the seam in black
GrayImage highlight_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    // Paint seam in black
    for (size_t row(0); row < seam.size(); ++row)
    {
        result[row][seam[row]] = 0;
    }
    return result;
}

// Draw a seam on an RGB image
// return a new RGB image with the seam in blue
RGBImage highlight_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    // Paint seam in blue
    for (size_t row(0); row < seam.size(); ++row)
    {
        result[row][seam[row]] = 0x000ff;
    }
    return result;
}

// Remove specified seam from a gray-scale image
// return the new gray image (width is decreased by 1)

GrayImage remove_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    for (size_t row(0); row < seam.size(); ++row)
    {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}

// Remove specified seam from an RGB image
// return the new RGB image (width is decreased by 1)
RGBImage remove_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    for (size_t row(0); row < seam.size(); ++row)
    {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}

// Computes the convolution of the central pixel of
// a nxn gray image and a nxn kernel
double convolve_nxn(const GrayImage& gray, const Kernel& kernel, const int n)
{
    vector<double> line;
    double result(0);
    for (long i(0); i < n; ++i)
    {
        for (long j(0); j < n; ++i)
        {
            result = result + kernel[i][j] * gray[i][j];
        }
    }
    return result;
}

// Computes the convolution of the central pixel of
// a 3x3 gray image and a 3x3 kernel
double convolve_3x3(const GrayImage& gray, const Kernel& kernel)
{
    return convolve_nxn(gray, kernel, 3)
}