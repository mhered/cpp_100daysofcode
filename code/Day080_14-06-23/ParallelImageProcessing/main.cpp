#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include "ppm.h"

// Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
// if possible the function will split mem into equal chunks, if not
// the last chunk will be slightly larger

std::vector<int> bounds(int parts, int mem)
{
    std::vector<int> bnd;
    int delta = mem / parts;
    int reminder = mem % parts;
    int N1 = 0, N2 = 0;
    bnd.push_back(N1);
    for (int i = 0; i < parts; ++i)
    {
        N2 = N1 + delta;
        if (i == parts - 1)
            N2 += reminder;
        bnd.push_back(N2);
        N1 = N2;
    }
    return bnd;
}

// Test if a given position (ii,jj) is "inside" the limits 0..nr_lines and 0..nr_columns
bool border(int ii, int jj, int nr_lines, int nr_columns)
{
    if (ii >= 0 && ii < nr_lines && jj >= 0 && jj < nr_columns)
        return true;
    else
        return false;
}

// Blur the pixel at (i,j) using information from the neighbour pixels
void process(ppm &image, ppm &image2, int i, int j)
{
    int ii, jj, nr_lines, nr_columns, indx;
    unsigned int r, g, b;
    float r_sum, g_sum, b_sum;
    // Filter used for bluring an image
    float filter[] = {
        0.10179640718562874, 0.11377245508982035, 0.10179640718562874,
        0.11377245508982035, 0.1377245508982036, 0.11377245508982035,
        0.10179640718562874, 0.11377245508982035, 0.10179640718562874};

    nr_lines = image.height;
    nr_columns = image.width;

    // Apply the filter:
    r_sum = 0;
    g_sum = 0;
    b_sum = 0;

    // check North-West
    ii = i - 1;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[0];
        g_sum += g * filter[0];
        b_sum += b * filter[0];
    }

    // check North
    ii = i - 1;
    jj = j;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[1];
        g_sum += g * filter[1];
        b_sum += b * filter[1];
    }

    // check North-East
    ii = i - 1;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[2];
        g_sum += g * filter[2];
        b_sum += b * filter[2];
    }

    // check West
    ii = i;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[3];
        g_sum += g * filter[3];
        b_sum += b * filter[3];
    }

    // center
    ii = i;
    jj = j;
    indx = ii * image.width + jj;

    r = (unsigned int)image.r[indx];
    g = (unsigned int)image.g[indx];
    b = (unsigned int)image.b[indx];

    r_sum += r * filter[4];
    g_sum += g * filter[4];
    b_sum += b * filter[4];

    // check East
    ii = i;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[5];
        g_sum += g * filter[5];
        b_sum += b * filter[5];
    }
    // check South-West
    ii = i + 1;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[6];
        g_sum += g * filter[6];
        b_sum += b * filter[6];
    }
    // check South
    ii = i + 1;
    jj = j;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[7];
        g_sum += g * filter[7];
        b_sum += b * filter[7];
    }
    // check South-East
    ii = i + 1;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns))
    {
        indx = ii * image.width + jj;

        r = (unsigned int)image.r[indx];
        g = (unsigned int)image.g[indx];
        b = (unsigned int)image.b[indx];

        r_sum += r * filter[8];
        g_sum += g * filter[8];
        b_sum += b * filter[8];
    }

    // Save the modifed pixel value in image2
    indx = i * image.width + j;
    image2.r[indx] = (unsigned char)r_sum;
    image2.g[indx] = (unsigned char)g_sum;
    image2.b[indx] = (unsigned char)b_sum;
}

// Blur a chunk of an image
void tst(ppm &image, ppm &image2, int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        int ii = i / image.width;
        int jj = i - ii * image.width;
        process(image, image2, ii, jj);
    }
}

int main()
{
    std::string fname = std::string("./data/sample_5184×3456.ppm");

    ppm image(fname);
    ppm image2(image.width, image.height); // blank to store blurred image w/o threads
    ppm image3(image.width, image.height); // blank to store blurred image w/ threads

    auto beg = std::chrono::high_resolution_clock::now();
    tst(image, image2, 0, image.size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
    int t_without_threads = duration.count();
    std::cout << "Elapsed Time without threads: " << t_without_threads << " microseconds" << std::endl;

    // Repeat for different numbers of threads to use (the image will be divided between threads)
    for (int parts = 1; parts < 30; parts++)
    {

        std::vector<int> bnd = bounds(parts, image.size);

        std::vector<std::thread> tt;

        beg = std::chrono::high_resolution_clock::now();

        // Lauch parts-1 threads
        for (int i = 0; i < parts - 1; ++i)
        {
            tt.push_back(std::thread(tst,
                                     std::ref(image),
                                     std::ref(image2),
                                     bnd[i],
                                     bnd[i + 1]));
        }

        // Use the main thread to do part of the work !!!
        for (int i = parts - 1; i < parts; ++i)
        {
            tst(image, image3, bnd[i], bnd[i + 1]);
        }

        // Join parts-1 threads
        for (auto &e : tt)
        {
            e.join();
        }

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
        int t_with_threads = duration.count();

        // Display the elapsed time

        std::cout << "Elapsed Time with " << parts + 1 << " threads: " << t_with_threads << " microseconds" << std::endl;

        std::cout << "With vs without threads: "
                  << 100.0 * (t_without_threads - t_with_threads) / t_without_threads
                  << "% less time with threads " << std::endl;
    }
    // Save the result
    // image2.write("blur_with_threads.ppm");
    // image3.write("blur_without_threads.ppm");

    return 0;
}
