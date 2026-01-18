/* 
| 2026/01/10
| main_par.cpp
| https://github.com/giuliogiamello/comsci-mod4-5_project
*/

#include <SFML/Graphics.hpp>
#include <complex>

#include <oneapi/tbb.h>
#include <vector>
#include <chrono>
#include <atomic>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using Complex = std::complex<double>;  // alias

/* 
| Function: mandelbrot
| Input: point on the comlex plane 'c'
| Output: number of iterations 'i', if i==256 the point is in the Mandelbrot set
*/
int mandelbrot(Complex const& c)
{
  int i = 0;
  auto z = c;
  for (; i != 256 && norm(z) < 4.; ++i) {
    z = z * z + c;
  }
  return i;
}

/* 
| Function: to_color
| Input: number of iterations returned by the mandelbrot function 'k'
| Output: if k==256 --> black, if k<256 red (brighter the more iterations)
*/
auto to_color(int k)
{
  return k < 256 ? sf::Color{static_cast<sf::Uint8>(10 * k), 0, 0}
                 : sf::Color::Black;
}

/* 
| Function: main
| It sets up an 800*800 pixel canvas,
| define a rectangualar area in the complex plane and compute the step size btw pixels.
| Then creates the image.
*/
int main()
{
  int const display_width{800};
  int const display_height{800};

  Complex const top_left{-2.2, 1.5};
  Complex const lower_right{0.8, -1.5};
  auto const diff = lower_right - top_left;

  auto const delta_x = diff.real() / display_width;
  auto const delta_y = diff.imag() / display_height;

  sf::Image image;

  std::vector<int> grain_sizes = {1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 80, 100, 160, 200, 400, 800};

  std::ofstream result_file("output/results.txt");
  if (!result_file.is_open()) {
    std::cerr << "Error opening results.txt" << std::endl;
    return 1;
  }

  result_file << std::left 
	      << std::setw(15) << "Grain" 
	      << std::setw(15) << "Time [ms]" 
	      << std::setw(15) << "Tasks" 
	      << '\n';

  for (int grain : grain_sizes) {

    std::atomic<int> task_count{0};
    image.create(display_width, display_height);
    auto start_time = std::chrono::high_resolution_clock::now();

    oneapi::tbb::parallel_for(
      oneapi::tbb::blocked_range2d<int>(0, display_height, grain, 0, display_width, grain),
        
      [&](const oneapi::tbb::blocked_range2d<int>& r) {
        task_count++;
        int chunk_start_row = r.rows().begin();
        int chunk_start_col = r.cols().begin();

        for (int row = r.rows().begin(); row != r.rows().end(); ++row) {
          for (int col = r.cols().begin(); col != r.cols().end(); ++col) {

            if ((row == chunk_start_row && row != 0) || (col == chunk_start_col && col != 0)) {
                image.setPixel(col, row, sf::Color::White);
            } else {
              auto k = mandelbrot(top_left + Complex{delta_x * col, delta_y * row});
              image.setPixel(col, row, to_color(k));
            }
          }
        }
      },
      
      oneapi::tbb::simple_partitioner()
    );

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    result_file << std::left 
	        << std::setw(15) << grain 
		<< std::setw(15) << duration.count() 
		<< std::setw(15) << task_count.load() 
		<< '\n';

    std::cout << std::left 
	      << "Grain: " << std::setw(15) << grain 
	      << "Time [ms]: " << std::setw(15) << duration.count() 
	      << "Tasks: " << std::setw(15) << task_count.load() 
	      << std::endl;

    std::string filename = "output/grid_grain_" + std::to_string(grain) + ".png";
    image.saveToFile(filename);
  }

  image.saveToFile("output/mandelbrot.png");
  result_file.close();
}

/*
| Inside the folder 'containers/IMAPP2025/plots' we saved plots of "Time VS Grain" and "Tasks VS Grain".
| The plots have been produced in Python (with matplotplib and pandas),
| the code is 'containers/IMAPP25/plots/mandelbrot_par.ipynbp'.
*/
